import QtQuick.Controls 2.1
import QtQuick 2.7
import QtQuick.Controls.Material 2.0


Popup{
    id:err
    width:320
    height:200

    property string errormessage
    Rectangle{
        width:300
        height:170
        radius: 10
        color: "gray"
        anchors.horizontalCenter: parent.horizontalCenter
        Row{
            width:100
            height: 50
            y:30
            anchors.horizontalCenter: parent.horizontalCenter
            id: img
            spacing: 10
            Text {
                id: txt
                text: qsTr("error")
                font.pointSize: 24;
                style: Text.Outline;
                styleColor: "red"
            }
            AnimatedImage {
                id:ok
                width: 20
                height: 50
                source: "qrc:/icons/Exclamation.gif"
            }}
        Text {
            anchors.top:img.bottom
            anchors.right: parent.right
            anchors.left: parent.left
            id: name
            text: qsTr(err.errormessage)
            wrapMode:Text.WrapAtWordBoundaryOrAnywhere
            fontSizeMode:Text.Fit
            horizontalAlignment: Text.AlignJustify
            verticalAlignment: Text.AlignVCenter
        }
    }
}

