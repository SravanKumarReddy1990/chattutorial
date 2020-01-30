TEMPLATE = app

QT += qml quick sql positioning androidextras xml websockets
CONFIG += c++11

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android-sources

HEADERS += sqlcontactmodel.h \
    echoclient.h \
    sqlconversationmodel.h \
    dbman.h\
    gps.h \
    customtimer.h\
    notificationclient.h

SOURCES += main.cpp \
    echoclient.cpp \
    sqlcontactmodel.cpp \
    sqlconversationmodel.cpp \
    dbman.cpp\
    gps.cpp \
    customtimer.cpp\
    notificationclient.cpp

#OTHER_FILES += \
#    android-sources/src/com/bsmaps/chat/NotificationClient.java \
#    android-sources/src/com/bsmaps/chat/SecondActivity.java \
#    android-sources/res/layout/second_activity.xml \
#    android-sources/AndroidManifest.xml

RESOURCES += \
    qml.qrc \
    ../shared/shared.qrc

target.path = $$[QT_INSTALL_EXAMPLES]/quickcontrols2/chattutorial/chapter5-styling
INSTALLS += target

OTHER_FILES += \
    android-sources/AndroidManifest.xml \
    android-sources/gradle/wrapper/gradle-wrapper.jar \
    android-sources/gradlew \
    #android-sources/res/values/libs.xml \
    android-sources/build.gradle \
    android-sources/gradle/wrapper/gradle-wrapper.properties \
    android-sources/gradlew.bat\
    android-sources/src/com/bsmaps/chat/NotificationClient.java \
    android-sources/src/com/bsmaps/chat/SecondActivity.java \
    android-sources/src/com/bsmaps/chat/ScanActivity.java \
    android-sources/src/com/bsmaps/chat/MainActivity.java \
    android-sources/src/com/bsmaps/chat/AudioDownloadListener.java \
    android-sources/src/com/bsmaps/chat/MyCameraView.java \
    android-sources/src/com/bsmaps/chat/MainActivitys.java \
    android-sources/src/com/bsmaps/chat/MyServerThread.java \
    android-sources/src/com/bsmaps/chat/MyClientThread.java \
    android-sources/src/com/bsmaps/chat/MyCameraViewss.java \
    android-sources/src/com/bsmaps/chat/MainActivityss.java \
    android-sources/src/com/bsmaps/chat/MyHandler.java \
    android-sources/res/layout/second_activity.xml\
    android-sources/res/layout/activity_main.xml\
    android-sources/res/layout/activity_mains.xml\
    android-sources/res/layout/activity_mainss.xml\
    android-sources/res/layout/activity_scan.xml\
    android-sources/assets/layers.html \
    android-sources/assets/jquery-1.11.2.min.js \
    android-sources/assets/index_new.js \
    android-sources/assets/ol.css \
    android-sources/assets/ol.js \
