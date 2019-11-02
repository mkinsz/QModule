import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls 1.4 as Controls_1_4
import QtQuick.Controls.Styles 1.4
import Network 1.0

Item {
    property int currentPage: 0 //当前是第几页
    signal requestFinished(string result)

    Connections {
        target: loader.source=="PlayList.qml"?loader.item : null
        onPlaylistRequest: {
            loader.setSource("Loading.qml")
            currentPage = page
            var offset = page * 60
        }

        onPlaylistDetail:{
            listDetail.open()
        }
    }

    Network {
        id: network
        onSign_requestFinished: {
            loader.setSource("PlayList.qml", {
                                 page: currentPage
                             })
            loader.requestFinished(bytes)
        }
        onSign_requestError: {
            loader.source = "NetworkError.qml"
        }
    }

    Details{
        id:listDetail
        x:parent.x
        y:parent.y
        width: parent.width
        height: parent.height
    }

    ButtonGroup {
        id: tabBtnGroup
        onClicked: {
            button.btnClickedFunc()
        } 
    }

    Row {
        id: tabBar
        height: 50
        spacing: 20
        anchors.horizontalCenter: parent.horizontalCenter

        ListModel {
            id: tabModel
            ListElement {
                name: "个性推荐"
                url: "/playlists?source=netease&limit=60"
            }
            ListElement {
                name: "歌单"
                url: "/playlists?source=netease&limit=60"
            }
            ListElement {
                name: "主播电台"
                url: "/playlists?source=netease&limit=60"
            }
            ListElement {
                name: "排行榜"
                url: "/playlists?source=netease&limit=60"
            }
            ListElement {
                name: "歌手"
                url: "/playlists?source=netease&limit=60"
            }
            ListElement {
                name: "最新音乐"
                url: "/playlists?source=netease&limit=60"
            }
        }

        Repeater {
            id: tabRepeater
            model: tabModel
            delegate: TabBtn {
                btnText: name
                ButtonGroup.group: tabBtnGroup
                btnClickedFunc: function () {
                    loader.setSource("Loading.qml")
                    currentPage = index
                    network.get(url)
                }
            }

            Component.onCompleted: {
                itemAt(currentPage).checked = true
            }
        }
    }

    Rectangle {
        anchors {
            top: tabBar.bottom
            topMargin: -1
            left: parent.left
            leftMargin: 20
            right: parent.right
            rightMargin: 20
        }
        height: 1
        z: -1
        color: "lightgray"
    }

    Loader {
        //这里还可以再封装一下
        id: loader
        anchors.top: tabBar.bottom
        anchors.topMargin: 5
        width: parent.width
        height: parent.height - tabBar.height
        source: "Loading.qml"

        signal requestFinished(string result)
    }
}
