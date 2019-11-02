import QtQuick 2.9
import QtQuick.Controls 2.2

Rectangle {
    id: root
    color: "transparent"

    readonly property string g_themeColor: '#3D4D5A'
    readonly property string g_fontFamily: 'Microsoft YaHei'
    readonly property int g_fontSize: 14
    readonly property string g_fontNormal: 'gray'
    readonly property string g_fontHover: 'black'
    readonly property int g_fontTitleSize: 15

    Rectangle {
        width: parent.width
        height: 2
        color: g_themeColor
    }

    NavigationBar {
        id: navigationBar
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.topMargin: 2
        width: 200
        height: parent.height - 2

        Rectangle {
            width: parent.height
            height: 8
            rotation: 90
            anchors.left: parent.right
            transformOrigin: Item.TopLeft

            gradient: Gradient {
                GradientStop {
                    color: Qt.rgba(0, 0, 0, 0.10)
                    position: 0
                }
                GradientStop {
                    color: Qt.rgba(0, 0, 0, 0.05)
                    position: 0.5
                }
                GradientStop {
                    color: Qt.rgba(0, 0, 0, 0)
                    position: 1
                }
            }
        }
    }

    Loader {
        id: contentWindow
        anchors {
            top: parent.top
            topMargin: 2
            left: navigationBar.right
            right: parent.right
            bottom: divider.top
        }
        height: parent.height - 2-playController.height

        source: 'PlayLists.qml'
    }

    Rectangle {
        id: divider
        height: 1
        color: 'lightgray'
        anchors {
            bottom: playController.top;
            left: parent.left;
            right: parent.right;
        }
    }

    PlayBar {
        id: playController
        anchors {
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }

        height: 50
    }

    /*
      播放歌曲
      url  获取歌曲的链接url
      pic_url  歌曲专辑图片
      song_length 歌曲的长度
      */
    function playMusic(url,pic_url,song_length,song_name,singer){
        playController.pic_url=pic_url
        playController.song_length=song_length
        playController.song_name=song_name
        playController.singer=singer
        playController.song_url=url //song_url要在最后，因为PlayController的onSong_urlChanged
    }

    /*
      切换右边内容界面
      */
    function setContentView(view){
        contentWindow.source=view
    }

}
