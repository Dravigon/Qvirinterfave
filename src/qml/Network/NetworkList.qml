
import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls.Material 2.0



Rectangle {
    signal errorm();
    signal added();
    Timer {//for dynamically getting the State of the network
        id:statetimer
        interval: 2000; running: true; repeat: true
        onTriggered:{
            network_list.refresh();
        }
    }

    Popup{
        id:addNetwork
        closePolicy: Popup.NoAutoClose
        Rectangle{
            width:login.width-20
            height:login.height-20
            ColumnLayout{
                anchors.centerIn: parent
                Text {
                    text: qsTr("Enter Name");
                }
                TextField{
                    id:newName
                    height:30
                    width:50
                }
                RowLayout{
                    Button{
                        text:"Okay"
                        onClicked:{
                            if(newName.text!=""){
                                network_list.addNewNetwork(newName.text)
                                addNetwork.close()
                                added();
                                //listView.contentItem.childAt(listView.count,0).state="expanded";
                            }
                        }
                    }
                    Button{
                        id: close
                        text:"Cancel"
                        onClicked: addNetwork.close()
                    }
                }
            }
        }
    }

    Rectangle {
        anchors.fill: parent
        Button{
            anchors.margins: 15
            anchors.right: parent.right
            anchors.top:parent.top
            width: 30
            height:30
            Image {
                id: addButton
                anchors.fill: parent
                source: "qrc:/../icons/add.png"
            }
            onClicked: {
                console.log("add button clicked")
                addNetwork.open()
                listView.lock=true;
            }
        }

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#4a4a4a" }
            GradientStop { position: 1.0; color: "#2b2b2b" }
        }
    }

    ListView {
        id: listView
        property bool lock: false
        anchors.topMargin: 50
        anchors.fill: parent
        clip: true

        delegate: detailsDelegate

        model: network_list
    }


    NetworklistDelegate{
        id:detailsDelegate
    }

}
