import QtQuick 2.7
import QMLTermWidget 1.0
import QtQuick.Controls 1.4
import QtQuick.Window 2.2
import QtQuick.Controls 2.1
import QtQuick.Controls.Material 2.0


Popup{
    id:popup
    width: 640
    height: 400
    modal: true
    focus: true
    Rectangle{
        anchors.fill: parent
        visible: parent.visible
        width: 640
        height: 400
        Shortcut{
            sequence: "Ctrl+Shift+C"
            onActivated:terminal.copyClipboard();
        }

        Shortcut{
            sequence:  "Ctrl+Shift+V"
            onActivated: terminal.pasteClipboard();
        }

        Shortcut{
            sequence: "Ctrl+F"
            onActivated: searchButton.visible = !searchButton.visible
        }


        QMLTermWidget {
            id: terminal
            anchors.fill: parent
            font.family: "Monospace"
            font.pointSize: 12
            colorScheme: "cool-retro-term"
            antialiasText:true
            session: QMLTermSession{
                id: mainsession
                initialWorkingDirectory: "$HOME"
                onMatchFound: {
                    console.log("found at: %1 %2 %3 %4".arg(startColumn).arg(startLine).arg(endColumn).arg(endLine));
                }
                onNoMatchFound: {
                    console.log("not found");
                }
            }
            onTerminalUsesMouseChanged: console.log(terminalUsesMouse);
            onTerminalSizeChanged: console.log(terminalSize);
            Component.onCompleted: mainsession.startShellProgram();
        }

        Button {
            id: searchButton
            text: "Find version"
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            visible: false
            onClicked: mainsession.search("version");
        }

        Button{
            id:close
            text: "X"
            anchors.top: parent.top
            anchors.right: parent.right
            onClicked:{popup.close();
            }
        }
    }

    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
    onVisibleChanged:  {terminal.forceActiveFocus();
        mainsession.clearScreen();
        mainsession.sendText("clear
");
    }

}
