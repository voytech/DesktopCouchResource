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

#include <QtDBus/QDBusConnection>
#include <QDebug>

#include <kabc/phonenumber.h>

using namespace Akonadi;
using KABC::PhoneNumber;


using namespace Akonadi;

ContactDesktopCouchResource::ContactDesktopCouchResource( const QString &id )
    : ResourceBase( id ), dbName(QString("contacts2"))
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

    CouchDBQt* m_db = m_dcp.getWrappedCouchDB();
    m_dcp.authenticate();
    m_db->createDatabase("pim");


    changeRecorder()->itemFetchScope().fetchFullPayload();
    synchronizeCollectionTree();

  // TODO: you can put any resource specific initialization code here.
}

ContactDesktopCouchResource::~ContactDesktopCouchResource()
{

}

static QVariant addresseeToVariant( const KABC::Addressee& a )
{
    QMap<QString,QVariant> vMap;
    //vMap.insert( "_id",QVariant(QString(/*a.uid()*/"sadd")));
    //vMap.insert( "_rev", QVariant(QString(/*a.custom( "akonadi-desktop-couch-resource", "_rev" )*/"2")) );
    vMap.insert("first_name",QVariant(QString(a.givenName())));
    vMap.insert("last_name",QVariant(QString(a.familyName())));
    vMap.insert("last_name",QVariant(QString(a.nickName())));
    vMap.insert("email_addresses",QVariant(a.emails()));
    vMap.insert("birth_date",QVariant(a.birthday()));
    QVariantList vlist;
    KABC::PhoneNumber::List phones = a.phoneNumbers(KABC::PhoneNumber::Home);
    for (int i=0;phones.length();i++)
    {
        QMap<QString,QVariant> phone;
        KABC::PhoneNumber pnumber = phones.at(i);
        phone.insert("id",QVariant(pnumber.id()));
        phone.insert("number",QVariant(pnumber.number()));
        phone.insert("type",QVariant(pnumber.type()));
        phone.insert("is_empty",QVariant(pnumber.isEmpty()));
        phone.insert("type_label",QVariant(pnumber.typeLabel()));
        //phone.insert("id",QVariant(pnumber.typeList()));
        vlist.append(phone);
    }
    vMap.insert("phone_numbers_home",QVariant(vlist));
    // FIXME handle known fields
    // FIXME restore unknown fields from customs
    return QVariant(vMap);
}

static KABC::Addressee variantToAddressee( const QVariant& v )
{
  KABC::Addressee a;
  QVariantMap vMap = v.toMap();
  a.setUid( vMap["_id"].toString() );
  a.setGivenName( vMap["first_name"].toString() );
  a.setFamilyName( vMap["last_name"].toString() );

  // extract email addresses
  const QVariantMap emails = vMap["email_addresses"].toMap();
  Q_FOREACH( QVariant email, emails ) {
    QVariantMap emailmap = email.toMap();
    const QString emailstr = emailmap["address"].toString();
    if ( !emailstr.isEmpty() )
      a.insertEmail( emailstr );
  }

  // birthday
  a.setBirthday( QDateTime::fromString( vMap["birth_date"].toString() ) );

  //phone numbers
  const QVariantMap numbers = vMap["phone_numbers"].toMap();
  Q_FOREACH( QVariant number, numbers ) {
    QVariantMap numbermap = number.toMap();
    const QString numberstr = numbermap["number"].toString();
    if ( !numberstr.isEmpty() ) {
      PhoneNumber phonenumber;
      phonenumber.setNumber(numberstr);
      phonenumber.setId(numbermap["description"].toString());

      // FIXME type

      // FIXME priority
      a.insertPhoneNumber( phonenumber );
    }
  }
  a.insertCustom( "akonadi-desktop-couch-resource", "_rev", vMap["_rev"].toString() );

  // FIXME enter all other fields as custom headers as well

  return a;
}

void ContactDesktopCouchResource::retrieveCollections()
{
    Collection::List list;
    list << m_root;
    collectionsRetrieved( list );
}

void ContactDesktopCouchResource::retrieveItems( const Akonadi::Collection &col )
{
    // CouchDB does not support folders so we can safely ignore the collection
    Q_UNUSED( col );
    CouchDBQt* m_db = m_dcp.getWrappedCouchDB();
    m_dcp.authenticate();

    m_db->disconnect( this, SLOT( slotDocumentsListed(CouchDBDocumentInfoList) ) );
    m_db->connect( m_db, SIGNAL( documentsListed( CouchDBDocumentInfoList ) ),
                this, SLOT( slotDocumentsListed(CouchDBDocumentInfoList) ) );
    m_db->listDocuments( "pim" );
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
    info.setDatabase( "pim" );
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
        info.setDatabase("pim");
        m->updateDocument(info,addresseeToVariant(addressee));

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
    if ( !addressee.isEmpty() ) {
      CouchDBQt* m_db = m_dcp.getWrappedCouchDB();
      m_dcp.authenticate();
      CouchDBDocumentInfo info;
      info.setId( addressee.uid() );
      info.setDatabase( "pim" );
      QVariant v = addresseeToVariant( addressee );
      m_db->updateDocument( info, v );
      // FIXME make async and check error
      // setProperty( "akonadiItem", QVariant::fromValue(item) );
      Item i( item );
      i.setRemoteId( addressee.uid() );
      changeCommitted( i );
    } else {
      changeProcessed();
    }
}

void ContactDesktopCouchResource::itemRemoved( const Akonadi::Item &item )
{
  Q_UNUSED( item );
  changeProcessed();
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
  KABC::Addressee a( variantToAddressee( v ) );
  Item i( property("akonadiItem").value<Item>() );
  Q_ASSERT( i.remoteId() == a.uid() );
  i.setMimeType( KABC::Addressee::mimeType() );
  i.setPayload<KABC::Addressee>( a );
  itemRetrieved( i );
}
AKONADI_RESOURCE_MAIN( ContactDesktopCouchResource )

#include "contactdesktopcouchresource.moc"
