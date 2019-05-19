

import QtQuick 2.9
import QtQuick.Controls 2.2

import io.qt.examples.chattutorial 1.0

Page {
    id: root
    readonly property bool inPortrait: window.width < window.height

    Drawer {
        id: drawer

        y: overlayHeader.height
        width: window.width / 2
        height: window.height - overlayHeader.height

        modal: inPortrait
        interactive: inPortrait
        position: inPortrait ? 0 : 1
        visible: !inPortrait

        ListView {
            id: listView1
            anchors.fill: parent

            headerPositioning: ListView.OverlayHeader
            header: Pane {
                id: header
                z: 2
                width: parent.width

                contentHeight: logo.height

                Image {
                    id: logo
                    width: parent.width
                    source: "Albert_Einstein.png"
                    fillMode: implicitWidth > width ? Image.PreserveAspectFit : Image.Pad

                }

                MenuSeparator {
                    parent: header
                    width: parent.width
                    anchors.verticalCenter: parent.bottom
                    visible: !listView1.atYBeginning
                }
            }

            footer: ItemDelegate {
                id: footer
                text: qsTr("Footer")
                width: parent.width

                MenuSeparator {
                    parent: footer
                    width: parent.width
                    anchors.verticalCenter: parent.top
                }
            }

            model: recipeModel
               ListModel {
                          id: recipeModel
                          ListElement {
                              name: "GPS"
                              url: "qrc:///gps.qml"
                          }
                          ListElement {
                              name: "Bye"
                              url: "qrc:///register.qml"
                          }
                          ListElement {
                              name: "Server Camera"
                              url: "qrc:///register.qml"
                          }

                          ListElement {
                              name: "Client Camera"
                              url: "qrc:///register.qml"
                          }
                }
            delegate: ItemDelegate {
                text: name
                width: parent.width
                onClicked: {
                    console.log("name: "+name)
                    drawer.close()
                    if(name == "Bye"){
                    notificationClient.opensecondActivity();
                    }else if(name == "Server Camera"){
                        notificationClient.openservercamActivity();
                    }else if(name == "Client Camera"){
                        notificationClient.openclientcamActivity();
                    }else{
                    root.StackView.view.push(url, {inConversationWith : name })
                    }
                }
            }

            ScrollIndicator.vertical: ScrollIndicator { }
        }
    }
    header: ChatToolBar {
        id: overlayHeader
        Button{
        id:opendraw
        text: "menu"
        onClicked: {
        drawer.open();
        }
        }
        Label {
            text: qsTr("Contacts")
            font.pixelSize: 20
            anchors.centerIn: parent
        }
    }

    ListView {
        id: listView
        anchors.fill: parent
        topMargin: 48
        leftMargin: 48
        bottomMargin: 48
        rightMargin: 48
        spacing: 20
        model: SqlContactModel {}
        delegate: ItemDelegate {
            text: model.display
            width: listView.width - listView.leftMargin - listView.rightMargin
            height: avatar.implicitHeight
            leftPadding: avatar.implicitWidth + 32
            onClicked: root.StackView.view.push("qrc:/ConversationPage.qml", { inConversationWith: model.display })

            Image {
                id: avatar
                source: "qrc:/" + model.display.replace(" ", "_") + ".png"
            }
        }
    }
    Component.onCompleted: {
        var userid=dbm.isloginDataBase();
        console.log("user details : "+userid)
        if(userid === "no"){
            console.log("user logged in : ")
                //maindialog.close();
            notificationClient.replyAdhar.connect(resultHandler);
            notificationClient.opensecondActivity();
        }
    }
    function resultHandler(result) {
        console.log("Contact Page"+result);
        var res=result.split(',');
        var adharno=res[0],name=res[1],gender=res[2],yob=res[3],co=res[4],house=res[5],vtc=res[6],po=res[7],dist=res[8],subdist=res[9],state=res[10],pc=res[11];
        registerUser(adharno,name,gender,yob,co,house,vtc,po,dist,subdist,state,pc);
    }
    function registerUser(adharno,name,gender,yob,co,house,vtc,po,dist,subdist,state,pc){
       var http = new XMLHttpRequest()
       var url = serverurl+"registeruser.php?adharno="+gpss.replaceCharPlus(adharno)+"&name="+gpss.replaceCharPlus(name)+
       "&gender="+gender+"&yob="+yob+"&co="+gpss.replaceCharPlus(co)+"&house="+gpss.replaceCharPlus(house)
        +"&vtc="+gpss.replaceCharPlus(vtc)+"&po="+gpss.replaceCharPlus(po)+"&dist="+gpss.replaceCharPlus(dist)
        +"&subdist="+gpss.replaceCharPlus(subdist)+"&state="+gpss.replaceCharPlus(state)+"&pc="+gpss.replaceCharPlus(pc)

       console.log(url)
       http.open("GET", url, true);
       //http.setRequestHeader('Content-Type', 'application/json;charset=UTF-8');
       http.onreadystatechange = function() {
           if(http.readyState == 4 && http.status == 200) {
               console.log(http.responseText)
               var params=JSON.parse(http.responseText)
               if(params.status === 1){
                   //dbm.loginDataBase(gpss.replaceCharPlus(userid.text),gpss.replaceCharPlus(username.text),gpss.replaceCharPlus(mobileno.text))
                   // console.log("Data Stored")
                   // maindialog.close();
               }
            }
       }
       http.send()
    }
}

