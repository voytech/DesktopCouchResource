/*
    Copyright (c) 2009 Canonical

    Author: Till Adam <till@kdab.com>

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2.1 or version 3 of the license,
    or later versions approved by the membership of KDE e.V.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
*/


#include "couchdb-qt.h"

#include "couchdbqtchangenotifier.h"

#include <serializer.h>
#include <parser.h>
#include <qwaitcondition.h>

#include <QtNetwork/QHttp>
#include <QtCore/QUrl>
#include <QtCore/QDebug>
#include <QtCore/QCoreApplication>
#include <QtCore/QTimer>
#include <QtCore/QVariant>

#include <QHttp>
#include <QtNetwork/QNetworkAccessManager>
#include <QNetworkRequest>
#include <iostream>
#include <stdio.h>
#include <qnetworkreply.h>
#include <QtOAuth/QtOAuth>
using namespace QJson;


class CouchDBDocumentInfo::Private
{
public:
  Private()
  {
  }
  QString dbname;
  QString docid;
};

CouchDBDocumentInfo::CouchDBDocumentInfo()
:d( new Private )
{
}

CouchDBDocumentInfo::CouchDBDocumentInfo( const CouchDBDocumentInfo& other )
:d( new Private( *other.d ) )
{
}

CouchDBDocumentInfo CouchDBDocumentInfo::operator= ( CouchDBDocumentInfo other )
{
  if( this != &other )
    other.swap( *this );
  return *this;
}


void CouchDBDocumentInfo::swap( CouchDBDocumentInfo& other )
{
  *other.d = *d;
}

void CouchDBDocumentInfo::setId( const QString& id )
{
  d->docid = id;
}

QString CouchDBDocumentInfo::id() const
{
  return d->docid;
}

void CouchDBDocumentInfo::setDatabase( const QString& db )
{
  d->dbname = db;
}

QString CouchDBDocumentInfo::database() const
{
  return d->dbname;
}

class CouchDBQt::Private
{
  public:
    Private()
    {
    }
    QString database;
    QVariant parseJSONString( const QByteArray& json );
    CouchDBDocumentInfoList variantMapToDocInfoList( const QVariant& map );
    QString serializeToJSONString( const QVariant& v);
    QNetworkAccessManager nmanager;
    Parser parser;
    Serializer serializer;
    QMap<QString, CouchDBQtChangeNotifier*> notifiers;   
    CouchDBDocumentInfo lastDoc;
    QVariant lastVariant;
};



QVariant CouchDBQt::Private::parseJSONString( const QByteArray& json )
{

  bool ok;
  QVariant data = parser.parse ( json, &ok );
  if ( !ok ) {
    qCritical("%i - Error: %s", parser.errorLine(), parser.errorString().toLatin1().data());
    exit (1);
  }
  else {
    qDebug() << "json object successfully converted to:";
    //qDebug() << data;
  }
  return data;
}

QString CouchDBQt::Private::serializeToJSONString( const QVariant& v )
{
    return serializer.serialize( v );
}

CouchDBDocumentInfoList CouchDBQt::Private::variantMapToDocInfoList( const QVariant& vmap )
{
  CouchDBDocumentInfoList list;
  QVariantMap map = vmap.toMap();
  bool ok = false;
  const int rows = map["total_rows"].toInt( &ok );
  if ( !ok )
    return list;
  const int offset = map["offset"].toInt( &ok );
  if ( !ok )
    return list;
  qDebug() << rows << offset;
  QVariantList rowlist = map["rows"].toList();
  if ( rowlist.count() != rows ) {
    qWarning() << "Inconsistent database: " << database;
    return list;
  }

  Q_FOREACH( QVariant v, rowlist ) {
    QVariantMap m = v.toMap();
    const QString id = m["id"].toString();
    if ( !id.isEmpty() ) {
      CouchDBDocumentInfo info;
      info.setDatabase( database );
      info.setId( id );
      list << info;
    }
  }
  return list;
}

CouchDBQt::CouchDBQt(int port)
    :d( new Private )
{
  this->port = port;
}

CouchDBQt::~CouchDBQt() { if (d!=NULL) delete d; }


void CouchDBQt::enableAuthentication(bool enable)
{
     a_enabled = enable;
}

void CouchDBQt::setAuthenticationInfo(const AuthInfo& info )
{
  this->a_info = info;
}


void CouchDBQt::setNotificationsEnabled( const QString& db, bool on )
{
  if ( on ) {
    if ( !d->notifiers.contains( db ) ) {
      CouchDBQtChangeNotifier *notifier = new CouchDBQtChangeNotifier( db );
      connect( notifier, SIGNAL(notification(QString,QVariant)),
               this, SLOT(slotNotificationTriggered(QString)) );
      d->notifiers.insert( db, notifier );
    }
  } else {
    if ( d->notifiers.contains( db ) ) {
      delete d->notifiers.take( db );
    }
  }
}

