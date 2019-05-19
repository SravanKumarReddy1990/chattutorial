#ifndef TIMER_H
#define TIMER_H

#include <QTimer>
#include <QDebug>
class CustomTimer : public QObject
{
    Q_OBJECT

public:
    explicit CustomTimer(QObject *parent = 0);

public slots:
    void startTimers();
    void stopTimers();
    void update();
private:
    QTimer *timer;
};

#endif // TIMER_H
