import QtQuick 2.9
import QtQuick.Controls 2.2

Rectangle{
    id:root;
    width: 200;
    height: parent.height;
    color: "#F5F5F7";

    ButtonGroup{
        id:navigationBtnGroup;
    }

    Column{
        anchors.fill: parent;
        spacing: 0;

        Label{
            anchors{
                left: parent.left;
                leftMargin: 10;
            }
            width: parent.width;
            height: 30;
            verticalAlignment: Label.AlignVCenter
            text:qsTr("推荐")
            font.family: g_fontFamily;
            font.pixelSize: 12;
            color: "#7d7d7d";
        }

        NavigationBtn{
            iconPath: "qrc:/res/music.svg";
            btnText: qsTr("发现音乐");
            width: parent.width;
            height: 30;
            ButtonGroup.group: navigationBtnGroup;
            onClicked: function(){
                setContentView("PlayLists.qml")
            }
            Component.onCompleted: {
                checked=true
            }
        }

        NavigationBtn{
            iconPath: "qrc:/res/wave.svg";
            btnText: qsTr("私人FM");
            width: parent.width;
            height: 30;
            ButtonGroup.group: navigationBtnGroup;
            onClicked: function(){
                setContentView("PersonFM.qml")
            }
        }

        NavigationBtn{
            iconPath: "qrc:/res/video.svg";
            btnText: qsTr("MV");
            width: parent.width;
            height: 30;
            ButtonGroup.group: navigationBtnGroup;
            onClicked: function(){

            }
        }

        Label{
            anchors{
                left: parent.left;
                leftMargin: 10;
            }
            width: parent.width;
            height: 30;
            verticalAlignment: Label.AlignVCenter
            text:qsTr("我的音乐")
            font.family: g_fontFamily;
            font.pixelSize: 12;
            color: "#7d7d7d";
        }

        NavigationBtn{
            iconPath: "qrc:/res/musicrl.svg";
            btnText: qsTr("本地音乐");
            width: parent.width;
            height: 30;
            ButtonGroup.group: navigationBtnGroup;
            onClicked: function(){

            }
        }

        NavigationBtn{
            iconPath: "qrc:/res/download.svg";
            btnText: qsTr("下载管理");
            width: parent.width;
            height: 30;
            ButtonGroup.group: navigationBtnGroup;
            onClicked: function(){

            }
        }
    }
}
