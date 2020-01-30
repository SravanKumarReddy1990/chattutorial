#ifndef ECHOCLIENT_H
#define ECHOCLIENT_H

#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSqlQuery>
#include <QSqlError>
class EchoClient : public QObject
{
    Q_OBJECT
public:
    explicit EchoClient(const QUrl &url, bool debug = false, QObject *parent = nullptr);

  //  Q_SIGNAL void insertContactsDataBase( QString & reply);


Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void onConnected();
    void onTextMessageReceived(QString message);
public slots:
    void onSentTextMessage(QString message);

private:
    QWebSocket m_webSocket;
    QUrl m_url;
    bool m_debug;
};

#endif // ECHOCLIENT_H
