import QtQuick 2.9
import QtQuick.Controls 2.2
import QtMultimedia 5.9
import Network 1.0

Rectangle {
    id: root

    property string song_url: "" //歌曲的url
    property string pic_url: "" //歌曲专辑图片
    property int song_length: 0 //歌曲的长度
    property string song_name: ""
    property string singer: ""

    color: "white"

    //播放进度条改变信号
    signal playSliderChanged(int value)
    //当前歌曲已播放完毕
    signal playFinished()
    //下一首
    signal nextSong()


    //格式化歌曲长度
    function durationFormat(length) {
        var m = parseInt(length / 60) >= 10 ? parseInt(
                                                  length / 60) : "0" + parseInt(
                                                  length / 60)
        var s = parseInt(length % 60) >= 10 ? parseInt(
                                                  length % 60) : "0" + parseInt(
                                                  length % 60)
        return m + ":" + s
    }

    Network {
        id: network
        onSign_requestFinished: {
            var data = JSON.parse(bytes)
            var url = data['song_url']
            mediaplayer.source = url
            mediaplayer.play()
        }
    }

    MediaPlayer {
        id: mediaplayer
        volume: vSlider.volume

        onError: {

        }
        onPlaying: {
            playBtn.state = "play"
        }
        onStopped: {
            playBtn.state = "pause"
        }
        onSourceChanged: {

        }
        onPositionChanged: {
            if (!playSlider.isPressed)
                playSlider.value = position / 1000
        }
    }

    onSong_urlChanged: {
        network.get("/music/url?" + song_url)
        infoLoader.item.updateInfo(pic_url, song_name, singer)
    }

    Row {
        id: playBtnRow
        anchors.left: parent.left
        anchors.leftMargin: 25
        width: 170
        height: parent.height
        spacing: 25

        //上一首
        Button {
            id: previousBtn
            width: 30
            height: 30
            anchors.verticalCenter: parent.verticalCenter
            background:Rectangle {
                anchors.fill: parent
                color: "transparent"
            }

            contentItem: Image {
                anchors.fill: parent
                source: "qrc:/res/prev.svg"
                verticalAlignment: Label.AlignVCenter
                horizontalAlignment: Label.AlignHCenter
            }

            ToolTip.visible: previousBtn.hovered
            ToolTip.delay: 500

            ToolTip.text: "上一首"

            onClicked: {

            }
        }

        //播放或暂停
        Button {
            id: playBtn
            width: 30
            height: 30
            anchors.verticalCenter: parent.verticalCenter
            state: "pause"
            background:Rectangle {
                anchors.fill: parent
                color: "transparent"
            }

            contentItem: Image {
                anchors.fill: parent
                source: playBtn.state == 'pause' ? "qrc:/res/pause.svg" : "qrc:/res/play.svg"
                verticalAlignment: Label.AlignVCenter
                horizontalAlignment: Label.AlignHCenter
            }

            states: [
                State {
                    name: "play"
                    PropertyChanges {
                        target: playBtn
                        ToolTip.text: "暂停"
                    }
                },
                State {
                    name: "pause"
                    PropertyChanges {
                        target: playBtn
                        ToolTip.text: "播放"
                    }
                }
            ]

            ToolTip.visible: playBtn.hovered
            ToolTip.delay: 500
            ToolTip.text: "播放"

            onClicked: {
                if (playBtn.state === "play") {
                    playBtn.state = "pause"
                    mediaplayer.pause()
                } else {
                    playBtn.state = "play"
                    mediaplayer.play()
                }
            }
        }

        //下一首
        Button {
            id: nextBtn
            width: 30
            height: 30
            anchors.verticalCenter: parent.verticalCenter
            background:Rectangle {
                anchors.fill: parent
                color: "transparent"
            }

            contentItem: Image {
                anchors.fill: parent
                source: "qrc:/res/next.svg"
                verticalAlignment: Label.AlignVCenter
                horizontalAlignment: Label.AlignHCenter
            }

            ToolTip.visible: nextBtn.hovered
            ToolTip.delay: 500
            ToolTip.text: "下一首"

            onClicked: {
                nextSong()
            }
        }
    }

    //当前歌曲已播放多长时间
    Label {
        id: playedTime
        anchors.left: playBtnRow.right
        anchors.leftMargin: 10
        width: 30
        height: parent.height
        text: "00:00"
        color: g_fontNormal
        font.pixelSize: 14
        font.family: g_fontFamily
        verticalAlignment: Label.AlignVCenter
        horizontalAlignment: Label.AlignRight
    }

    //歌曲播放进度条
    PlaySlider {
        id: playSlider
        anchors {
            //通过左右位置来设置width，但是会出现Binding loop detected for property "implicitWidth"，效果却是对的
            left: playedTime.right
            leftMargin: 3
            right: totalTime.left
            rightMargin: 3
            verticalCenter: parent.verticalCenter
        }
        //width: 400
        height: 15
        minValue: 0.0
        maxValue: root.song_length
        releasedFunc: function () {
            mediaplayer.seek(playSlider.value * 1000)
        }

        onValueChanged: {
            playedTime.text = durationFormat(playSlider.value)
            playSliderChanged(playSlider.value)
            if(playSlider.value===maxValue)
                playFinished()
        }

        onMoved: {
            mediaplayer.seek(playSlider.value * 1000)
        }
    }

    //歌曲时长
    Label {
        id: totalTime
        anchors.right: vBtn.left
        anchors.rightMargin: 15
        width: 30
        height: parent.height
        text: durationFormat(root.song_length)
        color: g_fontNormal
        font.pixelSize: 14
        font.family: g_fontFamily
        verticalAlignment: Label.AlignVCenter
        horizontalAlignment: Label.AlignLeft
    }

    //音量调节图标
    Button {
        property real volume: 50 //当前的音量
        id: vBtn
        anchors.right: vSlider.left
        anchors.rightMargin: 3
        anchors.verticalCenter: parent.verticalCenter
        width: 30
        height: 30
        state: "volume"

        background: Rectangle {
            anchors.fill: parent
            color: root.color
        }

        contentItem: Image {
            anchors.fill: parent
            verticalAlignment: Label.AlignVCenter
            horizontalAlignment: Label.AlignHCenter
            source: vBtn.state == "volume" ? "qrc:/res/sound.svg" : "qrc:/res/mute.svg"
        }

        ToolTip.visible: vBtn.hovered
        ToolTip.delay: 500
        ToolTip.text: "静音"

        states: [
            State {
                name: "volume"
                PropertyChanges {
                    target: vBtn
                    ToolTip.text: "静音"
                }
            },
            State {
                name: "mute"
                PropertyChanges {
                    target: vBtn
                    ToolTip.text: "恢复音量"
                }
            }
        ]

        onClicked: {
            if (vBtn.state === "volume") {
                vBtn.state = "mute"
                vBtn.volume = vSlider.value
                vSlider.value = 0
            } else {
                vBtn.state = "volume"
                vSlider.value = vBtn.volume
            }
        }
    }

    //音量调节
    PlaySlider {
        id: vSlider
        anchors.right: playOrder.left
        anchors.rightMargin: 10
        anchors.verticalCenter: parent.verticalCenter
        width: 100
        height: 15
        minValue: 0.0
        maxValue: 100.0
        isVisible: false
        value: 50

        property real volume: QtMultimedia.convertVolume(
                                  vSlider.value / 100,
                                  QtMultimedia.LogarithmicVolumeScale,
                                  QtMultimedia.LinearVolumeScale)

        onValueChanged: {
            vBtn.state = value ? "volume" : "mute"
        }
    }

    //播放顺序
    Button {
        id: playOrder
        anchors.right: playlist.left
        anchors.rightMargin: 10
        anchors.verticalCenter: parent.verticalCenter
        width: 20
        height: 20
        state: "order"
        property string source: "qrc:/res/order.svg"

        background: Rectangle {
            anchors.fill: parent
            color: 'transparent'
        }

        contentItem: Image {
            anchors.fill: parent
            source: playOrder.source
            verticalAlignment: Label.AlignVCenter
            horizontalAlignment: Label.AlignHCenter
        }

        ToolTip.visible: playOrder.hovered
        ToolTip.delay: 500
        ToolTip.text: "顺序播放"

        states: [
            State {
                name: "order"
                PropertyChanges {
                    target: playOrder
                    source: "qrc:/res/order.svg"
                    ToolTip.text: "顺序播放"
                }
            },
            State {
                name: "list"
                PropertyChanges {
                    target: playOrder
                    source: "qrc:/res/repeat.svg"
                    ToolTip.text: "列表循环"
                }
            },
            State {
                name: "single"
                PropertyChanges {
                    target: playOrder
                    source: "qrc:/res/repeatone.svg"
                    ToolTip.text: "单曲循环"
                }
            },
            State {
                name: "random"
                PropertyChanges {
                    target: playOrder
                    source: "qrc:/res/random.svg"
                    ToolTip.text: "随机播放"
                }
            }
        ]

        onClicked: {
            switch (playOrder.state) {
            case "order":
                playOrder.state = "list"
                break
            case "list":
                playOrder.state = "single"
                break
            case "single":
                playOrder.state = "random"
                break
            case "random":
                playOrder.state = "order"
                break
            }
        }
    }

    //歌曲列表
    Button {
        id: playlist
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.verticalCenter: parent.verticalCenter
        width: 30
        height: 30

        ToolTip.visible: playlist.hovered
        ToolTip.delay: 500
        ToolTip.text: "打开播放列表"

        background: Rectangle {
            anchors.fill: parent
            color: 'transparent'
        }

        contentItem: Image {
            anchors.fill: parent
            source: "qrc:/res/playlist.svg"
            verticalAlignment: Label.AlignVCenter
            horizontalAlignment: Label.AlignHCenter
        }

        onClicked: {

        }
    }

    //显示歌名、歌手等信息的窗口
    Loader {
        id: infoLoader
        anchors.left: parent.left
        anchors.bottom: parent.top
        width: 200
        height: 65
        visible: mediaplayer.status === MediaPlayer.NoMedia
                 || mediaplayer.status === MediaPlayer.UnknownStatus ? false : true
        source: "MinWindow.qml"
    }
}
