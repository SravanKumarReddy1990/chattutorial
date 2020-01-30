#include "dbman.h"

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
