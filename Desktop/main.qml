import QtQuick 2.12
import QtQuick.Window 2.12
import QtGraphicalEffects 1.13
import Material.Core 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Desktop")

    Item {
        anchors.centerIn: parent
         width: 300
         height: 300

         Image {
             id: bug
             source: "qrc:/res/dog.png"
             sourceSize: Qt.size(parent.width, parent.height)
             smooth: true
             visible: false
         }

         Image {
             id: mask
             source: "qrc:/res/circle.png"
             sourceSize: Qt.size(parent.width, parent.height)
             smooth: true
             visible: false
         }

         MaskedMouseArea {
             id: moonArea
             anchors.fill: parent
             alphaThreshold: 0.0
             maskSource: Qt.resolvedUrl("circle.png")

             onClicked: {
                 console.debug("////")
             }
         }

         OpacityMask {
             anchors.fill: bug
             source: bug
             maskSource: mask
             scale: moonArea.pressed ? 1.1 : 1.0
             opacity: moonArea.containsMouse ? 1.0 : 0.7
         }
     }
}
