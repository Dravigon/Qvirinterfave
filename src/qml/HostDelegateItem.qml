import QtQuick 2.0
import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

Component {
    id:host_root
    Rectangle {
                        width: parent.width
                        height: 50
                        //  color: size
                        Row{
                            Text {

                                text: "name:" //role to get data from internal model
                            }
                            TextField{
                                text: name
                            }
                            Text {
                                id: host_mac
                                text: qsTr("Mac")
                            }
                            TextField{
                                text: mac
                            }
                            Text {
                                id: host_id
                                text: qsTr("Id")
                            }
                            TextField{
                                text: id
                            }
                            Text {
                                id: host_ip
                                text: qsTr("IP")
                            }
                            TextField{
                                text: ip
                            }
                        }

                    }
}
