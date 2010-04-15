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

#include "test.h"
#include <iostream>
#include <qstringlist.h>
#include <serializer.h>
#include <parser.h>

using namespace QJson;
using namespace std;

ResponsePrinter::ResponsePrinter(CouchDBQt& cdb)
{  
  this->dataBase = &cdb; 
}
ResponsePrinter::~ResponsePrinter(void){  }

void ResponsePrinter::enableDataPrint(bool en)
{
  if (en)
  {
    this->dataBase->disconnect(SIGNAL(databasesListed(const QStringList&)),this,SLOT(showDataBases(const QStringList&)));
    connect(this->dataBase,SIGNAL(databasesListed(const QStringList&)),this,SLOT(showDataBases(const QStringList&))); 
    
    this->dataBase->disconnect(SIGNAL(documentsListed(const CouchDBDocumentInfoList&)),this,SLOT(showDataBaseEntries(const CouchDBDocumentInfoList&)));
    connect(this->dataBase,SIGNAL(documentsListed(const CouchDBDocumentInfoList&)),this,SLOT(showDataBaseEntries(const CouchDBDocumentInfoList&))); 
  
    this->dataBase->disconnect(SIGNAL(documentRetrieved( const QVariant)),this,SLOT(showEntry(const QVariant&)));
    connect(this->dataBase,SIGNAL(documentRetrieved( const QVariant)),this,SLOT(showEntry(const QVariant&)));   
  } 
}

void ResponsePrinter::showDataBases(const QStringList& list)
{
   cout << "Databases available: \n";
   for (int i=0; i<list.count();i++)
   {
      cout << list.at(i).toStdString() << "\n";
   }
}
void ResponsePrinter::showDataBaseEntries(const CouchDBDocumentInfoList& list)
{
   cout << "Current database records: \n";
   for (int i=0; i< list.count(); i++)
   {
      CouchDBDocumentInfo info = list.at(i);
      cout <<  info.database().toStdString() << "::" <<  info.id().toStdString() << endl;
   }
}
void ResponsePrinter::showEntry(const QVariant& qv)    
{
   cout << "Document :\n";
   Serializer serializer;
   QByteArray array = serializer.serialize(qv);  
   cout << array.data() << endl;   
}