bool CouchDBQt::notificationsEnabled( const QString& db) const
{
  return d->notifiers.contains( db );
}

void CouchDBQt::listDatabases()
{
   QNetworkRequest req;
   QString s(QString("http://localhost:%1/_all_dbs").arg(this->port));
   req = this->a_info.createAuthorizedRequest(s,QOAuth::GET);
   QNetworkReply* reply = d->nmanager.get(req);
   connect(reply,SIGNAL(finished()), SLOT(slotDatabaseListingFinished()));
}

void CouchDBQt::slotDatabaseListingFinished()
{
  // FIXME DOS?
  QNetworkReply* reply = ((QNetworkReply*)sender());
  const QByteArray dbstring = reply->readAll();
  const QVariant dbs = d->parseJSONString( dbstring );
  QStringList dbstringlist;
  Q_FOREACH( QVariant v, dbs.toList() ) {
    dbstringlist << v.toString();
  }
  emit databasesListed( dbstringlist );
}

void CouchDBQt::createDatabase( const QString& db )
{
  // FIXME
   QString s(QString("http://localhost:%1/%2").arg(this->port).arg(db));
   QNetworkRequest req = this->a_info.createAuthorizedRequest(s,QOAuth::PUT);
   QNetworkReply* reply = d->nmanager.put(req,"");
   connect(reply,SIGNAL(finished()),this, SLOT(slotDatabaseCreationFinished()));
}
void CouchDBQt::slotDatabaseCreationFinished()
{
  const QByteArray array = ((QNetworkReply*)sender())->readAll();
  QVariant variant = d->parseJSONString(array);
  QVariantMap map = variant.toMap();
  // listing result
  if ( map.contains("error") )
  {
    const QString errType = map["error"].toString();
    const QString err = map["reason"].toString();
    qWarning() << errType << " - " << err;
    emit databaseCreated( false, err );
    return;
  }
  Q_ASSERT( map.contains("ok") && map["ok"].toBool() == true );
  emit databaseCreated( true );
}
  // FIXME Check if it is written properly
void CouchDBQt::deleteDatabase( const QString& db )
{
    QString s(QString("http://localhost:%1/%2").arg(this->port).arg(db));
    QNetworkRequest req = this->a_info.createAuthorizedRequest(s,QOAuth::DELETE);
    QNetworkReply* reply = d->nmanager.deleteResource(req);
    connect(reply,SIGNAL(finished()),SLOT(slotDatabaseDeletionFinished()));
}

void CouchDBQt::slotDatabaseDeletionFinished()
{
  const QByteArray array = ((QNetworkReply*)sender())->readAll();
  QVariant variant = d->parseJSONString(array);
  QVariantMap map = variant.toMap();
  // listing result
  if ( map.contains("error") )
  {
    const QString errType = map["error"].toString();
    const QString err = map["reason"].toString();
    qWarning() << errType << " - " << err;
    emit databaseDeleted( false, err );
    return;
  }
  Q_ASSERT( map.contains("ok") && map["ok"].toBool() == true );
  emit databaseDeleted( true );
}

void CouchDBQt::listDocuments( const QString& db )
{
  QNetworkRequest req;
  QString s(QString("http://localhost:%1/%2/_all_docs").arg(this->port).arg(db));
  req = this->a_info.createAuthorizedRequest(s,QOAuth::GET);
  QNetworkReply* reply = d->nmanager.get(req);
  connect( reply, SIGNAL( finished()) ,
           this, SLOT( slotDocumentListingFinished() ) );
  d->database = db;
}

void CouchDBQt::slotDocumentListingFinished()
{
  // FIXME DOS?
  QNetworkReply* reply = ((QNetworkReply *)sender());
  const QByteArray docs = reply->readAll();
  //qDebug() << docs;
  const QVariant docsAsVariant = d->parseJSONString( docs );
  const CouchDBDocumentInfoList docList = d->variantMapToDocInfoList( docsAsVariant );
  emit documentsListed( docList );
}

void CouchDBQt::getDocument( const CouchDBDocumentInfo & info )
{  
  if ( info.id().isEmpty() )
    return;
  d->lastDoc = info;
  QNetworkRequest req;
  QString s(QString("http://localhost:%1/%2/%3").arg(this->port).arg(info.database()).arg(info.id()));
  req = this->a_info.createAuthorizedRequest(s,QOAuth::GET);
  QNetworkReply* reply = d->nmanager.get(req);
  connect( reply, SIGNAL( finished() ), this, SLOT( slotDocumentRetrievalFinished() ) );
}

void CouchDBQt::slotDocumentRetrievalFinished()
{
  // FIXME DOS?
  QNetworkReply* reply = ((QNetworkReply *)sender());
  const QByteArray doc = reply->readAll();
  //qDebug() << doc;
  const QVariant docAsVariant = d->parseJSONString( doc );  
  emit documentRetrieved( docAsVariant );

}

