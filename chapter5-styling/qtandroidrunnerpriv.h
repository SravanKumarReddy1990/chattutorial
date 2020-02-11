#ifndef QTANDROIDRUNNERPRIV_H
#define QTANDROIDRUNNERPRIV_H
#include <QObject>
#include <QAndroidJniEnvironment>
#include <QAndroidJniObject>
#include <QDebug>
#define JCLASS_Name "com/bsmaps/chat/NotificationClient"


class QtAndroidRunnerPriv : public QObject
{
    Q_OBJECT

public:
    jclass clazz;
    explicit QtAndroidRunnerPriv(QObject * parent=nullptr);
    static void invoke(JNIEnv  *env, jobject obj,jstring text);

    Q_SIGNAL static void setNames(QString name);

};
#endif // QTANDROIDRUNNERPRIV_H
