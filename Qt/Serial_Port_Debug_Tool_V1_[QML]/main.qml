import QtQuick 2.12
import QtQuick.Controls 2.5
import io.qt.backend 1.0
import "."

ApplicationWindow {
    id:app_main
    visible: true
    width: Config.win_width
    height: Config.win_height
    minimumWidth: Config.win_minwidth
    minimumHeight: Config.win_minheight
    title: qsTr("RealTek WLAN Debug Tool")

    Backend {
        id: backend
    }

    menuBar: MenuBar {
        id: app_mb
        height: Config.mb_height
        //background: Rectangle {color: "#ffffff"}
        delegate: MenuBarItem {
            id: app_mbi
            height: Config.mbi_height
            anchors.verticalCenter: parent.verticalCenter
            background: Rectangle {
                opacity: enabled ? 1 : 0.3
                color: app_mbi.highlighted ? "Teal" : "transparent"
            }
            contentItem: Text {
                text: app_mbi.text
                font: app_mbi.font
                opacity: enabled ? 1.0 : 0.3
                color: app_mbi.highlighted ? "#ffffff" : "#000000"
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }
        }

        Menu {
            title: qsTr("File")
            width: Config.m_width
            delegate: MenuItem {
                height: Config.mi_height
            }

            Action {
                text: qsTr("New")
                onTriggered: window.close()
            }

            Action {
                text: qsTr("Quit")
                onTriggered: Qt.quit()
            }
        }

        Menu {
            title: qsTr("Edit")
            width: Config.m_width
            delegate: MenuItem {
                height: Config.mi_height
            }

            Action { text: qsTr("Cut") }
            Action { text: qsTr("Copy") }
            Action { text: qsTr("Paste") }
        }

        Menu {
            title: qsTr("Help")
            width: Config.m_width
            delegate: MenuItem {
                height: Config.mi_height
            }

            Action { text: qsTr("About") }
        }
    }

    PageForm {
        Component.onCompleted:{
            //backend.setDefaultStyleSheet(textArea.textDocument)
        }
    }

    footer: Rectangle {
        id: app_status
        height: Config.ft_height
        color: "#D3D3D3"

        Text {
            text: qsTr("Operation Status")
            width: app_status.width * 0.6
            font.pixelSize: 12
            font.family: "Calibri"
            leftPadding: 15
            anchors.verticalCenter: parent.verticalCenter
        }
        Text {
            text: qsTr("Config Status")
            width: app_status.width * 0.4
            font.family: "Calibri"
            font.pixelSize: 12
            rightPadding: 15
            horizontalAlignment: Text.AlignRight
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.verticalCenter: parent.verticalCenter
        }
    }
}




