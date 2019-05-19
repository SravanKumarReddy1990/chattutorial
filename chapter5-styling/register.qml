import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1
Rectangle {
    id: itemname
    color: "#ca5e5e"
    width: 640
    height: 480
        TextEdit {
            id: textEdit1
            x: 8
            y: 72
            width: 130
            height: 50
            text: qsTr("USERID:")
            selectionColor: "#f3f2f2"
            font.pixelSize: 30
        }

        TextEdit {
            id: textEdit2
            x: 8
            y: 169
            width: 130
            height: 50
            text: qsTr("PASSWORD:")
            font.pixelSize: 25
        }
        TextField {
            x: 170
            y: 48
            width: 350
            height: 68
            id: useridinput
                    placeholderText: "ENTER USERID"
                    text: ""
                    style: TextFieldStyle {
                        textColor: "black"
                        background: Rectangle {
                            radius: 5
                            color: "orange"
                            implicitWidth: 100
                            implicitHeight: 24
                            border.color: "#333"
                            border.width: 1
                        }
                    }
                }
        TextField {
            x: 170
            y: 146
            width: 350
            height: 66
            id: passwordinput
                    placeholderText: "ENTER PASSWORD"
                    text: ""
                    style: TextFieldStyle {
                        textColor: "black"
                        background: Rectangle {
                            radius: 5
                            color: "orange"
                            implicitWidth: 100
                            implicitHeight: 24
                            border.color: "#333"
                            border.width: 1
                        }
                    }
                }
        TextEdit {
            id: textEdit3
            x: 8
            y: 243
            width: 130
            height: 50
            text: qsTr("EMAIL ID:")
            font.pixelSize: 25
        }
        TextField {
            x: 170
            y: 234
            width: 350
            height: 68
            id: emailinput
                    placeholderText: "ENTER EMAILID"
                    text: ""
                    style: TextFieldStyle {
                        textColor: "black"
                        background: Rectangle {
                            radius: 5
                            color: "orange"
                            implicitWidth: 100
                            implicitHeight: 24
                            border.color: "#333"
                            border.width: 1
                        }
                    }
                }

            Button {
                id:regbutton
                x: 145
                y: 382
                width: 300
                height: 74
                text: "REGISTER"
                    onClicked: { //login.loginbuttonClicked("logbutton");
                        request('http://resumecollection.orgfree.com/webservices/registeruser.php?names="+val.toLatin1()+"&loginid="+val.toLatin1()+"&pass=akscnasc&emailid=asjdj&mobileno=12365478', function (o) {
                                               var d = eval('new Object(' + o.responseText + ')');
                                               regbutton.text = d.msg
                        });
                       // pageLoader.source = "chat.qml";
                     }
                    function request(url, callback) {
                           var xhr = new XMLHttpRequest();
                           xhr.onreadystatechange = (function(myxhr) {
                               return function() {
                                   callback(myxhr);
                               }
                           })(xhr);
                           xhr.open('GET', url, true);
                           xhr.send('');
                       }
                }


    Component.onCompleted: {
      //  gps.replyAvailable.connect(resultHandler);
    }

}
