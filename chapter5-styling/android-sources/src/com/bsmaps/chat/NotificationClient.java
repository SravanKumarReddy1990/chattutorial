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

package com.bsmaps.chat;

import android.app.Notification;
import android.app.NotificationManager;
import android.content.Context;
import android.content.Intent;

public class NotificationClient extends org.qtproject.qt5.android.bindings.QtActivity
{
    private static NotificationManager m_notificationManager;
    private static Notification.Builder m_builder;
    private static NotificationClient m_instance;
    public static String tvresult="";
    public static AudioDownloadListener audioDownloadListener;
    public NotificationClient()
    {
        m_instance = this;
    }
@Override
public void onBackPressed() {
  // Log.d("CDA", "onBackPressed Called");
  super.onBackPressed();
              this.finish();
}
    public static String notify(String s)
    {
        if (m_notificationManager == null) {
            m_notificationManager = (NotificationManager)m_instance.getSystemService(Context.NOTIFICATION_SERVICE);
            m_builder = new Notification.Builder(m_instance);
            m_builder.setSmallIcon(R.drawable.icon);
            m_builder.setContentTitle("A message from Qt!");

        }

        m_builder.setContentText(s);
        m_notificationManager.notify(1, m_builder.build());
        return tvresult;
    }
public static String getValues(String s)
{
    return tvresult;
}
public static void openServerCamActivity(String s) {

            Intent intent = new Intent(m_instance, MainActivitys.class);
            m_instance.startIntent(intent);
}
public static void openClientCamActivity(String s) {

Intent intent = new Intent(m_instance, MainActivityss.class);
m_instance.startIntent(intent);
}
    public static void openSecondActivity(String s) {
                audioDownloadListener= new AudioDownloadListener(){
                                    @Override
                                    public void onAudioDownloaded(final String text) {

//                                            Runnable runnable = new Runnable () {
//                                                public void run() {
//                                                    invoke(tvresult);
//                                                };
//                                            };
                                           // m_instance.runOnUiThread(runnable);
                                    }
                                };
                Intent intent = new Intent(m_instance, ScanActivity.class);
                m_instance.startIntent(intent);
    }
    public static native void invoke(String text);

    public void startIntent(Intent intent){
        startActivity(intent);
    }
}
