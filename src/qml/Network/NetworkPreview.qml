import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Material 2.0


Rectangle{

    id:root_item
    anchors.margins: 20
    onWidthChanged: {
        addButton.width=(root_item.width<(login.width/2)?0:50)
        removeButton.width=(root_item.width<(login.width/2)?0:50)
    }

    Button{
        id:addButton
        width: 0
        height:50
        visible:(!forwardExist||!bridgeExist||!bandwidthExist||(!ip4Exist||!ip6Exist))
        anchors.margins: 20
        Image {
            id: add
            source: "qrc:/../icons/add.png"// This is available in all editors.
            anchors.fill: parent
        }
        z:2
        anchors.right: removeButton.left
        anchors.top: parent.top
        onClicked:  {addTab.open();
        }
    }
    Button{
        id:removeButton
        visible:forwardExist||bridgeExist||bandwidthExist||(ip4Exist||ip6Exist)
        anchors.top: parent.top
        anchors.right: parent.right
        width: 0
        height:50
        anchors.margins: 20
        Image {
            id: remove
            source: "qrc:/../icons/remove.png"// This is available in all editors.
            anchors.fill: parent
        }
        z:2
        onClicked:  {removeTab.open()
        }
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
            anchors.margins: 20
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
            anchors.margins: 20
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
            anchors.margins: 20
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
            anchors.margins: 20
            IpElement{
                id:ip_element
                visible: ip4Exist||ip6Exist
                anchors.fill: parent
                Component.onCompleted:ip_element.addTabs();
            }

        }

    }


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


    Popup{
        id:removeTab
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
                    visible: bandwidthExist
                    text:"Bandwidth"
                    onClicked: {
                        bandwidthExist=false;
                        for(i=0;i<netTab.count;i++)
                            if(netTab.getTab(i).title==="Bandwidth")
                                netTab.removeTab(i);
                    }
                }

                Button{
                    visible: (ip4Exist&&ip6Exist)
                    text:"Ip4"
                    onClicked: {
                        ip4Exist=false;
                        console.log("called");

                        for(i=0;i<netTab.count;i++)
                            if(netTab.getTab(i).title==="IP")
                                netTab.removeTab(i);
                        setIndex();
                    }
                }
                Button{
                    visible: (ip4Exist&&ip6Exist)
                    text:"Ip6"
                    onClicked: {
                        ip6Exist=false;
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
        anchors.fill: parent
        anchors.margins: 20
    }


}

