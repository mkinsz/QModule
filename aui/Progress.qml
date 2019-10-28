import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles.Flat 1.0 as Flat

Item {
    width: 300; height: 300;
    ProgressBar {
        width: 200; height: 20;
        indeterminate: true
        value: 30
        maximumValue: 100
        style: Flat.ProgressBarStyle {}
    }
}
