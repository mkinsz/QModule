import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    id: root
    visible: true
    width: 900
    height: 500
    title: qsTr("Desktop")

    Ark {
        anchors.fill: parent
    }
}
