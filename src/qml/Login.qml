import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Material 2.0


Item {
    id: login
    property string host_uri: "localhost"
    signal loginClicked;


    states: [
        State {
            name: "loggedin"
            PropertyChanges {
                target: loginscreen
                visible:false
            }
        }
    ]

    function clicked(){
        console.log(getUri())
        host_uri=getUri();
        loginClicked();
    }

    function getUri(){
        if(selectBox.currentText==="Local host")
            return "localhost";
        else
            return address_list.get(uriBox.currentIndex).address;
    }

    function checkCredentials(){
        host.username=username_textbox.text;
        host.password=password_textbox.text;
        return host.authenticate(getUri());
    }

    Rectangle {
        Image {
            id: bg
            anchors.fill: parent
            source: "file:///"+applicationDirPath + "/background/dashbord.png"
        }

        id:loginscreen
        anchors.fill: parent

        Column{
            spacing: 10
            anchors.centerIn: parent

            TextInput {
                id: username_textbox
                width: loginscreen.width/4
                text: qsTr("dravigon")
            }

            TextInput {
                id: password_textbox
                width: loginscreen.width/4
                echoMode: "Password"
                text: qsTr("spyman007")
                Keys.onReturnPressed: clicked()
            }

            CustomButton {
                id:log
                text: qsTr("Login")

                Material.foreground: Material.Purple
                height: 30
               width: loginscreen.width/4
                anchors.horizontalCenter:parent.horizontalCenter
                onClicked: {
                    console.log(getUri())
                    host_uri=getUri();
                    loginClicked();
                }
            }
        }

        ComboBox {
            id: selectBox
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.margins: 20
            textRole: "name"
            model:ListModel {
                id: host_list_model

                ListElement {
                    name: "Local host"
                }

                ListElement {
                    name: "Remote Host"
                }
            }
        }

        ComboBox {
            id: uriBox
            visible: selectBox.currentText=="Remote Host"?true:false;
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.margins: 20
            model:address_list
            textRole: "user_name"//this sets the role to be displayed as text
        }
    }
}
