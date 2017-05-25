import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

//Item {
//unimplimented>
Rectangle{
    id:root_item
    anchors.fill: parent
    //color: "red"

    Column{
        anchors.fill: parent
        anchors.margins: 20
        ForwardElement{
                anchors.fill: parent
        }

    }
    Image {
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        //source: imageSource
    }
}
//}
