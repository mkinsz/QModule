import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.13
import Theme 1.0

Item {

     StackLayout {
         anchors.fill: parent
         currentIndex: bar.currentIndex
         Item {
             id: maskedTab
             Masked {
                anchors.centerIn: parent
             }
         }
     }

     TabBar {
          id: bar
          width: parent.width
          position: TabBar.Footer
          anchors.bottom: parent.bottom

          Repeater {
              model: ['Masked']

              TabButton {
                  text: modelData
                  width: implicitWidth
              }
          }
      }
}
