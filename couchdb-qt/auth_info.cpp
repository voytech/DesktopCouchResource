/*
   Author: Wojciech Mąka <wojmak@gmail.com>

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

#include "auth_info.h"

AuthInfo::AuthInfo(AuthMode mode,const QMap<QString,QString> data)
{
  a_mode = mode;
  aData = data;
}
AuthInfo::AuthInfo(void)
{
}
AuthInfo::~AuthInfo(void)
{
}
void AuthInfo::setAuthorizationMode(AuthMode mode)
{
   a_mode = mode;
}

AuthInfo::AuthMode AuthInfo::authorizationMode(void)
{
   return a_mode;
}

void AuthInfo::setAuthData(const QMap<QString,QString> data)
{
   aData = data;
}

QMap<QString,QString> AuthInfo::authData(void)
{
   return aData;
}
// 
QNetworkRequest AuthInfo::createAuthorizedRequest(const  QString& url,const QOAuth::HttpMethod& method)
{
   QNetworkRequest req;
   if (a_mode==AuthInfo::OAUTH)
   {
      if (aData.contains("ConsumerKey") && aData.contains("ConsumerSecret") && aData.contains("Token") && aData.contains("TokenSecret"))
      {
	QOAuth::ParamMap map;
	map.clear();
	QOAuth::Interface qoauth;	
	qoauth.setConsumerKey(QByteArray().append(aData.value("ConsumerKey")));
	qoauth.setConsumerSecret(QByteArray().append(aData.value("ConsumerSecret")));
	QByteArray content = qoauth.createParametersString( url, method,QByteArray().append(aData.value("Token")), QByteArray().append(aData.value("TokenSecret")), QOAuth::HMAC_SHA1,map, QOAuth::ParseForHeaderArguments );
	req.setUrl(QUrl(url));
	req.setRawHeader("Authorization",content);
      }
   }
   else 
     if (a_mode==USERPASSWORD)
     {
       if (aData.contains("User") && aData.contains("Password"))
       {
	  // Implement here a logic for creating request if user and password credentials are given.
       }
     }
     else
     {
     }       
   return req;
}
