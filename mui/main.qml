import QtQuick 2.6
import QtQuick.Window 2.2

Window {
    visible: true
    width: 900
    height: 600
    title: qsTr("MUI")

    ListModel {
        id: model
        ListElement { url: "res/cover/jay.jpg" }
        ListElement { url: "res/cover/timg.jpg" }
        ListElement { url: "res/cover/timg2.jpg" }
        ListElement { url: "res/cover/timg3.jpg" }
        ListElement { url: "res/cover/timg4.jpg" }
    }

    CoverFlow {
        anchors.fill: parent
        model: model
    }
}
