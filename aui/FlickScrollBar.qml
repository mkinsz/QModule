import QtQuick 2.0


ScrollBar {
    id: root
    opacity: 0
    orientation: Qt.Vertical

    // 绑定到Flickable组件
    property Flickable target : Flickable{}

    // 位置
    width: orientation==Qt.Vertical ? 10 : target.width-10
    height: orientation==Qt.Vertical ? target.height-10 : 10
    anchors.right: orientation==Qt.Vertical ? target.right : undefined
    anchors.bottom: orientation==Qt.Vertical ? undefined : target.bottom

    // 滚动
    position: orientation==Qt.Vertical ? target.visibleArea.yPosition   : target.visibleArea.xPosition
    pageSize: orientation==Qt.Vertical ? target.visibleArea.heightRatio : target.visibleArea.widthRatio


    // 移动时显隐滚动轴
    Connections{
        target: root.target
        onMovingVerticallyChanged: {
            if (target.movingVertically)
                fadeIn.start();
            else
                fadeOut.start();
        }
        onMovingHorizontallyChanged: {
            if (target.movingHorizontally)
                fadeIn.start();
            else
                fadeOut.start();
        }
    }
    NumberAnimation { id:fadeIn;  target: root; properties: "opacity"; duration: 400; from:0; to:1 }
    NumberAnimation { id:fadeOut; target: root; properties: "opacity"; duration: 400; from:1; to:0 }
}

