import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Controls.Material 2.0


Flipable {
    id: flipable

    signal logout();

    property bool flipped: false
    property Vmlist vmlist

    front: DashboardFront{id:fr
        anchors.fill: parent
        onListClicked: {
            load.showlist()
            rotation.axis.y=1
            flipable.flipped = !flipable.flipped;
        }
        onNewvmClicked: {
            load.shownewvm()
            rotation.axis.y=1
            flipable.flipped = !flipable.flipped;
        }
        onNetlistClicked: {
            load.showNetlist()
            rotation.axis.y=-1;
           flipable.flipped = !flipable.flipped;
        }

        Button{
            id:logout_button
            text: qsTr("Logout")
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.margins: 50
            onClicked:{ host.close();
                logout();
            }
        }
    }
    back:Backitem{id:load}


    transform: Rotation {
        id: rotation
        origin.x: flipable.width/2
        origin.y: flipable.height/2
        axis.x: 0; axis.y: 1; axis.z: 0     // set axis.y to 1 to rotate around y-axis
        angle: 0    // the default angle
    }

    states: [
    State {
        name: "back"
        PropertyChanges {target: rotation;angle: 180}
        when: flipable.flipped
    }]

    transitions: Transition {
        NumberAnimation { target: rotation;
            easing.type: Easing.InOutBack
            property: "angle";
            duration: 2000 }
    }
}
