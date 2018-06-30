import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Material 2.0

ApplicationWindow {
    visible: true
    visibility:"Maximized"

    property var dommodel;

    title: qsTr("Qvirinterface")

    Errormessage{
        id:err
        x:parent.width/2-160;
        y:parent.height/2-100;
        onOpened: {
            errormessage=host.err();
        }
    }

    Login{
        id:login
        anchors.fill: parent
        onLoginClicked:{
            var errm=checkCredentials();
            if(errm==="connected"){
                login.state="loggedin";
            }
            else{
                err.errormessage=errm
                err.open()
            }
        }
    }
    Terminal{
        id:pop
        x:parent.width/2-320;
        y:parent.height/2-200;
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
    }
    Terminal_button {
        id: terminal_button
        visible: login.state==="loggedin"?false:true
        Material.foreground: Material.Purple
        anchors.bottom: parent.bottom
        anchors.margins: 50
        anchors.right: parent.right
    }



    Dashboard{
        anchors.fill: parent
        visible: login.state=="loggedin"?true:false
        onLogout:{ login.state="";
            visible:false
        }
    }


}




