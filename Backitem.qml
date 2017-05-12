import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0


Rectangle{
        id:load
        anchors.fill: parent
        function showlist(){
            list.visible=true;
            newvm.visible=false;
            list2.visible=false;
        }
        function showNetlist(){
            list2.visible=true;
            list.visible=false;
            newvm.visible=false;
        }
        function shownewvm(){
            list.visible=false;
            newvm.visible=true;
            list2.visible=false;
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
            id:list2
            anchors.fill: parent
        }
    }
