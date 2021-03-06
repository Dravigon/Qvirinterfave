import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import "./Network"

Rectangle{
        id:load
        anchors.fill: parent
        function showlist(){
            list.visible=true;
            newvm.visible=false;
            netlist.visible=false;
        }
        function showNetlist(){
            netlist.visible=true;
            list.visible=false;
            newvm.visible=false;
        }
        function shownewvm(){
            list.visible=false;
            newvm.visible=true;
            netlist.visible=false;
        }
        Errormessage{
            id:err
            x:parent.width/2-160;
            y:parent.height/2-100;
        }

        CreateVm{
            Button{
                id:back_button
                text: qsTr("back")

                anchors.top:parent.top
                anchors.left: parent.left
                onClicked: flipable.flipped = !flipable.flipped;
            }
            visible: false
            id:newvm
            anchors.fill: parent
        }

        Vmlist{
            Button{
                id:back_button2
                text: qsTr("back")

                anchors.top:parent.top
                anchors.left: parent.left
                onClicked: flipable.flipped = !flipable.flipped;
            }
            visible: false
            id:list
            anchors.fill: parent
            onErrorm: {
                err.errormessage=host.err();
                err.open();
            }
        }

        NetworkList{
            Button{
                id:back_button3
                text: qsTr("back")
                anchors.top:parent.top
                anchors.left: parent.left
                onClicked: flipable.flipped = !flipable.flipped;
            }
            visible: false
            id:netlist
            anchors.fill: parent

        }
    }
