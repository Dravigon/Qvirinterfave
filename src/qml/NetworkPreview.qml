import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Material 2.0

Rectangle{
    id:root_item
    function incrementdata(indx){
        for(i=0;i<indx;i++){
            tabBar.incrementCurrentIndex();
            swipe.incrementCurrentIndex();
        }
    }

    function setIndex(){
        if(forwardExist)
            tabBar.currentIndex=swipe.currentIndex
        else if(bridgeExist)
            incrementdata(1);

        else if(bandwidthExist)
            incrementdata(2);

        else if(ip4Exist)
            incrementdata(2);
    }
    //color: "red"


    StackLayout {
        id: swipe
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: parent.height-tabBar.height-40
        anchors.margins: 20

        currentIndex: tabBar.currentIndex
        Rectangle {
            color: "blue"
            visible: forwardExist
            ForwardElement{
                visible:forwardExist
                anchors.fill: parent
            }
        }

        Rectangle {
            visible: bridgeExist
            BridgeElement{
                visible: bridgeExist
                anchors.fill: parent
            }
        }

        Rectangle {
            visible: bandwidthExist

            BandwidthElement{
                visible: bandwidthExist
                anchors.fill: parent
            }
        }
        Rectangle {
            visible: ip4Exist
            IpElement{
                visible: ip4Exist
                anchors.fill: parent
            }
        }
    }


    TabBar {
        id: tabBar
        width: root_item.width
        TabButton{
            text: forwardExist?"Forward":""
            width:forwardExist?Math.max(100, tabBar.width / 5):0
        }
        TabButton{
            text:bridgeExist?"Bridge":""
            width: bridgeExist?Math.max(100, tabBar.width / 5):0
        }
        TabButton{
            text:bandwidthExist?"Bandwidth":""
            width: bandwidthExist?Math.max(100, tabBar.width / 5):0
        }
        TabButton{
            text:ip4Exist?"Ip":""
            width: ip4Exist?Math.max(100, tabBar.width / 5):0
        }
    }


}

