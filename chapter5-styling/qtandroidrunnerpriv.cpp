#include "qtandroidrunnerpriv.h"

QtAndroidRunnerPriv::QtAndroidRunnerPriv(QObject *parent)
    : QObject(parent)
{
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
        qDebug() << "Can't find class : " << JCLASS_Name << ". Did init() be called within JNI_onLoad?";
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
}

void QtAndroidRunnerPriv::invoke(JNIEnv  *env, jobject obj,jstring text) {
    qDebug() << text;
   const char *  path = env->GetStringUTFChars( text, NULL ) ;
qDebug() << " invoke jstring " <<QString::fromLocal8Bit(path);
QString name = QString::fromLocal8Bit(path);
emit setNames(name);

}
