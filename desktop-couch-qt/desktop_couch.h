/*
    Copyright [yyyy] [name of copyright owner]

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
#ifndef DESKTOP_COUCH_H
#define DESKTOP_COUCH_H

#include <qtimer.h>
#include <QObject>
#include <qnetworkrequest.h>
#include <qnetworkreply.h>
#include <QtOAuth/QtOAuth>

#include "couchdb-qt.h"
#include <auth_info.h>
#include <QtCrypto/QtCrypto>
#include <gnome-keyring-1/gnome-keyring.h>
#include <gnome-keyring-1/gnome-keyring-result.h>

class DesktopCouchProvider
{
  public: 
    DesktopCouchProvider(void);
    virtual ~DesktopCouchProvider(void);
    void authenticate();
    CouchDBQt* getWrappedCouchDB();
  private:
    void runDesktopCouch();
    const QStringList getOAuthCredentials(void);
    CouchDBQt* db;
    //In init method we'll determine port on which desktopcouch is running, after that we have to use OAuth - as for know do not know how ?
    //Then we have to edit a record for management database - the paired_server_records... but I think this record will be arledy properly set 
    //after the desktopcouch is running. 
};
#endif // DESKTOP_COUCH_H
