import QtQuick 2.0

Rectangle {
    width: 640
    height: 480

    // Create a flickable to view a large image.
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

        // Only show the scrollbars when the view is moving.
        states: State {
            name: "ShowBars"
            when: view.movingVertically || view.movingHorizontally
            PropertyChanges { target: verticalScrollBar; opacity: 1 }
            PropertyChanges { target: horizontalScrollBar; opacity: 1 }
        }

        transitions: Transition {
            NumberAnimation { properties: "opacity"; duration: 400 }
        }
    }

    // Attach scrollbars to the right and bottom edges of the view.
    ScrollBar {
        id: verticalScrollBar
        opacity: 0
        width: 10;
        height: view.height-10
        anchors.right: view.right
        orientation: Qt.Vertical
        position: view.visibleArea.yPosition
        pageSize: view.visibleArea.heightRatio
    }

    ScrollBar {
        id: horizontalScrollBar
        width: view.width-10; height: 10
        anchors.bottom: view.bottom
        opacity: 0
        orientation: Qt.Horizontal
        position: view.visibleArea.xPosition
        pageSize: view.visibleArea.widthRatio
    }
}
