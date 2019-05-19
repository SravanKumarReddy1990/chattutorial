/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtAndroidExtras module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "notificationclient.h"
#include <QDomElement>
#include <QDomAttr>
#include <QDomNode>
#include <QtAndroidExtras/QAndroidJniObject>
#include <QDebug>
NotificationClient::NotificationClient(QObject *parent)
    : QObject(parent)
{
    connect(this, SIGNAL(notificationChanged()), this, SLOT(updateAndroidNotification()));
}

void NotificationClient::setNotification(const QString &notification)
{
    if (m_notification == notification)
        return;

    m_notification = notification;
    emit notificationChanged();
}

QString NotificationClient::notification() const
{
    return m_notification;
}

void NotificationClient::updateAndroidNotification()
{
    QAndroidJniObject javaNotification = QAndroidJniObject::fromString(m_notification);
    QAndroidJniObject stringNumber =QAndroidJniObject::callStaticObjectMethod("com/bsmaps/chat/NotificationClient",
                                       "notify",
                                       "(Ljava/lang/String;)Ljava/lang/String;",
                                       javaNotification.object<jstring>());
    qDebug() << stringNumber.toString();
}
void NotificationClient::getValues(){
    QAndroidJniObject javaNotification = QAndroidJniObject::fromString("Hi");
    QAndroidJniObject stringNumber =QAndroidJniObject::callStaticObjectMethod("com/bsmaps/chat/NotificationClient",
                                       "getValues",
                                       "(Ljava/lang/String;)Ljava/lang/String;",
                                       javaNotification.object<jstring>());
    qDebug() << stringNumber.toString();
    QDomDocument d;
      d.setContent(stringNumber.toString());
      QDomNode n = d.firstChild();
      while (!n.isNull()) {
          if (n.isElement()) {
              QDomElement e = n.toElement();
              QDomAttr uid = e.attributeNode("uid");
              qDebug() << uid.value() << endl;
              QString suid=uid.value();
              QDomAttr name = e.attributeNode("name");
              qDebug() << name.value() << endl;
              QString sname=name.value();
              QDomAttr gender = e.attributeNode("gender");
              qDebug() << gender.value() << endl;
              QString sgender=gender.value();
              QDomAttr yob = e.attributeNode("yob");
              qDebug() << yob.value() << endl;
              QString syob=yob.value();
              QDomAttr co = e.attributeNode("co");
              qDebug() << co.value() << endl;
              QString sco=co.value();
              QDomAttr house = e.attributeNode("house");
              qDebug() << house.value() << endl;
              QString shouse=house.value();
              QDomAttr vtc = e.attributeNode("vtc");
              qDebug() << vtc.value() << endl;
              QString svtc=vtc.value();
              QDomAttr po = e.attributeNode("po");
              qDebug() << po.value() << endl;
              QString spo=po.value();
              QDomAttr dist = e.attributeNode("dist");
              qDebug() << dist.value() << endl;
              QString sdist=dist.value();
              QDomAttr subdist = e.attributeNode("subdist");
              qDebug() << subdist.value() << endl;
              QString ssubdist=subdist.value();
              QDomAttr state = e.attributeNode("state");
              qDebug() << state.value() << endl;
              QString sstate=state.value();
              QDomAttr pc = e.attributeNode("pc");
              qDebug() << pc.value() << endl;
              QString spc=pc.value();
               replyAdhar(suid+","+sname+","+sgender+","+syob+","+sco+","+shouse+","+svtc+","+spo+","+sdist+","+ssubdist+","+sstate+","+spc);
             // break;
          }
          n = n.nextSibling();
      }

}
void NotificationClient::opensecondActivity()
{
    QAndroidJniObject javaNotification = QAndroidJniObject::fromString("Hi");
    QAndroidJniObject::callStaticMethod<void>("com/bsmaps/chat/NotificationClient",
                                       "openSecondActivity",
                                       "(Ljava/lang/String;)V",
                                       javaNotification.object<jstring>());
}

void NotificationClient::openservercamActivity(){
    QAndroidJniObject javaNotification = QAndroidJniObject::fromString("Hi");
    QAndroidJniObject::callStaticMethod<void>("com/bsmaps/chat/NotificationClient",
                                       "openServerCamActivity",
                                       "(Ljava/lang/String;)V",
                                       javaNotification.object<jstring>());
}
void NotificationClient::openclientcamActivity(){
    QAndroidJniObject javaNotification = QAndroidJniObject::fromString("Hi");
    QAndroidJniObject::callStaticMethod<void>("com/bsmaps/chat/NotificationClient",
                                       "openClientCamActivity",
                                       "(Ljava/lang/String;)V",
                                       javaNotification.object<jstring>());
}
