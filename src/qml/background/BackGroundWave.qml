import QtQuick 2.0
import QtQuick.Scene3D 2.0


Scene3D {
    id: scene3d
    anchors.fill: parent
    anchors.margins: 10
    focus: true
    aspects: ["input", "logic"]
    cameraAspectRatioMode: Scene3D.AutomaticAspectRatio
BgMain{
    id: bg
}
}
