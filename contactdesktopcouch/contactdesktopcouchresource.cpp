#include "contactdesktopcouchresource.h"

#include "settings.h"
#include "settingsadaptor.h"
#include <akonadi/changerecorder.h>
#include <akonadi/itemfetchscope.h>
#include <akonadi/entitydisplayattribute.h>
#include <akonadi/collection.h>

#include <kfiledialog.h>
#include <klocale.h>
#include <KWindowSystem>
#include <kinputdialog.h>
#include <QtDBus/QDBusConnection>
#include <QDebug>

#include <kabc/phonenumber.h>

using namespace Akonadi;
using KABC::PhoneNumber;


using namespace Akonadi;

ContactDesktopCouchResource::ContactDesktopCouchResource( const QString &id )
    : ResourceBase( id )
{
   setName( i18n("Desktop Couch Address Book") );
   new SettingsAdaptor( Settings::self() );
   QDBusConnection::sessionBus().registerObject( QLatin1String( "/Settings" ),
                            Settings::self(), QDBusConnection::ExportAdaptors );

  //setSupportedMimetypes( QStringList() << KABC::Addressee::mimeType(), "office-address-book" )
    m_root.setParent( Collection::root() );
    m_root.setRemoteId( identifier() );
    m_root.setName( identifier() );

    QStringList mimeTypes;
    mimeTypes << "text/directory";
    m_root.setContentMimeTypes( mimeTypes );

    EntityDisplayAttribute *attr = m_root.attribute<EntityDisplayAttribute>( Collection::AddIfMissing );
    attr->setDisplayName( i18n("Desktop Couch Address Book") );
    //attr->setIconName( "couchdb" );

    dbName = "pim";
    initDataBase();
    changeRecorder()->itemFetchScope().fetchFullPayload();
    synchronizeCollectionTree();
  // TODO: you can put any resource specific initialization code here.
}

ContactDesktopCouchResource::~ContactDesktopCouchResource()
{

}

void ContactDesktopCouchResource::initDataBase()
{
    CouchDBQt* m_db = m_dcp.getWrappedCouchDB();
    m_dcp.authenticate();
    m_db->createDatabase(dbName);
}

void ContactDesktopCouchResource::retrieveCollections()
{
    Collection::List list;
    list << m_root;
    collectionsRetrieved( list );
}

void ContactDesktopCouchResource::retrieveItems( const Akonadi::Collection &col )
{
    Q_UNUSED( col );
    CouchDBQt* m_db = m_dcp.getWrappedCouchDB();
    m_dcp.authenticate();
    m_db->disconnect( this, SLOT( slotDocumentsListed(CouchDBDocumentInfoList) ) );
    m_db->connect( m_db, SIGNAL( documentsListed( CouchDBDocumentInfoList ) ),
                this, SLOT( slotDocumentsListed(CouchDBDocumentInfoList) ) );
    m_db->listDocuments( dbName );
}

bool ContactDesktopCouchResource::retrieveItem( const Akonadi::Item &item, const QSet<QByteArray> &parts )
{
    Q_UNUSED( parts );
    const QString rid = item.remoteId();
    CouchDBQt* m_db = m_dcp.getWrappedCouchDB();
    m_dcp.authenticate();
    m_db->disconnect( this, SLOT( slotDocumentRetrieved(QVariant) ) );
    m_db->connect( m_db, SIGNAL( documentRetrieved(QVariant) ),
                this, SLOT( slotDocumentRetrieved(QVariant) ) );
    CouchDBDocumentInfo info;
    info.setId( rid );
    info.setDatabase( dbName );
    m_db->getDocument(info);

    setProperty( "akonadiItem", QVariant::fromValue(item) );
  return true;
}

void ContactDesktopCouchResource::aboutToQuit()
{

}

void ContactDesktopCouchResource::configure( WId windowId )
{
    Q_UNUSED( windowId );
    QString name = KInputDialog::getText("Enter Data Base Name","Data Base","pim");
    //QString name = KInputDialog::getText("Enter Log file path","Logs","/home");
    //QString name = KInputDialog::getText("Enter Data Base Name","Data Base","pim");
    dbName = name;
    initDataBase();
    synchronize();
}

void ContactDesktopCouchResource::itemAdded( const Akonadi::Item &item, const Akonadi::Collection &collection )
{
    Q_UNUSED(collection);
    KABC::Addressee addressee;
    if ( item.hasPayload<KABC::Addressee>() )
      addressee  = item.payload<KABC::Addressee>();

    if ( !addressee.isEmpty() ) {
  //    mAddressees.insert( addressee.uid(), addressee );
        CouchDBQt* m = m_dcp.getWrappedCouchDB();
        m_dcp.authenticate();
        CouchDBDocumentInfo info;
        info.setId(addressee.uid());
        info.setDatabase(dbName);
        m->updateDocument(info,Mapper::addresseeToVariant(addressee));

      Item i( item );
      i.setRemoteId( addressee.uid() );
      changeCommitted( i );
    } else {
      changeProcessed();
    }
}

void ContactDesktopCouchResource::itemChanged( const Akonadi::Item &item, const QSet<QByteArray> &parts )
{
    Q_UNUSED(parts);
    KABC::Addressee addressee;
    if ( item.hasPayload<KABC::Addressee>() )
      addressee  = item.payload<KABC::Addressee>();
    if ( !addressee.isEmpty() )
    {
      CouchDBQt* m_db = m_dcp.getWrappedCouchDB();
      m_dcp.authenticate();
      CouchDBDocumentInfo info;
      info.setId( item.remoteId() );
      addressee.setUid(item.remoteId());
      info.setDatabase( dbName );
      QVariant v = Mapper::addresseeToVariant( addressee );
      m_db->updateDocument( info, v );
      // FIXME make async and check error
      // setProperty( "akonadiItem", QVariant::fromValue(item) );
      Item i( item );
      i.setPayload<KABC::Addressee>( addressee );
      i.setRemoteId( addressee.uid() );
      changeCommitted( i );
    } else {
      changeProcessed();
    }
}

void ContactDesktopCouchResource::itemRemoved( const Akonadi::Item &item )
{
  Q_UNUSED( item );
   CouchDBQt* m = m_dcp.getWrappedCouchDB();
   m_dcp.authenticate();
   CouchDBDocumentInfo info;
   info.setId(item.remoteId());
   info.setDatabase(dbName);
   m->deleteDocument(info);

  //Item i( item );
  //i.setRemoteId( addressee.uid() );
  changeCommitted( item );
}
void ContactDesktopCouchResource::slotDocumentsListed( const CouchDBDocumentInfoList& list )
{
  Item::List items;
  Q_FOREACH( const CouchDBDocumentInfo& info, list ) {
    Item item;
    item.setRemoteId( info.id() );
    item.setMimeType( KABC::Addressee::mimeType() );
    items.append( item );
  }
  itemsRetrieved( items );
}
void ContactDesktopCouchResource::slotDocumentRetrieved( const QVariant& v )
{
  KABC::Addressee a( Mapper::variantToAddressee( v ) );
  Item i( property("akonadiItem").value<Item>() );
  Q_ASSERT( i.remoteId() == a.uid() );
  i.setMimeType( KABC::Addressee::mimeType() );
  i.setPayload<KABC::Addressee>( a );
  itemRetrieved( i );
}
AKONADI_RESOURCE_MAIN( ContactDesktopCouchResource )

#include "contactdesktopcouchresource.moc"
