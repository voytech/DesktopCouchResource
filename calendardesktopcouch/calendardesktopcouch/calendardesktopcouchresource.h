#ifndef CALENDARDESKTOPCOUCHRESOURCE_H
#define CALENDARDESKTOPCOUCHRESOURCE_H

#include <akonadi/resourcebase.h>
#include <couchdb-qt.h>
#include <desktop_couch.h>
#include <kcal/incidencebase.h>
#include <kcal/incidence.h>
//#include <kcalcore/incidencebase.h>
//#include <akonadi/kcal/incidencemimetypevisitor.h>
#include <QLog.h>
class calendardesktopcouchResource : public Akonadi::ResourceBase,
                           public Akonadi::AgentBase::Observer
{
  Q_OBJECT
  private:    
    DesktopCouchProvider  m_dcp;
    //Akonadi::IncidenceMimeTypeVisitor* mtvisitor;
    Akonadi::Collection m_root;
    QString dbName;
    void initDataBase(void);
  public:
    calendardesktopcouchResource( const QString &id );
    ~calendardesktopcouchResource();

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
};

#endif
