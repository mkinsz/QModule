import QtQuick 2.12
import QtQuick.Window 2.12
import QtGraphicalEffects 1.12

import Material.Core 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Item {
        width: 300
        height: 300
        anchors.centerIn: parent

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

        OpacityMask {
            anchors.fill: bug
            source: bug
            maskSource: mask
            scale: maskArea.pressed ? 1.1 : 1.0
            opacity: maskArea.containsMouse ? 1.0 : 0.7
        }

        MaskedMouseArea {
            id: maskArea
            anchors.fill: parent
            alphaThreshold: 0.0
            maskSource: Qt.resolvedUrl("qrc:/res/circle.png")

            onClicked: {
    //            console.debug("Mask Clicked...")
            }
        }
    }
}
