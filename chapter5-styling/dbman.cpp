#include "dbman.h"
#include <QJsonArray>

DBMan::DBMan(QObject *parent): QObject(parent)
{
    qDebug() << " Function invoking";
//createDatabase();

}

void DBMan::createDatabase(){
    if (QSqlDatabase::database().tables().contains(QStringLiteral("Contacts"))) {
        // The table already exists; we don't need to do anything.
       // return;
    }

    QSqlQuery query;
    if (!query.exec(
        "CREATE TABLE IF NOT EXISTS 'LoginDataBase' ("
        "   'userid' TEXT NOT NULL,"
        "   password TEXT NOT NULL,"
        "   phoneno TEXT NOT NULL"
        ")")) {
        qFatal("Failed to query database: %s", qPrintable(query.lastError().text()));
    }

    QSqlQuery gpsquerystore;
    if (!gpsquerystore.exec(
        "CREATE TABLE IF NOT EXISTS 'GpsStore' ("
        "   'userid' TEXT NOT NULL,"
        "   latitude TEXT NOT NULL,"
        "   longitude TEXT NOT NULL"
        ")")) {
        qFatal("Failed to query database: %s", qPrintable(gpsquerystore.lastError().text()));
    }

}
void DBMan::loginDataBase(QString userid,QString password,QString phoneno){
    QSqlQuery query;
    QString queri=QString("delete from LoginDataBase");
    if (!query.exec(queri)) {
        qFatal("Failed to query LoginDataBase: %s", qPrintable(query.lastError().text()));
    }else{
        qDebug() << "Deleted";
    }
    QString quer=QString("INSERT INTO LoginDataBase(userid,password,phoneno) VALUES('%1','%2','%3')").arg(userid).arg(password).arg(phoneno);
    if (!query.exec(quer)) {
        qFatal("Failed to query LoginDataBase: %s", qPrintable(query.lastError().text()));
    }
}
void DBMan::gpstore(QString userid,QString latitude,QString longitude){
  QSqlQuery query;
    QString quer=QString("INSERT INTO GpsStore(userid,latitude,longitude) VALUES('%1','%2','%3')").arg(userid).arg(latitude).arg(longitude);
    if (!query.exec(quer)) {
        qFatal("Failed to query GpsStore: %s", qPrintable(query.lastError().text()));
    }
}
QString DBMan::gpscopy(){
    QJsonArray recordObject;
//        recordObject.insert("FirstName", QJsonValue::fromVariant("John"));
//        recordObject.insert("LastName", QJsonValue::fromVariant("Doe"));
//        recordObject.insert("Age", QJsonValue::fromVariant(43));

    QString quer=QString("select * from GpsStore");
       QSqlQuery qry;
       qDebug() << quer;
       if(qry.exec(quer)){
          // qDebug()<< qry.value(qry.record().indexOf("user_id")).toString();;
              if(qry.next())
              {
                  qDebug() << qry.value(qry.record().indexOf("userid")).toString();
                  QJsonObject addressObject;
                  addressObject.insert("latitude", qry.value(qry.record().indexOf("latitude")).toString());
                  addressObject.insert("longitude", qry.value(qry.record().indexOf("longitude")).toString());
                  addressObject.insert("userid",qry.value(qry.record().indexOf("userid")).toString());
                  recordObject.push_back(addressObject);

              }else{
              //    return "no";
              }
       }else{
       //qFatal("Failed to query database: %s", qPrintable(qry.lastError().text()));
       }
      // return "no";

        QJsonDocument doc(recordObject);
        QString qstr_test = QString::fromUtf8(doc.toJson().data());
            qDebug() << doc.toJson();
            return  qstr_test;
}
QString DBMan::isloginDataBase(){
    QString quer=QString("select * from LoginDataBase");
       QSqlQuery qry;
       qDebug() << quer;
       if(qry.exec(quer)){
          // qDebug()<< qry.value(qry.record().indexOf("user_id")).toString();;
              if(qry.next())
              {
                  qDebug() << qry.value(qry.record().indexOf("userid")).toString();
                       return qry.value(qry.record().indexOf("userid")).toString();
              }else{
                  return "no";
              }
       }else{
       //qFatal("Failed to query database: %s", qPrintable(qry.lastError().text()));
       }
       return "no";
}
void DBMan::insertContactsDataBase(QString name){
       QSqlQuery qry;
       qDebug() << "Message contentType:" << name;
       QString querys=QString("INSERT INTO Contacts VALUES('%1')").arg(name);
       if(qry.exec()){

       }else{
       qFatal("Failed to query database: %s", qPrintable(qry.lastError().text()));
       }
}
