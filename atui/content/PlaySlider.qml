import QtQuick 2.9
import QtQuick.Controls 2.2

Slider {
    id: sliderControl

    property real minValue: 0.0
    property real maxValue: 0.0
    property bool isVisible: true       //滑块handle是否显示，在音量调节器时需要隐藏
    property bool isPressed: false
    property var releasedFunc: function () {}

    from: minValue
    to: maxValue

    background: Rectangle {
        x: sliderControl.leftPadding
        y: sliderControl.topPadding + sliderControl.availableHeight / 2 - height / 2
        implicitWidth: sliderControl.width
        implicitHeight: 5
        width: sliderControl.availableWidth
        height: implicitHeight
        radius: 2
        color: "lightgray"

        Rectangle {
            width: sliderControl.visualPosition * parent.width
            height: parent.height
            color: g_themeColor
            radius: 2
        }
    }

    handle: Rectangle {
        x: sliderControl.leftPadding + sliderControl.visualPosition
           * (sliderControl.availableWidth - width)
        y: sliderControl.topPadding + sliderControl.availableHeight / 2 - height / 2
        width: 14
        height: 14
        radius: 7
        color: "white"
        border.width: 1
        border.color: 'lightgray'
        visible: isVisible ? isVisible : sliderControl.hovered

        Rectangle{
            anchors.centerIn: parent
            width: 4
            height: 4
            radius: 2
            color: g_themeColor
        }

        MouseArea {
            property real xmouse
            anchors.fill: parent
            hoverEnabled: true

            cursorShape: Qt.PointingHandCursor
            acceptedButtons: Qt.LeftButton
            onPressed: {
                xmouse = mouseX
                sliderControl.isPressed = true
            }

            onReleased: {
                sliderControl.isPressed = false
                sliderControl.releasedFunc()
            }

            onPositionChanged: {
                if (pressed) {
                    sliderControl.value = sliderControl.value + (mouseX - xmouse)
                            / (sliderControl.width) * (maxValue - minValue)
                }
            }
        }
    }
}
