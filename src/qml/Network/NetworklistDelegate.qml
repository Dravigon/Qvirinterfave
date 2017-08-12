import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls.Material 2.0


Component {
    id: detailsDelegate

    Item {
        id: wrapper

        property int i
        property int root_index: index
        property bool toggle: false

        width: listView.width
        height: 80


        Timer {//for dynamically getting the State of the network
            id:statetimer
            interval: 2000; running: true; repeat: true
            onTriggered:{ if(i>0)wrapper.state=network_list.task("state",index);
                i++;
                //     network_list.refresh();
                //        console.log("host_size:"+ip4DhcpHostModel.size())
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

            Popup{
                id:popupConfirm
                x:rt.width/2-250
                y:login.height/2-200
                Rectangle{
                    width:500
                    height:200
                    ColumnLayout{
                        anchors.centerIn: parent
                        Text {
                            text: qsTr("Are you sure to remove "+name+" Connection")
                        }
                        RowLayout{
                            Button{
                                text:"yes"
                                onClicked: {
                                    network_list.removeIndex(index);
                                }
                            }
                            Button{
                                text:"no"
                                onClicked: popupConfirm.close();
                            }
                        }
                    }

                }
            }

            Rectangle{
                id:removeButton
                anchors.right: parent.right
                anchors.top:parent.top
                anchors.margins: 20
                height:30
                width: 30
                MouseArea{
                    anchors.fill: parent
                    Image {
                        anchors.fill: parent
                        id: deleter
                        source: "qrc:/../icons/remove.png";
                    }
                    onClicked: {
                        popupConfirm.open();
                        console.log("okay");}
                }
            }

            //NOTE dont know why i added this incase somthing is wrong with preview uncomment this
            //            onHeightChanged: {
            //               // preview.height=height;
            //            }

            MouseArea {
                z:0
                anchors.right: removeButton.left
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                onClicked: {
                    if(!toggle){
                        if((network_list.task("stop",index)==="stopped")||(network_list.task("state",index)==="stopped")){
                            wrapper.state = "expanded"
                            toggle=!toggle;
                        }
                    }
                    else{
                        wrapper.state = ""
                        toggle=!toggle;
                        if(!network_list.setXmlData(index)){
                            err.errormessage=host.err()
                            err.open();
                        }
                    }
                }
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
                RowLayout{//for start stop and pause button
                    z:1
                    Button{
                        id:start
                        width: 50
                        Text {
                            anchors.centerIn: parent
                            text: qsTr(">")
                        }
                        onClicked: {if(network_list.task("start",index)==="started"){
                                wrapper.state = "started";
                                // console.log(domain_list.task("xml",index));
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
                        onClicked:{ if(network_list.task("stop",index)==="stopped"){
                                wrapper.state = "stopped";
                            }
                            else
                                errorm();
                        }
                    }
                }
            }
        }

        //for the details with last running display image of the vm

        NetworkPreview{
            id: preview
            width: 0
            height: rt.height
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.rightMargin: 2
            anchors.topMargin: 2
        }



        Item {//details of the vm and to edit vm
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
        //<planned

        //slots
        ListView.onAdd: {
            if((index===listView.count-1)&&listView.lock)
                state="expanded";
            listView.lock=false;
        }

        onStateChanged: {
            if(state==="expanded")
                preview.setIndex();
        }
        //

        states: [
            State {
                name: "expanded"

                PropertyChanges {target: statetimer; running:!statetimer.running}
                PropertyChanges { target: wrapper; height: listView.height }
                PropertyChanges { target: preview; width: listView.width; height: parent.height-80; anchors.rightMargin: 0; anchors.topMargin: rt.height }
                PropertyChanges { target: factsView; opacity: 1 }
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
            },
            State {
                name: "nil"
                PropertyChanges {
                    target: virterr
                    visible:true
                    opened:true
                }
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
