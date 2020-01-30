#include "gps.h"

Gps::Gps(QObject *parent): QObject(parent)
{
source = QGeoPositionInfoSource::createDefaultSource(this);
//if (source) {
    connect(source, SIGNAL(positionUpdated(QGeoPositionInfo)),
            this, SLOT(positionUpdated(QGeoPositionInfo)));
//}
}
void Gps::startUpdates(){
    qDebug() << "Position updating :" ;
source->startUpdates();
}
void Gps::stopUpdates(){
source->stopUpdates();
}


QString Gps::replaceChar(QString st){
        return st.replace("\"","");
}
QString Gps::replaceCharPlus(QString st){
        return st.replace(" ","+");
}
QString Gps::replaceCharPolygon(QString st){
    st=st.replace("MULTIPOLYGON(((","");
        return st.replace("POLYGON Z ((","");
}

QString Gps::replaceCharPolygonend(QString st){
    st=st.replace(")))","");
        return st.replace("))","");
}
void Gps::positionUpdated(const QGeoPositionInfo &info)
{
    qgeo=info;
   // if (qgeo.isValid())
   //  {
     // Get the current location coordinates
     QGeoCoordinate geoCoordinate = qgeo.coordinate();
     qreal latitude = geoCoordinate.latitude();
     qreal longitude = geoCoordinate.longitude();
     qDebug() << "Position updated:" << info;
     QString lat= QString("%1,%2").arg(latitude).arg(longitude);
     emit replyAvailable(lat);
     //return lat.toLocal8Bit().constData();
    //}else{
    //    QString text=QString("Location Not Found");
    //    emit replyAvailable(text);
        //return text.toLocal8Bit().constData();
    //}


}
