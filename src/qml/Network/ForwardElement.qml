import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0


Rectangle{
    id:forward

    Column{
        id:col_for
        anchors.right: parent.right
        anchors.left: parent.left
        spacing: 50

        Rectangle{
            width: forward.width
            height:forward.height/8

            Row{
                Rectangle{
                    anchors.verticalCenter: parent.verticalCenter
                    width: forward.width/2
                    height: forward.height/8
                    Row{
                        anchors.verticalCenter: parent.verticalCenter
                        spacing: 20
                        id: forward_mode
                        Text {
                            id: forward_mode_id
                            text: qsTr("Mode")
                            font.pixelSize: 20
                        }
                        TextField{
                            id: forward_mode_text
                            text: forwardMode
                            onTextChanged:{
                                if(text.toLowerCase()==="nat"){
                                    nat_box.visible=true;
                                }
                                else
                                    nat_box.visible=false;

                                network_list.set_data(index,forward_mode_text.text.toLowerCase(),"forwardMode")
                                //anyone who can find error in the below statement is a qml god
                                //console.log(forward_mode_text.text.toLowerCase()+ "index "+index+"but actual text "+forwardMode+"return on setdata "+network_list.set_data(index,forward_mode_text.text.toLowerCase(),"forwardMode"))
                            }
                        }
                    }
                }
                Rectangle{
                    anchors.verticalCenter: parent.verticalCenter

                    width: forward.width/2
                    height: forward.height/8
                    Row{
                        anchors.verticalCenter: parent.verticalCenter
                        spacing: 20
                        id: forward_dev
                        Text {
                            id: forward_dev_id
                            text: qsTr("Device")
                            font.pixelSize: 20
                        }
                        TextField{
                            id: forward_dev_text
                            text: forwardDev
                            onTextChanged: {
                                network_list.set_data(index,forward_dev_text.text.toLowerCase(),"forwardDev")
                            }
                        }
                    }
                }
            }
        }
        Rectangle{
            id:nat_box
            visible: forward_mode_text.text==="nat"?true:false
            width: forward.width
            height:forward_mode_text.text==="nat"?forward.height/8:0

            Row{
                anchors.verticalCenter: parent.verticalCenter
                spacing: 20
                id: nat
                Column{
                    spacing: 5
                    Text {
                        id: nat_id
                        text: qsTr("Nat:")
                        font.pixelSize: 20
                    }
                    Row{
                        spacing: 20
                        Text {
                            id: nat_port_id
                            //  anchors.horizontalCenter: parent.horizontalCenter
                            text: qsTr("Port:")
                            font.pixelSize: 20
                        }
                        Column{
                            Text {
                                id: nat_port_start_id
                                text: qsTr("start")
                                font.pixelSize: 20
                            }
                            TextField{
                                id: nat_port_start_id_text
                                text: natStart
                                validator: IntValidator { bottom:0; top: contoller.getMaxPort()}

                                onTextChanged: {
                                    network_list.set_data(index,nat_port_start_id_text.text,"natStart")
                                }
                            }
                        }
                        Column{
                            Text {
                                id: nat_port_end_id
                                text: qsTr("end")
                                font.pixelSize: 20
                            }
                            TextField{
                                id: nat_port_end_id_text
                                text: natEnd
                                validator: IntValidator { bottom:0; top: contoller.getMaxPort()}

                                onTextChanged: {
                                    network_list.set_data(index,nat_port_end_id_text.text,"natEnd")
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

