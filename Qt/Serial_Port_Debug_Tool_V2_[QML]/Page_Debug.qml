import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.5

Page {
    id: page
    property alias textArea: textArea
    property alias textField: textField
    property alias roundButton: roundButton
    transformOrigin: Item.Center

    states: [
        State {
            name: "State2"

            PropertyChanges {
                target: button
                anchors.horizontalCenterOffset: 0
                anchors.verticalCenterOffset: -33
            }

            PropertyChanges {
                target: rectangle
                width: 204
                anchors.leftMargin: 1
            }
        }
    ]

    ScrollView {
        id: scrollView
        width: page.width * 2 / 3 - 1
        anchors.bottom: textField.top
        anchors.bottomMargin: 1
        anchors.left: parent.left
        anchors.leftMargin: 1
        anchors.top: parent.top
        anchors.topMargin: 1
        //background: Rectangle {color: "#afafaf"}

        TextArea {
            id: textArea
            text: qsTr("")
            wrapMode: Text.WrapAnywhere
            renderType: Text.NativeRendering
            verticalAlignment: Text.AlignBottom
            KeyNavigation.priority: KeyNavigation.BeforeItem
            KeyNavigation.tab: textField
            selectByKeyboard: true
            selectByMouse: true
            background: Rectangle {
                color: "transparent"
            }
        }
    }

    TextField {
        id: textField
        width: page.width * 2 / 3 - 1
        height: 40
        text: qsTr("")
        anchors.left: parent.left
        anchors.leftMargin: 1
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 1
        renderType: Text.QtRendering
        color: "blue"
        background: Rectangle {
            color: "#afafaf"
        }
        Keys.onReturnPressed: {
            textArea.append(textField.text)
            textField.clear()
        }
    }

    Rectangle {
        id: rectangle
        width: page.width / 3
        color: "#e9e9e9"
        radius: 1
        anchors.top: parent.top
        anchors.topMargin: 1
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 1
        anchors.right: parent.right
        anchors.rightMargin: 1

        RoundButton {
            id: roundButton
            x: rectangle.width - 100
            y: page.height -100
            text: qsTr("→")
            width: 60
            height: 60
            font.bold: true
            font.pixelSize: 16
            highlighted: true
            Material.accent: Material.Teal
        }

        Button {
            id: button
            text: qsTr("Open")
            anchors.verticalCenterOffset: -30
            anchors.horizontalCenterOffset: 0
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }
    }
}





/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
