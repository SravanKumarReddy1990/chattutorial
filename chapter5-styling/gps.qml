import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtLocation 5.3;
import QtPositioning 5.5
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
                          radius: 1000
                          color: "#5B2C6F"
                          border.color: "#EC7063"
                          border.width: 2
                          smooth: true
                          opacity: 0.25
                          center: QtPositioning.coordinate(0.00, 0.00);
                      }
            }


            Component {
                  id: pointDelegate
                  MapCircle {
                              id: point
                              radius: 1000
                              color: "#46a2da"
                              border.color: "#190a33"
                              border.width: 2
                              smooth: true
                              opacity: 0.25
                              center: locationData.coordinate
                          }
              }
    Component.onCompleted: {
        gpss.startUpdates();
        gpss.replyAvailable.connect(resultHandler);
      }
    function loadPolygon(type,polygonid,url){
                        var http = new XMLHttpRequest()
                        //console.log(url)
                        http.open("GET", url, true);
                        //http.setRequestHeader('Content-Type', 'application/json;charset=UTF-8');
                        http.onreadystatechange = function() {
                            if(http.readyState == 4 && http.status == 200) {
                                //console.log(http.responseText)
                                var resp= JSON.parse(http.responseText);
                                var geom=resp[0].geom;
                                geom=gpss.replaceCharPolygon(geom);
                                geom=gpss.replaceCharPolygonend(geom);
                               // console.log(geom)
                                var geo=geom.split(",");
                                //var c=[];
                                for(var n=0;n<geo.length;n++){
                                    var cood=geo[n];
                                    var coord=cood.split(" ");

                                    //c.push({latitude:coord[1],longitude:coord[0]});

                                     polygonid.addCoordinate(QtPositioning.coordinate(coord[1],coord[0]))
                                    //map.center.latitude=coord[1];
                                    //map.center.longitude=coord[0];
                                }
                                //var jsonObj=JSON.stringify(c);
                                //console.log(jsonObj);
                                //polygonid.path = c;
                                console.log("path Set")
                            }
                        }
                        http.send()
    }
    function resultHandler(result) {
        gpss.stopUpdates();
        console.log("from qml resultHandler "+result)
        var latlong= result.toString().split(',');
        pointt.center = QtPositioning.coordinate(latlong[0], latlong[1]);
        loadPolygon("v",vmappolygon, "http://sravankumar1990.herokuapp.com/gettnvillagenames.php?lat="+latlong[0]+"&long="+latlong[1]);
        loadPolygon("a",amappolygon, "http://sravankumar1990.herokuapp.com/getassemblyname.php?lat="+latlong[0]+"&long="+latlong[1]);
        loadPolygon("p",pmappolygon, "http://sravankumar1990.herokuapp.com/getparliamentname.php?lat="+latlong[0]+"&long="+latlong[1]);

        map.center.latitude=latlong[0];
        map.center.longitude=latlong[1];

    }
}
