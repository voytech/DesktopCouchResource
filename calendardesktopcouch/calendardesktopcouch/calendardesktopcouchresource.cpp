#include "calendardesktopcouchresource.h"

#include "settings.h"
#include "settingsadaptor.h"
#include <akonadi/changerecorder.h>
#include <akonadi/itemfetchscope.h>
#include <akonadi/entitydisplayattribute.h>
#include <QtDBus/QDBusConnection>
#include <klocale.h>
#include "incidencemapper.h"
#include "kcal/journal.h"
#include <boost/shared_ptr.hpp>


using namespace Akonadi;
using namespace KCal;
calendardesktopcouchResource::calendardesktopcouchResource( const QString &id )
  : ResourceBase( id )
    //mtvisitor(new Akonadi::IncidenceMimeTypeVisitor())
{
    setName( i18n("Desktop Couch Calendar") );
    new SettingsAdaptor( Settings::self() );
    QDBusConnection::sessionBus().registerObject( QLatin1String( "/Settings" ),Settings::self(), QDBusConnection::ExportAdaptors );

   //setSupportedMimetypes( QStringList() << KABC::Addressee::mimeType(), "office-address-book" )
     m_root.setParent( Collection::root() );
     m_root.setRemoteId( identifier() );
     m_root.setName( identifier() );

     QStringList mimeTypes;

     mimeTypes << "text/calendar"
               << "application/x-vnd.akonadi.calendar.event"
               << "application/x-vnd.akonadi.calendar.todo"
               << "application/x-vnd.akonadi.calendar.journal";
     m_root.setContentMimeTypes( mimeTypes );

     EntityDisplayAttribute *attr = m_root.attribute<EntityDisplayAttribute>( Collection::AddIfMissing );
     attr->setDisplayName( i18n("Desktop Couch Calendar") );

     dbName = "calendar";
     QLog::getLogger()->setOutput("/home/voytech/calendar_resource_logs.txt");
     initDataBase();
     changeRecorder()->itemFetchScope().fetchFullPayload();
     synchronizeCollectionTree();
}

calendardesktopcouchResource::~calendardesktopcouchResource()
{
    //delete mtvisitor;
}
void calendardesktopcouchResource::initDataBase()
{
    QLog::getLogger()->log("Initializing data base :"+dbName+"\n",QLog::INFO);

    CouchDBQt* m_db = m_dcp.getWrappedCouchDB();
    m_dcp.authenticate();
    m_db->createDatabase(dbName);
}

void calendardesktopcouchResource::retrieveCollections()
{
    QLog::getLogger()->log("Retrieving collections for :"+dbName+"\n",QLog::INFO);

    Collection::List list;
    list << m_root;
    collectionsRetrieved( list );
}

void calendardesktopcouchResource::retrieveItems( const Akonadi::Collection &collection )
{
  QLog::getLogger()->log("Retrieving items for :"+dbName+"\n",QLog::INFO);

  Q_UNUSED( collection );
  CouchDBQt* m_db = m_dcp.getWrappedCouchDB();
  m_dcp.authenticate();
  m_db->disconnect( this, SLOT( slotDocumentsListed(CouchDBDocumentInfoList) ) );
  m_db->connect( m_db, SIGNAL( documentsListed( CouchDBDocumentInfoList ) ),
              this, SLOT( slotDocumentsListed(CouchDBDocumentInfoList) ) );
  m_db->listDocuments( dbName );
}

