import QtQuick 2.5
import QtQuick.Layouts 1.1
import QtQuick.Controls.Private 1.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 1.4
import QtQuick.XmlListModel 2.0

Item {
    id: root
    width: 200
    height: 400

    ListView {
        anchors.fill: parent

        model: ["Home", "Global", "Measure", "Settings", "About"]

        Gradient {
            id: pressGradient
            GradientStop { position: 0; color: "#EEEEEE" }
            GradientStop { position: 0.3; color: "#9E9E9E" }
            GradientStop { position: 0.6; color: "#9E9E9E" }
            GradientStop { position: 1; color: "#BDBDBD" }
        }

        Gradient {
            id: releaseGradient
            GradientStop { position: 0; color: "#E0E0E0" }
            GradientStop { position: 0.3; color: "#757575" }
            GradientStop { position: 0.6; color: "#757575" }
            GradientStop { position: 1; color: "#9E9E9E" }
        }

        Gradient {
            id: unGradeint
            GradientStop { position: 0; color: "#E0E0E0" }
            GradientStop { position: 0.3; color: "#E0E0E0" }
            GradientStop { position: 0.6; color: "#E0E0E0" }
            GradientStop { position: 1; color: "#E0E0E0" }
        }

        delegate: MouseArea {
            id: mouseArea
            height: 40;
            width: parent.width
            hoverEnabled: true
            onClicked: {
                console.debug(modelData)
            }

            Rectangle {
                color: mouseArea.containsMouse ? "#cccccc" : "#888888"
                anchors.fill: parent
                anchors.margins: 1
                radius: 4;
                border.color: mouseArea.containsMouse ? "#212121" : "#333333"
                border.width: mouseArea.containsMouse ? 2 : 1
                opacity: 0.4

                gradient: !mouseArea.enabled ? unGradeint : mouseArea.pressed ? pressGradient : releaseGradient
            }

            Text {
                anchors.centerIn: parent
                text: modelData
                font.family: "微软雅黑"
                font.pointSize: 13
            }
        }
    }
}
