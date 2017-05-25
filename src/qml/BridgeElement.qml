import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

Rectangle{
    id:bridge

    Column{
        id:col_for
        spacing: 50
        Rectangle{
            width: bridge.width
            height:bridge.height/8
            color: "blue"
            Row{
                Rectangle{
                    anchors.verticalCenter: parent.verticalCenter
                    width: bridge.width/2
                    height: bridge.height/8
                    Row{
                                            anchors.verticalCenter: parent.verticalCenter
                        spacing: 20
                        id: bridge_name
                        Text {
                            id: bridge_name_id
                            text: qsTr("Name")
                            font.pixelSize: 20
                        }
                        TextField{
                            id: bridge_name_text
                            text: bridgeName
                        }
                    }
                }
                Rectangle{
                    anchors.verticalCenter: parent.verticalCenter

                    width: bridge.width/2
                    height: bridge.height/8
                    Row{
                                            anchors.verticalCenter: parent.verticalCenter
                        spacing: 20
                        id: bridge_stp
                        Text {
                            id: bridge_stp_id
                            text: qsTr("Stp")
                            font.pixelSize: 20
                        }
                        TextField{
                            id: bridge_stp_text
                            text: bridgeStp
                        }
                    }
                }
            }
        }
        Rectangle{
            width: bridge.width/2
            height: bridge.height/8
            Row{
                                    anchors.verticalCenter: parent.verticalCenter
                spacing: 20
                id: bridge_Delay
                Text {
                    id: bridge_delay_id
                    text: qsTr("Delay")
                    font.pixelSize: 20
                }
                TextField{
                    id: bridge_delay_text
                    text: bridgeStp
                }
            }
        }
    }
}

