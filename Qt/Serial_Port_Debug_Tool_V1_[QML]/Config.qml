pragma Singleton
import QtQuick 2.12

QtObject {
    id: app_config
    // window
    property int win_width: 720
    property int win_height: 540
    property int win_minwidth: 720
    property int win_minheight: 540
    // menubar
    property int mb_height: 26
    // menubar_item
    property int mbi_width: 50
    property int mbi_height: app_config.mb_height
    // menu
    property int m_width: 160
    // menu_item
    property int mi_height: app_config.mb_height
    // footer
    property int ft_height: 22
    // config
    property int cfg_tab_height: 20
}
