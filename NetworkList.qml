import QtQuick 2.0
import QtQuick.Controls.Material 2.0


Item {
    signal errorm();
    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#4a4a4a" }
            GradientStop { position: 1.0; color: "#2b2b2b" }
        }
    }

    ListView {
        id: listView
        anchors.topMargin: 50
        anchors.fill: parent

        delegate: detailsDelegate

        model: network_list
    }

    NetworklistDelegate{
        id:detailsDelegate
    }

}