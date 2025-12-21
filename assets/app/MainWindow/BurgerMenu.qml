import QtQuick
import 'qrc:/component/visual'
import 'qrc:/js/color.mjs' as Color

Overlay {
    Rectangle {
        id: menu
        anchors {
            top: parent.top
            bottom: parent.bottom
            left: parent.left
            leftMargin: parent.visible ? 0 : -width
        }
        width: 350
        color: Color.MANTLE

        Behavior on anchors.leftMargin {
            NumberAnimation {
                duration: 75
            }
        }
    }

    onShowed: menu.anchors.leftMargin = 0
    onClosed: menu.anchors.leftMargin = -menu.width
}