#include <QtCore/QCoreApplication>
#include <iostream>
#include <qdebug.h>
#include <qtimer.h>
#include <qmetatype.h>
//include <Qt/QtDBus>
#include <desktop_couch.h>
//#include <couchdb-qt.h>
//class Test;

int main( int argc, char** argv )
{
  QCoreApplication app( argc, argv );

  QMap<QString,QVariant> smap;
  smap.insert("Name",QVariant(QString("Dorota")));
  smap.insert("LastName",QVariant(QString("Loran")));
  smap.insert("BirthDate",QVariant(QString("19-09-1985")));
  QVariant sample(smap);


  CouchDBDocumentInfo info;
  info.setId("doc3");
  info.setDatabase("contacts");

  
  DesktopCouchProvider provider;

  CouchDBQt* db = provider.getWrappedCouchDB();
  provider.authenticate();
  // db->listDocuments("contacts2");
  db->updateDocument(info,sample);
  //db->createDatabase("contacts");
  //ResponsePrinter tester(*db);
  //tester.enableDataPrint(true);
 // qDebug("removing ");
  //db->deleteDocument(info);*/
  //delete db;
  return app.exec();
}




