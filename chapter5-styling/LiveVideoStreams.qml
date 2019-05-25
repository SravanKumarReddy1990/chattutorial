import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtLocation 5.3;
import QtPositioning 5.5
import QtWebView 1.1
Page {
    id:root
    property var locationData:({})
    //locationData.coordinate={};
    property string inConversationWith
    header: ChatToolBar {
        ToolButton {
            text: qsTr("Back")
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            onClicked: root.StackView.view.pop()
        }

        Label {
            id: pageTitle
            text: inConversationWith
            font.pixelSize: 20
            anchors.centerIn: parent
        }
    }

    WebView {
         id: webView
         height: parent.height
         width: parent.width
         visible: true
         onLoadingChanged: {
              if (loadRequest.errorString){
                  console.error(loadRequest.errorString);
              }
          }
         url:"https://ramureddy1990.herokuapp.com"
   }
}
