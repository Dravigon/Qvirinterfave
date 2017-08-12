//import QtQuick 2.0

//Rectangle {
//    color: "violet"

//}
import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1

GridLayout {
id: id_gridLayout
//anchors.fill: parent
//spacing: 2

//Layout.rowSpan: 2

columns: 3
Button { text: "prev"
    focus: false
}
Button { text: "next" }
Slider { Layout.fillWidth: true }
Text { text: "asdf" }
Button { text: "prev" }
Button { text: "next" }
Text { text: "asdf" }
Slider {
Layout.fillWidth: true
Layout.columnSpan: 2
}

}
