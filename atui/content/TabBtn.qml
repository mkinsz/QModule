import QtQuick 2.9
import QtQuick.Controls 2.2

Button {
    property string btnText: "" //按钮名称
    property var btnClickedFunc: (function () {}) //按钮点击处理函数
    id: root
    width: 100
    height: 50
    checkable: true

    background: Rectangle {
        anchors.fill: parent
        color: "transparent"

        Rectangle {
            implicitHeight: 2
            implicitWidth: parent.width
            anchors.bottom: parent.bottom
            color: g_themeColor
            visible: root.pressed | root.checked ? true : false
        }
    }

    contentItem: Rectangle {
        anchors.fill: parent
        color: "transparent"

        Label {
            width: parent.width
            height: parent.height
            text: btnText
            font.family: g_fontFamily
            font.pixelSize: g_fontTitleSize
            verticalAlignment: Label.AlignVCenter
            horizontalAlignment: Label.AlignHCenter
            color: root.hovered | root.checked ? "#000000" : "#5C5C5C"
        }
    }
}
