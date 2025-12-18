import QtQuick
import "component/control"
import "js/color.mjs" as Color

Rectangle {
    id: chatList
    anchors {
        top: statusBar.bottom
        bottom: parent.bottom
        left: parent.left
    }
    width: 500
    color: Color.mantle

    property real minWidth: 75

    /**
     * Resize the chat list
     * @param newWidth A new chat list width
     */
    function resize(newWidth = 0): void {
        if (newWidth !== 0 && (newWidth > 300 || newWidth < this.minWidth))
            this.width = newWidth;
        if (messageArea.width < 350) this.width = parent.width - 350;
        if (this.width < 250) this.width = this.minWidth;
    }

    Column {
        anchors.fill: parent;

        /* Chats */
        Button {

        }
    }

    /* Resizer */
    MouseArea {
        height: parent.height
        width: 20
        cursorShape: Qt.SizeHorCursor
        anchors {
            horizontalCenter: parent.right
            top: parent.top
        }

        /* Resize the chat list */
        onPositionChanged: (mouse) => {
            parent.resize(parent.width + mouse.x - this.width / 2);
        }
    }

    /* New chat button */
    Button {
        property int size: 50
        width: size
        height: size
        anchors {
            right: parent.right
            bottom: parent.bottom
            margins: (parent.minWidth - size) / 2
        }
        hoverEnabled: true
        onEntered: ToolTip.show(this, qsTr('Create a new chat'));
        onExited: ToolTip.hide();

        Image {
            source: 'qrc:/img/chat-list/new-chat.svg'
            sourceSize {
                width: parent.size
                height: parent.size
            }
        }

        onClicked: console.log('New chat button is clicked')
    }
}