void CouchDBQt::createDocument( const QString& docname, const QString& database, const QVariant& v )
{
  const QString str = d->serializeToJSONString( v );
  if ( str.isNull() ) {
    emit documentUpdated( false, tr("Error parsing JSON document") );
    return;
  }
  QNetworkRequest req;
  QString s(QString("http://localhost:%1/%2/%3").arg(this->port).arg(database).arg(docname));
  req = this->a_info.createAuthorizedRequest(s, QOAuth::PUT);
  QNetworkReply* reply = d->nmanager.put(req,str.toUtf8());
  connect(reply, SIGNAL(finished()),SLOT(slotDocumentUpdateFinished()));
}

//TODO implement
void CouchDBQt::deleteDocument( const CouchDBDocumentInfo& info )
{ 
    this->disconnect(SIGNAL(documentRetrieved(const QVariant&)));
    connect(this, SIGNAL(documentRetrieved(const QVariant&)),this,SLOT(slotDocumentDeleteProgress(const QVariant&)));
    this->getDocument(info);
}
void CouchDBQt::slotDocumentDeleteProgress(const QVariant& doc)
{
    QVariant revisionV = (doc.toMap()).take("_rev");
    QString revision = revisionV.toString();
    QString s(QString("http://localhost:%1/%2/%3").arg(this->port).arg(d->lastDoc.database()).arg(d->lastDoc.id()));
    QNetworkRequest req = this->a_info.createAuthorizedRequest(s, QOAuth::DELETE);
    req.setRawHeader("If-Match",QByteArray().append(revision));
    QNetworkReply* reply = d->nmanager.deleteResource(req);
    connect(reply, SIGNAL(finished()),SLOT(slotDocumentDeleteFinished()));
}
void CouchDBQt::slotDocumentDeleteFinished()
{
    const QByteArray array = ((QNetworkReply*)sender())->readAll();
    QVariant variant = d->parseJSONString(array);
    QVariantMap map = variant.toMap();
    // listing result
    if ( map.contains("error") )
    {
      const QString errType = map["error"].toString();
      const QString err = map["reason"].toString();
      qWarning() << errType << " - " << err;
      emit documentRemoved( false, err );
      return;
    }
    Q_ASSERT( map.contains("ok") && map["ok"].toBool() == true );
    emit documentRemoved( true );
}
void CouchDBQt::updateDocument( const CouchDBDocumentInfo& info, const QVariant& v )
{
  d->lastDoc = info;
  d->lastVariant = v;

  const QString str = d->serializeToJSONString( v );
  if ( str.isNull() ) {
    emit documentUpdated( false, tr("Error parsing JSON document") );
    return;
  }
  QNetworkRequest req;
  QString s(QString("http://localhost:%1/%2/%3").arg(this->port).arg(info.database()).arg(info.id()));
  req = this->a_info.createAuthorizedRequest(s, QOAuth::PUT);
  QNetworkReply* reply = d->nmanager.put(req,str.toUtf8());
  connect(reply, SIGNAL(finished()),SLOT(slotDocumentUpdateFinished()));
}

void CouchDBQt::slotDocumentUpdateFinished()
{

  QNetworkReply* reply = ((QNetworkReply*)sender());
  const QVariantMap map = d->parseJSONString( reply->readAll() ).toMap();
  if ( map.contains("error") ) {
    const QString err = map["reason"].toString();
    qWarning() << err;
    if ( err.contains("Document update conflict",Qt::CaseInsensitive))
    {
        this->disconnect(SIGNAL(documentRetrieved(const QVariant&)));
        connect(this, SIGNAL(documentRetrieved(const QVariant&)),this,SLOT(slotDocumentUpdateProgress(const QVariant&)));
        getDocument(d->lastDoc);
    }
    else emit documentUpdated( false, err );
    return;
  }
  Q_ASSERT( map.contains("ok") && map["ok"].toBool() == true );
  emit documentUpdated( true );
}
void CouchDBQt::slotDocumentUpdateProgress(const QVariant& v)
{
    QString json = d->serializeToJSONString(d->lastVariant);
    QVariantMap map = v.toMap();
    QVariant revisionV = map.value("_rev");
    QString revision = revisionV.toString();
    QString s(QString("http://localhost:%1/%2/%3").arg(this->port).arg(d->lastDoc.database()).arg(d->lastDoc.id()));
    QNetworkRequest req = this->a_info.createAuthorizedRequest(s, QOAuth::PUT);
    req.setRawHeader("If-Match",QByteArray().append(revision));
    QNetworkReply* reply = d->nmanager.put(req,json.toUtf8());
    //connect(reply, SIGNAL(finished()),SLOT(slotDocumentUpdateFinished()));
}
void CouchDBQt::slotNotificationTriggered( const QString& db )
{
  qWarning() << "Notified: " << db;
}


