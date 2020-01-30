/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.9
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.1
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.0
import QtWebView 1.1
ApplicationWindow {
    id: window
    width: 540
    height: 960
    visible: true
    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: ContactPage {}
    }
    Connections {
            target: GUI
            onBack: console.log("back")
        }
    Dialog {
        id:maindialog
          visible: false
          title: "REGISTER USERS"
          width: 540
          height: 500
          contentItem: Rectangle {
              color: "lightskyblue"
              anchors.fill: parent
              TextField{
                id:userid
                placeholderText: "ENTER USERID:"
                y:closebutton.y -150
                x:closebutton.x-80
              }
              TextField{
                id:username
                placeholderText: "ENTER USERNAME:"
                y:closebutton.y -150+userid.height+10
                x:closebutton.x-80
              }
              TextField{
                id:mobileno
                placeholderText: "ENTER MOBILE NUMBER:"
                y:closebutton.y -150+userid.height+10+username.height+10
                x:closebutton.x-80
              }

                  Button{
                    id:closebutton
                    text:"REGISTER USER"
                    anchors.centerIn: parent
                    onClicked: {
                        if(userid.text.length==0){
                            return;
                        }
                        if(username.text.length==0){
                            return;
                        }
                        if(mobileno.text.length==0){
                            return;
                        }
                        console.log(gpss.replaceCharPlus(userid.text)+" "+gpss.replaceCharPlus(username.text)+" "+gpss.replaceCharPlus(mobileno.text))
                        registerUser();
                        //console.log("Data Stored")
                        //maindialog.close();
                      }

                  }
                  Component.onCompleted: {
                        webView.url = "file:///assets/layers.html";
                  }
                  WebView {
                       id: webView
                       y:closebutton.y +userid.height+10
                       x:closebutton.x-80
                       height: 250
                       width: 150
                       visible: true
                       onLoadingChanged: {
                            if (loadRequest.errorString){
                                console.error(loadRequest.errorString);
                            }
                        }
                 }

          }
      }
}
