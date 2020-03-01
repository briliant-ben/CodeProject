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

    SwipeView {
        id: app_sv
        anchors.fill: parent
        interactive: false
        //currentIndex: app_tb.currentIndex

        Page_Config {
            roundButton.onClicked: {
                app_sv.currentIndex = app_sv.currentIndex + 1
                roundButton.visible = false
            }
        }

        Page_Debug {
            Component.onCompleted:{
                backend.setDefaultStyleSheet(textArea.textDocument)
            }

            textField {
            }

            roundButton.onClicked: {
                app_sv.currentIndex = app_sv.currentIndex + 1
                roundButton.visible = false
                app_sv.interactive = true
                app_sv.currentIndex = Qt.binding( function(){
                    return app_tb.currentIndex;
                });
                app_tb.visible = true
            }
        }

        Page_Usage {
        }
    }

    footer: TabBar {
        id: app_tb
        height: Config.ft_height
        visible: false
        currentIndex: app_sv.currentIndex
        //onCurrentIndexChanged: {console.log("SwipeView index ", app_sv.currentIndex)}

        TabButton {
            height: Config.ftb_height
            anchors.verticalCenter: parent.verticalCenter
            text: qsTr("Config")
        }
        TabButton {
            height: Config.ftb_height
            anchors.verticalCenter: parent.verticalCenter
            text: qsTr("Debug")
        }
        TabButton {
            height: Config.ftb_height
            anchors.verticalCenter: parent.verticalCenter
            text: qsTr("Usage")
        }
    }
}
