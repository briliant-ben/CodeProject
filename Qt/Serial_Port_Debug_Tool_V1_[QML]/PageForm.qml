import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.5
//import QtQuick.Dialogs 1.3

Page {
    id: page
    anchors.fill: parent
    property alias textArea: textArea

    Pane {
        id: pane
        width: 252
        verticalPadding: 0
        horizontalPadding: 0
        anchors.left: parent.left
        anchors.leftMargin: 1
        anchors.top: parent.top
        anchors.topMargin: 1
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        Material.elevation: 4

        TabBar {
            id: tabBar
            width: pane.width * 2/3
            height: 30
            anchors.top: parent.top
            anchors.topMargin: 2
            anchors.left: parent.left
            anchors.leftMargin: 3
            font.pixelSize: 11
            spacing: 1
            currentIndex: swipeView.currentIndex

            TabButton {
                id: cfg_tab
                width: tabBar.width/2
                height: tabBar.height
                text: qsTr("Config")
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.verticalCenter: parent.verticalCenter
            }

            TabButton {
                id: usg_tab
                width: tabBar.width/2
                height: tabBar.height
                text: qsTr("Usage")
                anchors.left: cfg_tab.right
                anchors.leftMargin: 0
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        SwipeView {
            id: swipeView
            clip: true
            width: pane.width
            height: pane.height - tabBar.height - 6
            spacing: 3
            verticalPadding: 0
            horizontalPadding: 3
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            currentIndex: tabBar.currentIndex

            Column {
                id: cfg_tab_col
                spacing: 5
                bottomPadding: 3

                Pane {
                    width: cfg_tab_col.width - 1
                    height: cfg_tab_col.height * 2/3 - 5
                    Material.background: "Grey"
                    Material.elevation: 4
                    Button {
                        id: name
                        text: qsTr("text")
                    }
                }
                Pane {
                    width: cfg_tab_col.width - 1
                    height: cfg_tab_col.height * 1/3 - 5
                    Material.background: "Grey"
                    Material.elevation: 4

                    Grid {
                        rows: 2
                        columns: 2
                        spacing: 5
                        anchors.fill: parent
                        verticalItemAlignment: Grid.AlignVCenter
                        horizontalItemAlignment: Grid.AlignHCenter

                        Label {text: qsTr("Path:")}
                        Button {
                            id: cfg_path_btn
                            text: qsTr("Location")
                        }
                        ComboBox {
                            width: parent.width * 2/3
                            model: ["*.zip", "*.rar", "*.7z"]
                        }
                        Button {
                            id: cfg_form_btn
                            text: qsTr("Foramt")
                        }

                    }
                }
            }

            Item {
                Button {
                    x: 20
                    width: 40
                    height: 40
                    text: qsTr("aaa")
                }
            }

        }


    }

    /*
    FileDialog {
        id: fileDialog
        visible: fileDialogVisible.checked
        modality: fileDialogModal.checked ? Qt.WindowModal : Qt.NonModal
        title: fileDialogSelectFolder.checked ? "Choose a folder" :
            (fileDialogSelectMultiple.checked ? "Choose some files" : "Choose a file")
        selectExisting: fileDialogSelectExisting.checked
        selectMultiple: fileDialogSelectMultiple.checked
        selectFolder: fileDialogSelectFolder.checked
        nameFilters: [ "Image files (*.png *.jpg)", "All files (*)" ]
        selectedNameFilter: "All files (*)"
        sidebarVisible: fileDialogSidebarVisible.checked
        onAccepted: {
            console.log("Accepted: " + fileUrls)
            if (fileDialogOpenFiles.checked)
                for (var i = 0; i < fileUrls.length; ++i)
                    Qt.openUrlExternally(fileUrls[i])
        }
        onRejected: { console.log("Rejected") }
    }*/

    ScrollView {
        id: scrollView
        width: page.width - pane.width - 10
        anchors.top: parent.top
        anchors.topMargin: 1
        anchors.right: parent.right
        anchors.rightMargin: 4
        anchors.bottom: text_edit_rec.top
        anchors.bottomMargin: 6
        background: Rectangle {color: "Black"}

        TextArea {
            id: textArea
            clip: true
            font.preferShaping: false
            font.kerning: false
            //anchors.fill: parent
            wrapMode: Text.WrapAnywhere
            verticalAlignment: Text.AlignBottom
            KeyNavigation.priority: KeyNavigation.BeforeItem
            KeyNavigation.tab: textField
            selectByKeyboard: true
            selectByMouse: true
            background: Rectangle {color: "transparent"}
            font {pixelSize: 12; family: "Calibri"}
            color: "white"
        }
    }

    Rectangle {
        id: text_edit_rec
        width: scrollView.width
        height: 32
        anchors.right: parent.right
        anchors.rightMargin: 4
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
        color: "Black" //border.color: textInput.enabled ? "Grey" : "transparent"
        radius: 2

        TextEdit {
            id: textField
            anchors.fill: text_edit_rec
            color: "White"
            font.preferShaping: false
            font.kerning: false
            verticalAlignment: TextInput.AlignVCenter
            font {pixelSize: 12; family: "Calibri"}
            Keys.onReturnPressed: {
                textArea.append(textField.text)
                textField.clear()
            }
        }
    }
}





/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
