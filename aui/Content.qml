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
        { name: 'Flick', component: flickComponent},
        { name: 'Button', component: buttonsComponent},
        { name: 'Charts', component: chartsComponent},
        { name: 'QrCode', component: qrcodeComponent},
        { name: 'Progress', component: progressComponent},
        { name: 'Script', component: scriptComponent},
        { name: "Flow", component: flowComponent },
        { name: "View", component: viewComponent },
    ]

    Loader {
        id: componentLoader
        anchors.fill: parent
        sourceComponent: componentModel[controlData.componentIndex].component
    }

    Component {
        id: flickComponent

        Item {
            enabled: !settingsData.allDisabled

            FlickImage {
                anchors.fill: parent
            }
        }
    }

    Component {
        id: buttonsComponent

        Item {
            enabled: !settingsData.allDisabled

            Buttons {

            }
        }
    }

    Component {
        id: chartsComponent

        Item {
            enabled: !settingsData.allDisabled

            Charts {
                anchors.fill: parent
            }
        }
    }

    Component {
        id: scriptComponent

        Item {
            enabled: !settingsData.allDisabled

            Script {
                anchors.fill: parent
            }
        }
    }

    Component {
        id: progressComponent

        Item {
            enabled: !settingsData.allDisabled

            Progress {
                anchors.fill: parent
            }
        }
    }

    Component {
        id: qrcodeComponent

        Item {
            enabled: !settingsData.allDisabled

            QrCode {
                anchors.top : parent.top
                anchors.topMargin : 30
                anchors.horizontalCenter : parent.horizontalCenter
                width : 320
                height : 320
                value : inputField.text
                level : "H"
            }
            TextInput {
                id : inputField
                anchors.bottom : parent.bottom
                anchors.bottomMargin : 30
                anchors.horizontalCenter : parent.horizontalCenter
                text : "http://www.baidu.com"
            }
        }
    }

    Component {
        id: flowComponent
        Item {
            enabled: !settingsData.allDisabled

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
                        Button {
                            id: button
                            text: qsTr("Change Color")
                            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                        }
                    }
                }
            }
        }
    }
}
