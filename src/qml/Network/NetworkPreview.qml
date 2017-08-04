import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Material 2.0


Rectangle{

    id:root_item

    Button{
        anchors.right: parent.right
        anchors.top:parent.top
        text:"add"
        onClicked: addTab.open();
    }

    function tabExist(tabName){
        for(i=0;i<netTab.count;i++)
            if(netTab.getTab(i).title===tabName)
                return true;

        return false;
    }

    function setIndex(){

        if(forwardExist)
            if(!tabExist("Forward"))
                netTab.addTab("Forward",forward_tab)
        if(bridgeExist)
            if(!tabExist("Bridge"))
                netTab.addTab("Bridge",bridgeTab)
        if(bandwidthExist)
            if(!tabExist("Bandwidth"))
                netTab.addTab("Bandwidth",bandwidthTab)
        if((ip4Exist||ip6Exist))
            if(!tabExist("IP")){
                netTab.addTab("IP",ipTab)
            }



    }
    //color: "red"
    Component{
        id:forward_tab
        Rectangle {
            visible: forwardExist
            anchors.fill: parent
            ForwardElement{
                visible:forwardExist
                anchors.fill: parent
            }
        }
    }
    Component{
        id:bridgeTab
        Rectangle {
            visible: bridgeExist
            anchors.fill: parent
            BridgeElement{
                visible: bridgeExist
                anchors.fill: parent
            }
        }
    }
    Component{
        id:bandwidthTab
        Rectangle {
            visible: bandwidthExist
            anchors.fill: parent
            BandwidthElement{
                visible: bandwidthExist
                anchors.fill: parent
            }
        }

    }
    Component{
        id:ipTab

        Rectangle {
            id:ipComponent
            function addtabs(){
                ip_element.addTabs();
            }
            visible: ip4Exist||ip6Exist
            anchors.fill: parent
            IpElement{
                id:ip_element
                visible: ip4Exist||ip6Exist
                anchors.fill: parent
                Component.onCompleted:ip_element.addTabs();
            }

        }

    }
    //TODO put ip4 and ip6 in seperate tabs or make ip6 and ip4 dynamically viewable

    Popup{
        id:addTab


        Rectangle{
            color: "gray"
            width:root_item.width
            height:login.height-50
            opacity: 0.7
            // anchors.centerIn: root_item
            ColumnLayout{
                anchors.horizontalCenter:  parent.horizontalCenter
                anchors.verticalCenter:   parent.verticalCenter
                Button{
                    visible: !forwardExist
                    text:"Forward"
                    onClicked: {
                        forwardExist=true;
                        netTab.addTab("Forward",forward_tab)
                    }
                }
                Button{
                    visible: !bridgeExist
                    text:"Bridge"
                    onClicked: {
                        bridgeExist=true;
                        netTab.addTab("Bridge",bridgeTab)
                    }
                }
                Button{
                    visible: !bandwidthExist
                    text:"Bandwidth"
                    onClicked: {
                        bandwidthExist=true;
                        netTab.addTab("Bandwidth",bandwidthTab)
                    }
                }
                Button{
                    visible: !(ip4Exist||ip6Exist)
                    text:"Ip"
                    onClicked: {
                        netTab.addTab("Ip",ipTab)
                    }
                }
                Button{
                    visible: !(ip4Exist)
                    text:"Ip4"
                    onClicked: {
                        ip4Exist=true;
                        console.log("called");

                        for(i=0;i<netTab.count;i++)
                            if(netTab.getTab(i).title==="IP")
                                netTab.removeTab(i);
                        setIndex();
                    }
                }
                Button{
                    visible: !(ip6Exist)
                    text:"Ip6"
                    onClicked: {
                        ip6Exist=true;
                        console.log("called");
                        for(i=0;i<netTab.count;i++)
                            if(netTab.getTab(i).title==="IP")
                                netTab.removeTab(i);
                        setIndex();
                    }
                }
            }
        }
    }



    TabView {
        id: netTab
        width: root_item.width
        height: root_item.height

    }


}