bool calendardesktopcouchResource::retrieveItem( const Akonadi::Item &item, const QSet<QByteArray> &parts )
{
    QLog::getLogger()->log("Retrieving item ..\n",QLog::INFO);

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

void calendardesktopcouchResource::aboutToQuit()
{
  // TODO: any cleanup you need to do while there is still an active
  // event loop. The resource will terminate after this method returns
}

void calendardesktopcouchResource::configure( WId windowId )
{
  Q_UNUSED( windowId );
  // TODO: this method is usually called when a new resource is being
  // added to the Akonadi setup. You can do any kind of user interaction here,
  // e.g. showing dialogs.
  // The given window ID is usually useful to get the correct
  // "on top of parent" behavior if the running window manager applies any kind
  // of focus stealing prevention technique
  //
  // If the configuration dialog has been accepted by the user by clicking Ok,
  // the signal configurationDialogAccepted() has to be emitted, otherwise, if
  // the user canceled the dialog, configurationDialogRejected() has to be emitted.
}

void calendardesktopcouchResource::itemAdded( const Akonadi::Item &item, const Akonadi::Collection &collection )
{
    QLog::getLogger()->log("Adding item\n",QLog::INFO);

    Q_UNUSED(collection);
    if ( item.hasPayload<Incidence::Ptr>() )
    {
        Incidence::Ptr incidencePtr = item.payload<Incidence::Ptr>();
        Incidence* inc = incidencePtr.get();
        if (inc!=NULL)
        {                 
            QVariant variant = IncidenceMapper::incidenceToVariant(inc);
            CouchDBQt* m = m_dcp.getWrappedCouchDB();
            if (m!=NULL)
            {
                m_dcp.authenticate();
                CouchDBDocumentInfo info;
                info.setId(inc->uid());

                QLog::getLogger()->log("Item id :"+inc->uid()+", and mimeType: "+item.mimeType()+"\n",QLog::INFO);

                info.setDatabase(dbName);
                m->updateDocument(info,variant);
                Item i( item );
                i.setRemoteId( inc->uid() );
                changeCommitted( i );
            }
        }
        else
        {
                changeProcessed();
        }
    }
}

void calendardesktopcouchResource::itemChanged( const Akonadi::Item &item, const QSet<QByteArray> &parts )
{
    QLog::getLogger()->log("Item changed\n",QLog::INFO);

    if ( item.hasPayload<Incidence::Ptr>() )
    {
        Incidence::Ptr incidencePtr = item.payload<Incidence::Ptr>();
        Incidence* inc = incidencePtr.get();
        if (inc!=NULL)
        {
            CouchDBQt* m = m_dcp.getWrappedCouchDB();
            if (m!=NULL)
            {
                m_dcp.authenticate();
                CouchDBDocumentInfo info;
                info.setId(item.remoteId());
                inc->setUid(item.remoteId());
                info.setDatabase(dbName);
                QVariant variant = IncidenceMapper::incidenceToVariant(inc);
                m->updateDocument(info,variant);
                Item i( item );
                QLog::getLogger()->log("Item id :"+inc->uid()+", and mimeType: "+item.mimeType()+"\n",QLog::INFO);
                i.setRemoteId( inc->uid() );
                i.setPayload<Incidence::Ptr>(incidencePtr);
                changeCommitted( i );
            }
        }
        else
        {
          changeProcessed();
        }
    }
}

void calendardesktopcouchResource::itemRemoved( const Akonadi::Item &item )
{
    QLog::getLogger()->log("Item removed\n",QLog::INFO);

    Q_UNUSED( item );
    CouchDBQt* m = m_dcp.getWrappedCouchDB();
    if (m!=NULL)
    {
        m_dcp.authenticate();
        CouchDBDocumentInfo info;
        info.setId(item.remoteId());
        info.setDatabase(dbName);
        QLog::getLogger()->log("Item id :"+info.id()+", and mimeType: "+item.mimeType()+"\n",QLog::INFO);
        m->deleteDocument(info);
        changeCommitted( item );
    }
    else changeProcessed();
    //Item i( item );
    //i.setRemoteId( addressee.uid() );

}
void calendardesktopcouchResource::slotDocumentsListed( const CouchDBDocumentInfoList&  documents)
{
    QLog::getLogger()->log("Documents have been listed\n",QLog::INFO);
    Item::List items;
    Q_FOREACH( const CouchDBDocumentInfo& info, documents ) {
      Item item;
      item.setRemoteId( info.id() );
      item.setMimeType( "text/calendar" );
      items.append( item );
    }
    itemsRetrieved( items );
}

void calendardesktopcouchResource::slotDocumentRetrieved( const QVariant& v )
{
    QLog::getLogger()->log("Document have been retrieved.. Adding to Akonadi collection\n",QLog::INFO);

    KCal::Incidence* inc =  IncidenceMapper::variantToIncidence( v ) ;
    KCal::Incidence::Ptr ptr = KCal::Incidence::Ptr(inc);
    Item i( property("akonadiItem").value<Item>() );
    Q_ASSERT( i.remoteId() == inc->uid() );
    i.setMimeType( "text/calendar" );
    i.setPayload<KCal::Incidence::Ptr>( ptr );
    itemRetrieved( i );
}

AKONADI_RESOURCE_MAIN( calendardesktopcouchResource )

#include "calendardesktopcouchresource.moc"
