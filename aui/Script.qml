import QtQuick 2.0

import "js/Dummy.js" as Dummy
import "js/utils.js" as Utils

Item {
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: {
            Dummy.dummy()
        }
    }

    Text {
        text: Utils.i18n('old')
    }
}
