import QtQuick 2.0
import QtQuick.Controls.Material 2.0
/*this is list menue for all VMs
  *the delegate is a custom delegate
  */

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
        clip: true

        delegate: detailsDelegate
        model: domain_list
    }

    VmlistDelegate{
        id:detailsDelegate
    }

    onVisibleChanged: {
        //TODO limit all ui with these variables
        var n=JSON.parse(host.hostCapabilities());
        //retrieve values from JSON again
        var aString = n.capabilities.host.uuid;
        console.log(aString);
    }

}
