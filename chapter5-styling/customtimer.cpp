#include "customtimer.h"

CustomTimer::CustomTimer(QObject *parent): QObject(parent)
{

}
void CustomTimer::startTimers(){
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000);
}
void CustomTimer::stopTimers(){
    timer->stop();
}
void CustomTimer::update(){
qDebug()<<"aksjcna asnak";
}
