#ifndef CONTACTDESKTOPCOUCHRESOURCE_H
#define CONTACTDESKTOPCOUCHRESOURCE_H

#include <akonadi/resourcebase.h>
#include <akonadi/agentbase.h>
#include <akonadi/collection.h>
#include <kabc/addressee.h>
#include <couchdb-qt.h>
#include <desktop_couch.h>
#include "mapper.h"
class ContactDesktopCouchResource : public Akonadi::ResourceBase,
                           public Akonadi::AgentBase::Observer
{
  Q_OBJECT

  public:
    ContactDesktopCouchResource( const QString &id );
    ~ContactDesktopCouchResource();

  public Q_SLOTS:
    virtual void configure( WId windowId );

  protected Q_SLOTS:
    void retrieveCollections();
    void retrieveItems( const Akonadi::Collection &col );
    bool retrieveItem( const Akonadi::Item &item, const QSet<QByteArray> &parts );

  protected:
    virtual void aboutToQuit();

    virtual void itemAdded( const Akonadi::Item &item, const Akonadi::Collection &collection );
    virtual void itemChanged( const Akonadi::Item &item, const QSet<QByteArray> &parts );
    virtual void itemRemoved( const Akonadi::Item &item );

  private slots:
    void slotDocumentsListed( const CouchDBDocumentInfoList& );
    void slotDocumentRetrieved( const QVariant& v );
//    void slotDocumentsListed( const CouchDBDocumentInfoList& );
//   void slotDocumentRetrieved( const QVariant& v );

  private:
    void initDataBase(void);
    DesktopCouchProvider  m_dcp;
    Akonadi::Collection m_root;
    QString dbName;
};

#endif
