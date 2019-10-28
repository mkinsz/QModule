import QtQuick 2.0

Rectangle {

    Flickable {
        id: view
        anchors.fill: parent
        contentWidth: picture.width
        contentHeight: picture.height
        Image {
            id: picture
            source: "res/coombe.jpg"
            asynchronous: true
        }
    }

    FlickScrollBar {
        target: view
        orientation: Qt.Vertical
    }
    FlickScrollBar {
        target: view
        orientation: Qt.Horizontal
    }
}
