import QtQuick
import 'qrc:/component/control'
import 'qrc:/component/visual'
import 'qrc:/js/color.mjs' as Color
import 'qrc:/js/chat_type.mjs' as ChatType

Rectangle {
    readonly property real minWidth: 75
    property Item activeChat
    property bool collapsed

    /**
     * Resize the chat list
     * @param newWidth A new chat list width
     */
    function resize(newWidth = 0): void {
        if (newWidth !== 0 && (newWidth > 300 || newWidth < this.minWidth))
            this.width = newWidth;
        if (messageArea.width < 350) this.width = parent.width - 350;
        if (this.width < 250) {
            this.width = this.minWidth;
            this.collapsed = true;
        } else this.collapsed = false;
    }

    Scrollable {
        anchors.fill: parent
        scrollable: chatColumn

        Column {
            id: chatColumn
            width: parent.width

            Repeater {
                model: 100
                Chat {
                    title: 'Агрессивно-пассивные кабачки'
                    lastMessageTimestamp: Date.now() - index * 3 * 60 * 60 * 1000
                    membersNumber: index + 1
                    chatType: ChatType.CHAT
                }
            }
        }
    }

    /* Resizer */
    MouseArea {
        height: parent.height
        width: 20
        cursorShape: Qt.SizeHorCursor
        anchors {
            left: parent.right
            top: parent.top
        }

        /* Resize the chat list */
        onPositionChanged: (mouse) => {
            parent.resize(parent.width + mouse.x);
        }
    }
}