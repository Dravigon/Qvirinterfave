import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3


Rectangle {
    id:ip_root


    Rectangle {
        height: parent.height
        anchors.margins: 20
        id: rec_ip4
        visible: ip4Exist
        anchors.fill: parent
        Rectangle{
            Row{
                spacing: 50
                Column{
                    spacing:30
                    Row{
                        Text {
                            id: fam
                            text: qsTr("Family: ")
                            font.pixelSize: 20

                        }
                        TextField {
                            id: fam_textField
                            text: qsTr(ip4Family===""?"ip4":ip4Family)
                        }
                    }
                    Row{
                        Text {
                            id: addr
                            text: qsTr("Ip Address: ")
                            font.pixelSize: 20

                        }
                        TextField{
                            id: addr_textField
                            text: qsTr(ip4Address)
                            onTextChanged: {
                                console.log("blosck")
                                network_list.set_data(index,addr_textField.text,"ip4Address")
                            }
                        }
                    }
                    Row{
                        Text {
                            id: netmask
                            text: qsTr("Device: ")
                            font.pixelSize: 20
                        }
                        TextField{
                            id: netmask_textField
                            text: ip4Netmask
                        }
                    }
                }

                Column{
                    spacing: 20
                    Row{
                        visible: ip4DhcpExist
                        spacing:20
                        Text {
                            id: dhcp_text
                            text: qsTr("Dhcp:")
                            font.pixelSize: 20
                        }
                        ColumnLayout{
                            visible: ip4DhcpRangeExist

                            Row{
                                Text {
                                    id: ip4_dhcp_start
                                    text: qsTr("Range Start: ")
                                    font.pixelSize: 20

                                }
                                TextField{
                                    id:ip4_dhcp_start_text
                                    text:ip4DhcpRangeStart
                                }
                            }

                            Row{
                                Text {
                                    id: ip4_dhcp_end
                                    text: qsTr("Range End: ")
                                    font.pixelSize: 20

                                }
                                TextField{
                                    id:ip4_dhcp_end_text
                                    text:ip4DhcpRangeEnd
                                }
                            }

                        }
                    }
                    Button {
                        visible: ip4DhcpHasHost
                        id: button
                        text: qsTr("Hosts")
                        onClicked: hosts_popup.open()
                    }
                }
            }
        }


        Popup{
            id:hosts_popup
            height: ip4DhcpHostModel.size()*50+20
            width: ip_root.width/1.4
            Rectangle{
                visible: ip4DhcpHasHost
                radius: 0.5
                height: ip4DhcpHostModel.size()*50
                width: ip_root.width/1.4-20
                color: "gray"
                opacity: 0.8
                ListView{
                    id: listView
                    z: 1
                    clip: true
                    anchors.fill: parent
                    model: ip4DhcpHostModel
                    delegate:HostDelegateItem{
                    }
                }
            }
        }
    }

    //    Rectangle {
    //        id: rec_ip6
    //        anchors.bottom: parent.bottom
    //        anchors.left: parent.left
    //        anchors.right: parent.right
    //        height: parent.height/2
    //    }

}
