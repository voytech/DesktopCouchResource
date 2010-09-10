/*
    Copyright (c) 2009 Canonical

    Author: Till Adam <till@kdab.com>, Wojciech Mąka <wojmak@gmail.com>

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

#ifndef COUCHDBQT_H
#define COUCHDBQT_H

#include <qtimer.h>
#include <QObject>
#include <qnetworkrequest.h>
#include <qnetworkreply.h>
#include <QAuthenticator>
#include <QtOAuth/QtOAuth>
#include <auth_info.h>
class QHttpResponseHeader;


class CouchDBDocumentInfo
{
public:
    CouchDBDocumentInfo();
    CouchDBDocumentInfo( const CouchDBDocumentInfo& );
    CouchDBDocumentInfo operator=( CouchDBDocumentInfo );
    QString id() const;
    void setId( const QString& );
    QString database() const;
    void setDatabase( const QString& );

private:
    void swap( CouchDBDocumentInfo& );
    class Private;
    Private * const d;
};

typedef QList<CouchDBDocumentInfo> CouchDBDocumentInfoList;

class CouchDBQt : public QObject
{
  Q_OBJECT
public:
    CouchDBQt(int);
    ~CouchDBQt();
    bool notificationsEnabled( const QString& db ) const;
                       // for connections that needs authentication.    
    void enableAuthentication(bool enable);
    void setAuthenticationInfo(const AuthInfo&);
  public slots:
    // CouchDB API.
    void listDatabases();
    void createDatabase( const QString& db );
    void deleteDatabase( const QString& db );
    void listDocuments( const QString& db );
    // slots for documents
    void getDocument( const CouchDBDocumentInfo& info );
    void updateDocument( const CouchDBDocumentInfo& info, const QVariant& v );
    // just added
    void createDocument( const QString& docname, const QString& database, const QVariant& v);
    void deleteDocument( const CouchDBDocumentInfo& info);   
    //
    void setNotificationsEnabled( const QString& db, bool on );
signals:
    void databaseCreated( bool ok, const QString& error = QString() );
    void databaseDeleted( bool ok, const QString& error = QString() );
    void databasesListed( const QStringList& );
    void documentsListed( const CouchDBDocumentInfoList& );
    void documentRetrieved( const QVariant & v );
    void documentUpdated( bool ok, const QString& error = QString() );
    void documentRemoved(bool ok, const QString& error = QString());
    void changeNotification( const QString& db, const QVariant& change );
private slots:
    void slotConnectionErrorOccured(QNetworkReply::NetworkError);
    void slotDatabaseListingFinished();
    void slotDocumentListingFinished();
    void slotDocumentRetrievalFinished();
    void slotDocumentUpdateFinished();
    void slotDocumentDeleteFinished();
    void slotDatabaseCreationFinished();
    void slotDatabaseDeletionFinished();
    void slotDocumentDeleteProgress( const QVariant&);
    void slotNotificationTriggered( const QString& db );
    void slotDocumentUpdateProgress( const QVariant& v );
private:
    //const QString& signHeager(const QString& header);
    QNetworkRequest createRequest(const QString& url, const QOAuth::HttpMethod& method);
    class Private;
    Private * const d;
    AuthInfo a_info;
    int port;
    bool a_enabled;
};

#endif // COUCHDBQT_H
