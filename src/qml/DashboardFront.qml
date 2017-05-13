
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
                target: user_details
                height:parent.parent.height
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
        anchors.top: user_details.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        GridLayout{
            anchors.margins: 50
            anchors.centerIn: parent
            columnSpacing: parent.width/2
            rowSpacing: parent.height/4
            columns: 2

            Button{
                id:list_button
                text: qsTr("Your Pcs")
                Material.foreground: Material.Purple
                width: parent.parent.width/2
                onClicked: {listClicked();
                    domain_list.refresh();
                }
            }
            Button{
                id:network_button
                text: qsTr("Networking")
                Material.foreground: Material.Purple


                onClicked: {netlistClicked();
                    network_list.refresh();
                }
            }
            Button{
                id:new_button
                text: qsTr("    New    ")
                width: 100
                Material.foreground: Material.Purple
                onClicked: newvmClicked()
            }
            Terminal_button {
                id: terminal_button2
                Material.foreground: Material.Purple
            }
        }

    }
}
