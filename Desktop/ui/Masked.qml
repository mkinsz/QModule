import QtQuick 2.0
import QtGraphicalEffects 1.13
import Material.Core 1.0

Item {
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
