import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.5

Page {
    id: page
    property alias roundButton: roundButton

    RoundButton {
        id: roundButton
        x: page.width - 100
        y: page.height - 100
        width: 60
        height: 60
        text: qsTr("→")
        font.bold: true
        font.pixelSize: 16
        highlighted: true
        Material.accent: Material.Teal
    }

    Pane {
        id: pane
        width: page.width * 0.5
        height: page.height * 0.8
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        Material.elevation: 2
        /*background: Rectangle {
            width: page.width * 0.5
            height: page.height * 0.8
            radius: 5
            color: "#eeeeee"
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            gradient: "NightFade"
        }*/
    }

    DelayButton {
        id: delayButton
        x: 41
        y: 335
        text: qsTr("Delay Button")
    }
}












/*##^## Designer {
    D{i:0;height:480;width:640}
}
 ##^##*/
