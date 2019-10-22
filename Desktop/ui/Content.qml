import QtQuick 2.4
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import QtQuick.Extras 1.4
import QtQuick.XmlListModel 2.0

Item {
    anchors.fill: parent

    Text {
        id: text
        visible: false
    }

    property var componentModel: [
        { name: "Tabs", component: tabsComponent },
        { name: "View", component: viewComponent },
    ]

    Loader {
        id: componentLoader
        anchors.fill: parent
        sourceComponent: componentModel[controlData.componentIndex].component
    }

    Component {
        id: tabsComponent
        Item {
            enabled: !settingsData.allDisabled

            Tabs{
                anchors.fill: parent
            }
        }
    }

    property Component viewComponent: ScrollView {
        id: scrollView
        horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff

        Flickable {
            anchors.fill: parent
            contentWidth: viewport.width
            contentHeight: buttoncolumn.implicitHeight + textMargins * 1.5
            ColumnLayout {
                id: buttoncolumn
                anchors.fill: parent
                anchors.margins: textMargins
                anchors.topMargin: textMargins / 2
                spacing: textMargins / 2
                enabled: !settingsData.allDisabled

                GroupBox {
                    title: "Button"
                    checkable: settingsData.checks
                    flat: !settingsData.frames
                    Layout.fillWidth: true
                    GridLayout {
                        columns: Math.max(1, Math.floor(scrollView.width / button.implicitWidth - 0.5))

                    }
                }
            }
        }
    }
}
