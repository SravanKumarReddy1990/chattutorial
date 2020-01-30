import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtLocation 5.3;
import QtPositioning 5.5
import QtWebSockets 1.0
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
    //id: itemname
    //color: "#ca5e5e"

            Plugin {
               id: osmMapPlugin
               name: "osm"
               PluginParameter {
                  name: "osm.mapping.host"
                  value: "http://tile.openstreetmap.org/"
               }
               PluginParameter {
                  name: "osm.mapping.providersrepository.disabled"
                  value: true
               }
            }

            Map{
              id:map
              anchors.fill: parent
              plugin: osmMapPlugin
              gesture.enabled: true
              zoomLevel: 14
              //activeMapType: supportedMapTypes[7]
                      MapPolygon {
                               id:vmappolygon
                               //color: Qt.rgba(255, 0, 0, 0.1)
                               border.color: "red"
                               border.width: 2
                               path: []
                     }
                      MapPolygon {
                               id:amappolygon
                               //color: Qt.rgba(255, 0, 0, 0.1)
                               border.color: "green"
                               border.width: 2
                               path: []
                     }
                      MapPolygon {
                               id:pmappolygon
                               //color: Qt.rgba(255, 0, 0, 0.1)
                               border.color: "blue"
                               border.width: 2
                               path: []
                     }

              MapCircle {
                          id: pointt
                          radius: 100
                          color: "#5B2C6F"
                          border.color: "#EC7063"
                          border.width: 2
                          smooth: true
                          opacity: 0.25
                          center: QtPositioning.coordinate(0.00, 0.00);
                      }
            }

            PositionSource {
                    id: positionSource
                    updateInterval: 3000
                    active: true

                    onPositionChanged: {
                        var coord = positionSource.position.coordinate;
                        console.log("Coordinate:", coord.longitude, coord.latitude);
                        resultHandler(coord.latitude+","+coord.longitude)
                        echoclient.onSentTextMessage('{"status":"sravan","contentType":"loc","from":"sravan","to":"all","content":"'+coord.longitude+','+coord.latitude+'"}');
                    }

                    onSourceErrorChanged: {
                        if (sourceError == PositionSource.NoError)
                            return

                        console.log("Source error: " + sourceError)
                        stop()
                    }
            }

    Component.onCompleted: {
        positionSource.start();
       // gpss.startUpdates();
       // gpss.replyAvailable.connect(resultHandler);
      }

    function resultHandler(result) {
        //gpss.stopUpdates();
        console.log("from qml resultHandler "+result)
        var latlong= result.toString().split(',');
        pointt.center = QtPositioning.coordinate(latlong[0], latlong[1]);
        //loadPolygon("v",vmappolygon, "http://sravankumar1990.herokuapp.com/gettnvillagenames.php?lat="+latlong[0]+"&long="+latlong[1]);
        //loadPolygon("a",amappolygon, "http://sravankumar1990.herokuapp.com/getassemblyname.php?lat="+latlong[0]+"&long="+latlong[1]);
        //loadPolygon("p",pmappolygon, "http://sravankumar1990.herokuapp.com/getparliamentname.php?lat="+latlong[0]+"&long="+latlong[1]);

        map.center.latitude=latlong[0];
        map.center.longitude=latlong[1];

    }
}
