/*
    Author: Wojciech Mąka <wojmak@gmail.com>

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

#include "desktop_couch.h"
#include <Qt/QtDBus>
#include <QtOAuth/QtOAuth>

DesktopCouchProvider::DesktopCouchProvider(void ) : db(NULL)
{
   QLog::getLogger()->setOutput("/home/voytech/Logs.txt");
}
DesktopCouchProvider::~DesktopCouchProvider(void )
{
   if (db!=NULL) delete db;
}
/*

*/
CouchDBQt* DesktopCouchProvider::getWrappedCouchDB()
{
   if (db != NULL ) return (db);
   runDesktopCouch();
   return (db);
}
/*
 This method uses Dbus api to get port of local desktopcouch and also runs desktopcouch itself.
 Each invokation of that method will delete our couchdb handler and create a new one.
 TODO: add exceptions.
*/
void DesktopCouchProvider::runDesktopCouch()
{
    QLog::getLogger()->log("-----------------------",QLog::INFO);
    QLog::getLogger()->log("Running DesktopCouch...",QLog::INFO);

   if (db!=NULL) delete db;
   QDBusInterface iface(QString("org.desktopcouch.CouchDB"),QString("/"),QString(""),QDBusConnection::sessionBus());
   if (iface.isValid())
   {
      QDBusMessage message = iface.call("getPort"); 
      QDBusReply<int> reply(message);
      if (reply.isValid())
      {
	 if (reply.value()>0)
	 {
            // creating CouchDBQt instance for managinf underlaying CouchDB instance.
	    db = new CouchDBQt(reply.value());
	 }
      }
   }
}
/*
  This should be replaced by more convenient method of accessing gnome-keyring..
  We have very unnecessery dependecies with gnome devs here.
 */
const QStringList DesktopCouchProvider::getOAuthCredentials(void)
{
    QLog::getLogger()->log("Retrieving credentials...",QLog::INFO);
    //QStringList* creds = NULL;
    g_set_application_name("desktop-couch-qt");
    GnomeKeyringAttributeList* attributes;
    GnomeKeyringResult result;
    GList* found_list;
    GList* i;
    GnomeKeyringFound * found;

    attributes = g_array_new(FALSE, FALSE, sizeof (GnomeKeyringAttribute));
    gnome_keyring_attribute_list_append_string(attributes,"desktopcouch","oauth");
    result = gnome_keyring_find_items_sync(GNOME_KEYRING_ITEM_GENERIC_SECRET,attributes,&found_list);
    char* item;
    if (result == GNOME_KEYRING_RESULT_OK )
    {
        for ( i = found_list; i != NULL; i = i->next )
        {
            found = (GnomeKeyringFound*)i->data;
            item = g_strdup(found->secret);
            QString i(item);
            QStringList lcreds = i.split(":");
            return lcreds;
        }
    }
    QLog::getLogger()->log("Retrieving credentials failed...\n(check if Gnome-Keyring-Daemon is running)",QLog::ERROR);
    return QStringList();
}
void DesktopCouchProvider::authenticate()
{
   getWrappedCouchDB();
   QStringList credentials =  getOAuthCredentials();
   QLog::getLogger()->log("Applying credentials...",QLog::INFO);
   if (db!=NULL)
   {
     if (!credentials.size() == 0)
     {
        QMap<QString,QString> map;
        //This is wrong approach we should hardly specify interface.
         map.insert("ConsumerKey",credentials.at(0));
         map.insert("ConsumerSecret",credentials.at(1));
         map.insert("Token",credentials.at(2));
         map.insert("TokenSecret",credentials.at(3));
         AuthInfo info(AuthInfo::OAUTH,map);
         db->enableAuthentication(true);
         db->setAuthenticationInfo(info);
     }
     else QLog::getLogger()->log("Empty credentials list...",QLog::ERROR);
   }  
}
