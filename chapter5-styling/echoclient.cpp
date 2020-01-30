#include "echoclient.h"
#include <QtCore/QDebug>

QT_USE_NAMESPACE

EchoClient::EchoClient(const QUrl &url, bool debug, QObject *parent) :
    QObject(parent),
    m_url(url),
    m_debug(debug)
{
    if (m_debug)
        qDebug() << "WebSocket server:" << url;
    connect(&m_webSocket, &QWebSocket::connected, this, &EchoClient::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &EchoClient::closed);
    m_webSocket.open(QUrl("ws://part1290.herokuapp.com/chat/sravan"));
}

void EchoClient::onConnected()
{
    if (m_debug)
        qDebug() << "WebSocket connected";
    connect(&m_webSocket, &QWebSocket::textMessageReceived,
            this, &EchoClient::onTextMessageReceived);
   // m_webSocket.sendTextMessage(QStringLiteral("Hello, world!"));
}

void EchoClient::onTextMessageReceived(QString message)
{
    if (m_debug)
        qDebug() << "Message received:" << message;
    //m_webSocket.close();
//    QStringList propertyNames;
//    QStringList propertyKeys;
//    QString strReply = (QString)reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(message.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    QString contenttype = jsonObject["contentType"].toString();
    if(contenttype.compare(QString("useradd"),Qt::CaseSensitive)==0){

         QString name = jsonObject["content"].toString();
         QString querys=QString("select * from Contacts where name='%1'").arg(name);
         qDebug() << "Message contentType:" << name;
            QSqlQuery qrys;
            if(qrys.exec(querys)){
               // qDebug()<< qry.value(qry.record().indexOf("user_id")).toString();;
                   if(!qrys.next())
                   {
        QSqlQuery qry;
        QString queryss=QString("INSERT INTO Contacts VALUES('%1')").arg(name);
        if(qry.exec(queryss)){

        }else{
        qFatal("Failed to query database: %s", qPrintable(qry.lastError().text()));
        }
                   }
            }
    }
//    foreach (const QJsonValue & value, jsonArray) {
//        QJsonObject obj = value.toObject();
//        propertyNames.append(obj["PropertyName"].toString());
//        propertyKeys.append(obj["key"].toString());
//    }

}
void EchoClient::onSentTextMessage(QString message)
{
    if (m_debug)
        qDebug() << "Message Sent:" << message;
    m_webSocket.sendTextMessage(message);
}
