#ifndef GPS_H
#define GPS_H

#include <QGeoPositionInfoSource>
#include <QGeoPositionInfo>
#include <QDebug>

class Gps : public QObject
{
    Q_OBJECT

public:
    explicit Gps(QObject *parent = 0);
    Q_SIGNAL void replyAvailable(const QString & reply);

public slots:
    QString replaceChar(QString st);
    QString replaceCharPlus(QString st);
    QString replaceCharPolygon(QString st);
    QString replaceCharPolygonend(QString st);
    void startUpdates();
    void stopUpdates();
private slots:
    void positionUpdated(const QGeoPositionInfo &info);
private:
    QGeoPositionInfo qgeo;
    QGeoPositionInfoSource *source;
};

#endif // GPS_H
