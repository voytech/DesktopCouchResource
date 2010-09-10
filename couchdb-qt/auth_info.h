/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef AUTH_INFO_H
#define AUTH_INFO_H

#include <qtimer.h>
#include <QObject>
#include <qnetworkrequest.h>
#include <qnetworkreply.h>
#include <QAuthenticator>
#include <QtOAuth/QtOAuth>

class CouchDBQt;
class AuthInfo 
{
public:   
  enum AuthMode{
     OAUTH,
     USERPASSWORD,
     UNKNOWN
  };
  AuthInfo(void);
  AuthInfo(AuthMode mode,const QMap<QString,QString> data);
  virtual ~AuthInfo(void);
  void setAuthData(const QMap<QString,QString> data);
  void setAuthorizationMode(AuthMode);
  AuthMode authorizationMode(void);
  QMap<QString,QString> authData(void);
  virtual  QNetworkRequest createAuthorizedRequest(const QString& url, const QOAuth::HttpMethod& method);

private:
  QMap<QString,QString> aData;   
  AuthMode a_mode;  
  
};

#endif // AUTH_INFO_H
