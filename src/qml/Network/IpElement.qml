import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Material 2.0


Rectangle {
    id:ip_root
    onWidthChanged: {
        visible=(root_item.width<(login.width/2)?false:true)
    }
    function tabExist(tabName){
        for(i=0;i<id_tab.count;i++)
            if(id_tab.getTab(i).title===tabName)
                return true;

        return false;
    }
    function addTabs(){
        if(ip4Exist)
            if(!tabExist("ip4"))
                id_tab.addTab("ip4",rec_ip4);
        if(ip6Exist)
            if(!tabExist("ip6"))
                id_tab.addTab("ip6",rec_ip6);
    }

    TabView{
        id:id_tab
        anchors.fill: parent

        //ip4 elements display
        Component{
            id: rec_ip4
            Rectangle {
                anchors.fill: parent
                anchors.margins: 20

                Button{
                    id:ipAddButton
                    width: 50
                    height:50
                    visible:!ip4DhcpExist||!ip4DhcpHasHost
                    Image {
                        id: ipAdd
                        source: "qrc:/../icons/add.png"// This is available in all editors.
                        anchors.fill: parent
                    }
                    z:2
                    anchors.right: parent.right
                    anchors.top: parent.top
                    onClicked:  {ip4_add_values.open();
                    }
                }
                Button{
                    id:ipRemoveButton
                    visible:ip4DhcpExist||ip4DhcpHasHost
                    anchors.top: ipAddButton.bottom
                    anchors.right: parent.right
                    width: 50
                    height:50
                    Image {
                        id: ipremove
                        source: "qrc:/../icons/remove.png"// This is available in all editors.
                        anchors.fill: parent
                    }
                    z:2
                    onClicked:  {ip4_remove_values.open()

                    }
                }
                Popup{
                    id:ip4_add_values
                    Rectangle{
                        color: "gray"
                        width:root_item.width-200
                        height:login.height-500
                        opacity: 0.7

                        ColumnLayout{
                            anchors.centerIn: parent
                            Button{
                                text:"add DHCP"
                                visible: (!ip4DhcpExist)
                                onClicked: {ip4DhcpExist=true
                                    ip4_dhcp.visible=true;
                                    ip4DhcpRangeExist=true;
                                    ipAddButton.visible=(!ip4DhcpExist||!ip4DhcpHasHost);
                                    ipRemoveButton.visible=ip4DhcpExist||ip4DhcpHasHost;
                                }
                            }
                            Button{
                                text:"add Host"
                                visible: (!ip4DhcpHasHost)
                                onClicked: {
                                    ip4DhcpHasHost=true
                                    ipAddButton.visible=(!ip4DhcpExist||!ip4DhcpHasHost);
                                    ipRemoveButton.visible=ip4DhcpExist||ip4DhcpHasHost;
                                }
                            }
                        }
                    }
                }

                Popup{
                    id:ip4_remove_values
                    Rectangle{
                        color: "gray"
                        width:root_item.width-200
                        height:login.height-500
                        opacity: 0.7
                        ColumnLayout{
                            anchors.centerIn: parent
                            Button{
                                text:"Remove DHCP"
                                visible: (ip4DhcpExist)
                                onClicked: {ip4DhcpExist=false;
                                    ip4_dhcp.visible=false;
                                    ip6DhcpRangeExist=false;
                                    ipAddButton.visible=(!ip4DhcpExist||!ip4DhcpHasHost);
                                    ipRemoveButton.visible=ip4DhcpExist||ip4DhcpHasHost;
                                }
                            }
                            Button{
                                text:"Remove Host"
                                visible: (ip4DhcpHasHost)
                                onClicked: {
                                    ip4DhcpHasHost=false;
                                    ipAddButton.visible=(!ip4DhcpExist||!ip4DhcpHasHost);
                                    ipRemoveButton.visible=ip4DhcpExist||ip4DhcpHasHost;
                                }
                            }
                        }
                    }
                }



                visible: ip4Exist
                Rectangle{
                    Row{
                        spacing: 50
                        Column{
                            spacing:30

                            Row{
                                Text {
                                    id: addr
                                    text: qsTr("Ip Address: ")
                                    font.pixelSize: 20

                                }
                                TextField{
                                    id: addr_textField
                                    validator: IpValidator{

                                    }

                                    text: qsTr(ip4Address)
                                    onTextChanged: {
                                        network_list.set_data(index,addr_textField.text,"ip4Address")
                                    }
                                }
                            }
                            Row{
                                Text {
                                    id: netmask
                                    text: qsTr("Netmask: ")
                                    font.pixelSize: 20
                                }
                                TextField{
                                    id: netmask_textField
                                    text: ip4Netmask
                                    onTextChanged: {
                                        network_list.set_data(index,netmask_textField.text,"ip4Netmask")
                                    }
                                }
                            }
                        }

                        Column{
                            spacing: 20
                            Row{
                                id:ip4_dhcp
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
                                            validator: IpValidator{}

                                            onTextChanged: {
                                                network_list.set_data(index,ip4_dhcp_start_text.text,"ip4DhcpRangeStart")
                                            }
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
                                            validator: IpValidator{}
                                            onTextChanged: {
                                                network_list.set_data(index,ip4_dhcp_end_text.text,"ip4DhcpRangeEnd")
                                            }
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
                    height: (ip4DhcpHostModel.size()*50+20)==20?120:ip4DhcpHostModel.size()*50+20;
                    width: ip_root.width/1.4
                    Rectangle{
                        visible: ip4DhcpHasHost
                        Button{
                            id:addButton
                            width: 50
                            height:50
                            Image {
                                id: add
                                source: "qrc:/../icons/add.png"// This is available in all editors.
                                anchors.fill: parent
                            }
                            z:2
                            anchors.right: parent.right
                            anchors.top: parent.top
                            onClicked: {
                                ip4DhcpHostModel.create();
                                parent.height=ip4DhcpHostModel.size()*50;
                                hosts_popup.height=(ip4DhcpHostModel.size()*50+20)<120?120:ip4DhcpHostModel.size()*50+20;
                                parent.width=ip_root.width/1.4-20;
                            }
                        }
                        Button{
                            id:removeButon
                            anchors.top: addButton.bottom
                            width: 50
                            height:50
                            Image {
                                id: remove
                                source: "qrc:/../icons/remove.png"// This is available in all editors.
                                anchors.fill: parent
                            }
                            z:2
                            anchors.right: parent.right
                            onClicked: {
                                ip4DhcpHostModel.remove();
                                parent.height=ip4DhcpHostModel.size()*50;
                                hosts_popup.height=(ip4DhcpHostModel.size()*50+20)<120?120:ip4DhcpHostModel.size()*50+20;
                                parent.width=ip_root.width/1.4-20;
                            }
                        }
                        radius: 0.5
                        height: ip4DhcpHostModel.size()*50
                        width: ip_root.width/1.4-20
                        color: "gray"
                        opacity: 0.8
                        ListView{
                            id: listView
                            z:1
                            clip: true
                            anchors.fill: parent
                            model: ip4DhcpHostModel
                            delegate:HostDelegateItem{
                            }
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
        //ip6 below
        Component{
            id: rec_ip6
            Rectangle {
                anchors.fill: parent
                height: parent.height
                anchors.margins: 20
                visible: ip6Exist
                Button{
                    anchors.right: parent.right
                    anchors.top:parent.top
                    text: "add_values"
                    onClicked: ip6_add_values.open()
                }
                Popup{
                    id:ip6_add_values
                    Rectangle{
                        anchors.fill: parent
                        opacity: 0.7
                        ColumnLayout{
                            Button{
                                text:"add DHCP"
                                visible: (!ip6DhcpExist)
                                onClicked: {ip6DhcpExist=true
                                    ip6_dhcp.visible=true;
                                    ip6DhcpRangeExist=true;
                                }
                            }
                            Button{
                                text:"add Host"
                                visible: (!ip6DhcpExist)
                                onClicked: {
                                    ip6DhcpHasHost=true
                                }
                            }
                        }
                    }
                }

                Rectangle{
                    Row{
                        spacing: 50
                        Column{
                            spacing:30

                            Row{
                                Text {
                                    id: ip6_addr
                                    text: qsTr("Ip Address: ")
                                    font.pixelSize: 20

                                }
                                TextField{
                                    id: ip6_addr_textField
                                    text: qsTr(ip6Address)
                                    onTextChanged: {
                                        console.log("blosck")
                                        network_list.set_data(index,ip6_addr_textField.text,"ip6Address")
                                    }
                                }
                            }
                            Row{
                                Text {
                                    id: ip6_netmask
                                    text: qsTr("Prefix: ")
                                    font.pixelSize: 20
                                }
                                TextField{
                                    id: ip6_prefic_textField
                                    text: ip6Prefix
                                    onTextChanged: {
                                        network_list.set_data(index,ip6_prefix_textField.text,"ip6Netmask")
                                    }
                                }
                            }
                        }

                        Column{
                            spacing: 20
                            Row{
                                id:ip6_dhcp
                                visible: ip6DhcpExist
                                spacing:20
                                Text {
                                    visible: ip6DhcpRangeExist
                                    id: ip6_dhcp_text
                                    text: qsTr("Dhcp:")
                                    font.pixelSize: 20
                                }
                                ColumnLayout{
                                    visible: ip6DhcpRangeExist

                                    Row{
                                        Text {
                                            id: ip6_dhcp_start
                                            text: qsTr("Range Start: ")
                                            font.pixelSize: 20

                                        }
                                        TextField{
                                            id:ip6_dhcp_start_text
                                            text:ip6DhcpRangeStart
                                            onTextChanged: {
                                                network_list.set_data(index,ip6_dhcp_start_text.text,"ip6DhcpRangeStart")
                                            }
                                        }
                                    }

                                    Row{
                                        Text {
                                            id: ip6_dhcp_end
                                            text: qsTr("Range End: ")
                                            font.pixelSize: 20

                                        }
                                        TextField{
                                            id:ip6_dhcp_end_text
                                            text:ip6DhcpRangeEnd
                                            onTextChanged: {
                                                network_list.set_data(index,ip6_dhcp_end_text.text,"ip6DhcpRangeEnd")
                                            }
                                        }
                                    }

                                }
                            }
                            Button {
                                visible: ip6DhcpHasHost
                                id: ip6_button
                                text: qsTr("Hosts")
                                onClicked: ip6_hosts_popup.open()
                            }
                        }
                    }
                }


                Popup{
                    id:ip6_hosts_popup
                    height: ip6DhcpHostModel.size()*50+20
                    width: ip_root.width/1.4
                    Rectangle{


                        visible: ip6DhcpHasHost
                        radius: 0.5
                        height: ip6DhcpHostModel.size()*50
                        width: ip_root.width/1.4-20
                        color: "gray"
                        opacity: 0.8
                        ListView{
                            id: ip6_listView
                            z: 1
                            clip: true
                            anchors.fill: parent
                            model: ip6DhcpHostModel
                            delegate:HostDelegateItem{
                            }
                            onModelChanged: {
                                network_list.set_data(index,ip6_listView.model,"ip6DhcpHostModel")
                            }
                        }
                    }
                }
            }
        }
    }
}
