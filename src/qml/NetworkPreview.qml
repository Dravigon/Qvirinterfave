import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Material 2.0

//Item {
//unimplimented>
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
        else if(bridgeExist){
            incrementdata(1);
        }
    }
            //color: "red"
            StackLayout {
                id: swipe
                anchors.fill: parent

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
            }

            TabBar {
                id: tabBar
                TabButton{
                    text: "Forward"
                    width:forwardExist?Math.max(100, tabBar.width / 5):0
                }
                TabButton{
                    text:"Bridge"
                    width: bridgeExist?Math.max(100, tabBar.width / 5):0
                }
            }


            //    ColumnLayout{
            //        id:col
            //        anchors.right: parent.right
            //        anchors.left: parent.left
            //         anchors.margins: 20
            //         spacing: 20

            //        Rectangle{
            //            anchors.right: parent.right
            //            anchors.left: parent.left
            //            height: root_item.height/20
            //            id: conf
            //            Text {
            //                text: qsTr("Configuration")
            //                font.pixelSize: 20
            //            }
            //        }
            //        TabView {
            //            anchors.fill: parent
            //            anchors.topMargin: 30
            //            Tab {
            //                title: "Forward"
            //                anchors.topMargin: 30
            //                ForwardElement{
            //                    id:frwd
            //                    anchors.right: parent.right
            //                    anchors.left: parent.left
            //                    height: forwardExist?root_item.height/8:0
            //                }
            //            }
            //            Tab {
            //                title: "Bridge"
            //                anchors.topMargin: 30
            //                BridgeElement{
            //                    id:brdg
            //                    anchors.right: parent.right
            //                    anchors.left: parent.left
            //                    height: bridgeExist?root_item.height/8:0

            //                }
            //            }
            //            Tab {
            //                title: "Green"
            //                Rectangle { color: "green" }
            //            }
            //        }




            //    }


        }
        //}
