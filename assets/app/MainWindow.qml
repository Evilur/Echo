import QtQuick
import 'MainWindow'
import 'qrc:/component/control'
import 'qrc:/js/color.mjs' as Color

Window {
    id: root
    visible: true
    width: 1280
    height: 720
    minimumWidth: 425
    minimumHeight: 450
    title: 'Ping'

    StatusBar {
        id: statusBar
        anchors {
            top: parent.top
            right: parent.right
            left: parent.left
        }
        height: 50
        color: Color.MANTLE

    }

    ChatList {
        id: chatList
        anchors {
            top: statusBar.bottom
            bottom: parent.bottom
            left: parent.left
        }
        width: 500
        color: Color.MANTLE
    }

    MessageArea {
        id: messageArea
        anchors {
            top: statusBar.bottom
            right: parent.right
            bottom: parent.bottom
            left: chatList.right
        }
        color: Color.BASE
    }

    BurgerMenu {
        id: burgerMenu
    }

    /* Resize the chat list */
    onWidthChanged: chatList.resize()
}