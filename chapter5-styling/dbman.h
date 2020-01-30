#ifndef DBMAN_H
#define DBMAN_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QSqlQuery>
#include <QSqlRecord>
#include <echoclient.h>
class DBMan : public QObject
{
    Q_OBJECT

public:
    explicit DBMan(QObject *parent = 0);

public Q_SLOTS:
    void insertContactsDataBase(QString name);

public slots:
    void createDatabase();
    void loginDataBase(QString userid,QString password,QString phoneno);
    QString isloginDataBase();

};

#endif // DBMAN_H
