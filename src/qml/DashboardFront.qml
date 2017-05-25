
import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Material 2.0

Item {
    id:root
    signal listClicked();
    signal netlistClicked();
    signal newvmClicked();


    states: [
        State {
            name: "image_clicked"
            PropertyChanges {
                target: actions
                height:0
            }
        }
    ]
    transitions: [
        Transition {
            NumberAnimation {
                easing.type: Easing.InOutBack
                duration: 1000
                properties: "height"
            }
        }
    ]

    Rectangle{
        id:user_details
        color: "purple"
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        height: parent.height/2;
        Image {
            id: bg2
            anchors.fill: parent
            source: "file:///"+applicationDirPath + "/background/dashbord.png"
        }
        MouseArea{
            id:user_area
            anchors.fill: parent
            onClicked:root.state=(root.state==="image_clicked"?"":"image_clicked");
        }
    }

    Rectangle{
        id:actions
        color: "green"
        Image {
            id: bg
            anchors.fill: parent
            source: "file:///"+applicationDirPath + "/background/dashbord2.jpg"
        }
        height: user_details.height/2
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        Grid{
            opacity: 0.75

            anchors.centerIn: parent
            columnSpacing:5
            rowSpacing: 5
            columns: 2

            Button{
                id:list_button
                text: qsTr("Your Pcs")
                Material.foreground: Material.Purple
                width: actions.width/2-5
                height: actions.height/2-5
                onClicked: {listClicked();
                    domain_list.refresh();
                }
            }
            Button{
                id:network_button
                text: qsTr("Networking")
                Material.foreground: Material.Purple
                width: actions.width/2-5
                height: actions.height/2-5

                onClicked: {netlistClicked();
                    network_list.refresh();
                }
            }
            Button{
                id:new_button
                text: qsTr("New")
                width: actions.width/2-5
                height: actions.height/2-5
                Material.foreground: Material.Purple
                onClicked: newvmClicked()
            }
            Terminal_button {
                id: terminal_button2
                width: actions.width/2-5
                height: actions.height/2-5
                Material.foreground: Material.Purple
            }
        }

    }
}
