import QtQuick 2.9
import QtQuick.Controls 2.2

Button{
    property string iconPath:"";
    property string btnText: "";

    id:root;
    width: parent.width;
    height: 40;
    checkable: true;

    background: Rectangle{
        anchors.fill: parent;
        color: parent.pressed | parent.checked?"#E6E7EA":"transparent";

        Rectangle{
            implicitWidth: 3;
            implicitHeight: parent.height;
            anchors.left: parent.left;
            color: g_themeColor;
            visible:  root.pressed |root.checked? true : false;
        }
    }

    contentItem: Rectangle{
        anchors.fill: parent;
        color: "transparent";

        Image {
            id:iconLabel;
            anchors{
                left: parent.left;
                leftMargin: 15;
                verticalCenter: parent.verticalCenter;
            }
            height: 25
            width: 25
            source: iconPath
            verticalAlignment:Label.AlignVCenter;
            horizontalAlignment: Label.AlignHCenter;
        }

        Label{
            anchors{
                left: iconLabel.right;
                leftMargin: 10;
                right: parent.right;
                rightMargin: 3;
            }
            height: parent.height;
            text:btnText;
            font.family: g_fontFamily;
            font.pixelSize: 12;
            wrapMode: Text.Wrap;
            verticalAlignment:Label.AlignVCenter;
            color: root.hovered | root.checked ?"#000000":"#5C5C5C";
        }
    }
}
