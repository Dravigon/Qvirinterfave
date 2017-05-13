import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls.Material 2.0


Component {
    id: detailsDelegate

    Item {
        id: wrapper

        property int i
        width: listView.width
        height: 80

        Timer {
            id:statetimer
             interval: 1000; running: true; repeat: true
             onTriggered:{ if(i>0)wrapper.state=network_list.task("state",index);
                 i++;
             }
             onRunningChanged: i=0;
         }


        Rectangle {
            id:rt
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top

            height: 80

            color: "#333"
            border.color: Qt.lighter(color, 1.2)
            MouseArea {
                z:0
                anchors.fill: rt
                onClicked: wrapper.state = "expanded"
            }

            ColumnLayout{
                anchors.left: parent.left
                anchors.leftMargin: 10
                Text {
                    id:domname
                    font.pixelSize: parent.parent.height-60
                    color: '#fff'
                    text: name
                }
                RowLayout{
                    z:1
                    Button{
                        id:start
                        width: 50
                        Text {
                            anchors.centerIn: parent
                            text: qsTr(">")
                        }
                        onClicked:{ if(network_list.task("start",index)==='ok'){
                                       wrapper.state = "started";
                                       console.log(network_list.task("xml",index));
                                   }
                            else
                                errorm();
                        }
                    }

                    Button{
                        id:stop
                        width: 0
                        visible: false
                        Text {
                            anchors.centerIn: parent
                            text: qsTr("#")
                        }
                        onClicked: {if(network_list.task("stop",index)==='ok'){
                                       wrapper.state = "stopped";
                                   }
                            else
                                errorm();
                        }
                    }
                }
            }
        }

        Rectangle {
            id: preview
            width: 26
            height: rt.height
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.rightMargin: 2
            anchors.topMargin: 2
            color: "black"

            Image {
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
                //source: imageSource
            }
        }



        Item {
            id: factsView

            anchors.top: preview.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom

            opacity: 0

            Rectangle {
                anchors.fill: parent

                gradient: Gradient {
                    GradientStop { position: 0.0; color: "#fed958" }
                    GradientStop { position: 1.0; color: "#fecc2f" }
                }
                border.color: '#000000'
                border.width: 2

                Text {
                    anchors.fill: parent
                    anchors.margins: 5

                    clip: true
                    wrapMode: Text.WordWrap
                    color: '#1f1f21'

                    font.pixelSize: 12

                    //text: facts
                }
            }
        }

        Rectangle {
            id: closeButton

            anchors.right: parent.right
            anchors.top: parent.top
            anchors.rightMargin: 2
            anchors.topMargin: 2

            width: rt.height
            height: rt.height-3

            color: "#157efb"
            border.color: Qt.lighter(color, 1.1)

            opacity: 0
            Text {
                anchors.centerIn: parent
                text: qsTr("X")
            }

            MouseArea {
                anchors.fill: parent
                onClicked: wrapper.state = ""
            }
        }

        states: [
            State {
                name: "expanded"

                PropertyChanges { target: wrapper; height: listView.height }
                PropertyChanges { target: preview; width: listView.width; height: listView.width; anchors.rightMargin: 0; anchors.topMargin: rt.height }
                PropertyChanges { target: factsView; opacity: 1 }
                PropertyChanges { target: closeButton; opacity: 1 }
                PropertyChanges { target: wrapper.ListView.view; contentY: wrapper.y; interactive: false }
            },
            State {
                name: "started"
                PropertyChanges{target:domname;color:"green"}
                PropertyChanges {target: start;width:0}
                PropertyChanges{target: start;visible:false}
                PropertyChanges {target: stop;width:50}
                PropertyChanges {target:stop;x:75}
                PropertyChanges {target: stop;visible:true}
            },
            State {
                name: "stopped"
                PropertyChanges{target:domname;color:"#fff"}
                PropertyChanges {target: start;width:50}
                PropertyChanges{target: start;visible:true}

                PropertyChanges {target: stop;width:0}
                PropertyChanges {target:stop;x:50}

                PropertyChanges {target: stop;visible:false}
            }
        ]

        transitions: [
            Transition {
                NumberAnimation {
                    easing.type: Easing.InOutBack
                    duration: 1000
                    properties: "height,width,anchors.rightMargin,anchors.topMargin,opacity,contentY"
                }
                NumberAnimation {
                    easing.type: Easing.InOutBack
                    duration: 800
                    properties: "x,y"
                }
                PropertyAnimation{
                    duration: 1200
                    property: "visible"
                }
            }
        ]
    }

}
