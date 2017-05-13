import QtQuick 2.0

/*for login alone
 *text is represented as transparent
 *and the button is solid colour
 */

MouseArea {
  width: txt.contentWidth + 20
  height: txt.contentHeight + 10
  property alias text: txt.text
  property alias color: sh.color
  ShaderEffect {
    id: sh
    anchors.fill: parent
    property color color: "lightgray"
    property var source : ShaderEffectSource {
      sourceRect: Qt.rect(0, 0, sh.width, sh.height)
      sourceItem: Item {
        width: sh.width
        height: sh.height
        Text {
          id: txt
          anchors.centerIn: parent
          font.bold: true
          text: "test"
        }
      }
    }
    fragmentShader:
        "varying highp vec2 qt_TexCoord0;
           uniform highp vec4 color;
           uniform sampler2D source;
           void main() {
               gl_FragColor = color * (1.0 - texture2D(source, qt_TexCoord0).w);
           }"
  }

}
