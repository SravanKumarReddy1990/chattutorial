/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QGuiApplication>
#include <QStandardPaths>
#include <QSqlDatabase>
#include <QSqlError>
#include <QtQml>
#include <QDebug>
#include "sqlcontactmodel.h"
#include "sqlconversationmodel.h"
#include "dbman.h"
#include "gps.h"
#include <customtimer.h>
#include "notificationclient.h"
#include <QObject>
#include <QCoreApplication>
#include <QtCore>
#include <QAndroidJniEnvironment>
#include <QAndroidJniObject>

#define JCLASS_Name "com/bsmaps/chat/NotificationClient"

 NotificationClient notificationclient;


class QtAndroidRunnerPriv
{

public:
    jclass clazz;
    //jmethodID tick;

   // static QtAndroidRunnerPriv* qtan;
  // Q_SIGNAL void setNames(QString name);
   // virtual ~QtAndroidRunnerPriv() {};
    explicit QtAndroidRunnerPriv() {
        QAndroidJniEnvironment env;

        clazz = env->FindClass(JCLASS_Name);
        //QAndroidJniObject m_javaClass = QAndroidJniObject (JCLASS_Name);
        //jclass objectClass = env->GetObjectClass(m_javaClass.object<jobject>());
        /* QAndroidJniObject only works for
         * core library and cached classes like
         * QtActivity / QtApplication.
         *
         * Therefore, it need to use the raw API
         * and must be executed within the JNI_onLoad()
         * call.
         *
         */

        if (!clazz)
        {
            qCritical() << "Can't find class : " << JCLASS_Name << ". Did init() be called within JNI_onLoad?";
        } else {

            //tick = env->GetStaticMethodID(clazz,"post","()V");
           // if (tick ==0) {
           //     qCritical() << "Failed to obtain the method : tick";
           // }

            JNINativeMethod methods[] =
            {
                {"invoke", "(Ljava/lang/String;)V", reinterpret_cast<void*>(invoke)},
            };

            // Register the native methods.
            int numMethods = sizeof(methods) / sizeof(methods[0]);
            if (env->RegisterNatives(clazz, methods, numMethods) < 0) {
                if (env->ExceptionOccurred()) {
                    env->ExceptionDescribe();
                    env->ExceptionClear();
                    qCritical() << "Exception in native method registration";
                }
            }

        }
       // qtan=this;
    }
    static void invoke(JNIEnv  *env, jobject obj,jstring text) {
        qDebug() << text;
       const char *  path = env->GetStringUTFChars( text, NULL ) ;
qDebug() << " invoke jstring " <<QString::fromLocal8Bit(path);
QString name = QString::fromLocal8Bit(path);
notificationclient.setNames(name);
    }
};
#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>
#include <jni.h>
#include <echoclient.h>
JNIEXPORT
jint
JNI_OnLoad(JavaVM* vm, void*) {
    Q_UNUSED(vm);

    QtAndroidRunnerPriv qtAndroidRunnerPriv;
 // QObject::connect(&qtAndroidRunnerPriv, SIGNAL(setNames), &notificationclient,SLOT(setNames));

    return JNI_VERSION_1_6;
}


static void connectToDatabase()
{
     qDebug() << "Connected Database" ;
    QSqlDatabase database = QSqlDatabase::database();
    if (!database.isValid()) {
        database = QSqlDatabase::addDatabase("QSQLITE");
        if (!database.isValid()){
            qFatal("Cannot add database: %s", qPrintable(database.lastError().text()));
        }
    }

    const QDir writeDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    //qDebug() << writeDir.absolutePath() <<"hi";
    if (!writeDir.mkpath(".")){
        qFatal("Failed to create writable directory at %s", qPrintable(writeDir.absolutePath()));
    }

    // Ensure that we have a writable location on all devices.
    const QString fileName = writeDir.absolutePath() + "/chat-database.sqlite3";
    // When using the SQLite driver, open() will create the SQLite database if it doesn't exist.
    database.setDatabaseName(fileName);
    if (!database.open()) {
        qFatal("Cannot open database: %s", qPrintable(database.lastError().text()));
        QFile::remove(fileName);
    }
}

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    connectToDatabase();

    qmlRegisterType<SqlContactModel>("io.qt.examples.chattutorial", 1, 0, "SqlContactModel");
    qmlRegisterType<SqlConversationModel>("io.qt.examples.chattutorial", 1, 0, "SqlConversationModel");



    QQmlApplicationEngine engine;
    //CustomTimer customTimer;
    //customTimer.startTimers();
    //QtWebEngine::initialize();
EchoClient client(QUrl(QStringLiteral("ws")), true);
//client.onOpen();
engine.rootContext()->setContextProperty("echoclient",&client);

    engine.rootContext()->setContextProperty("notificationClient",&notificationclient);
    DBMan dbm;
    dbm.createDatabase();
    engine.rootContext()->setContextProperty("dbm",&dbm);
    Gps gps;
    engine.rootContext()->setContextProperty("gpss",&gps);
    QString serverurl("http://resumecollection.orgfree.com/streamservices/");
    engine.rootContext()->setContextProperty("serverurl",serverurl);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

