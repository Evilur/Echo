import QtQuick
import "qrc:/component/control"
import "qrc:/js/color.mjs" as Color

Window {
    id: root
    visible: true
    width: 1280
    height: 720
    minimumWidth: 425
    minimumHeight: 450
    title: 'Ping'

    /* Status Bar */
    Rectangle {
        id: statusBar
        anchors {
            top: parent.top
            right: parent.right
            left: parent.left
        }
        height: 45
        color: Color.mantle

        /* Move the window by dragging the status bar */
        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.OpenHandCursor

            property int clickPosX
            property int clickPosY

            /* Save the cursor position on the status bar */
            onPressed: (mouse) => {
                this.clickPosX = mouse.x
                this.clickPosY = mouse.y
            }

            /* Move the window */
            onPositionChanged: (mouse) => {
                root.x += mouse.x - this.clickPosX
                root.y += mouse.y - this.clickPosY
            }
        }

        /* Action Buttons */
        component ActionButton: Rectangle {
            height: parent.height
            width: parent.height * 2
            property alias source: image.source

            /* Default and hover colors */
            color: hoverHandler.hovered ? hoverColor : "transparent"
            property string hoverColor: Color.grey_05

            /* OnClicked signal */
            signal clicked()

            Image {
                id: image
                anchors.centerIn: parent
                fillMode: Image.PreserveAspectFit
            }

            MouseArea {
                /* Fill the parent */
                anchors.fill: parent

                /* Change the cursors type to pointer */
                cursorShape: Qt.PointingHandCursor

                /* Send the onClicked signal */
                onClicked: parent.clicked()
            }

            HoverHandler { id: hoverHandler }
        }
        ActionButton {
            id: collapseButton
            anchors.right: maximizeButton.left
            anchors.top: parent.top
            source: 'qrc:/img/status-bar/collapse.svg'
        }
        ActionButton {
            id: maximizeButton
            anchors.right: closeButton.left
            anchors.top: parent.top
            source: 'qrc:/img/status-bar/maximize.svg'
        }
        ActionButton {
            id: closeButton
            hoverColor: Color.red
            anchors.right: parent.right
            anchors.top: parent.top
            source: 'qrc:/img/status-bar/close.svg'
        }
    }

    /* Chat List */
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
            if (messageArea.width < 350) this.width = root.width - 350;
            if (this.width < 250) this.width = this.minWidth;
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
        Image {
            id: newChatButton
            property int size: 50
            anchors {
                right: parent.right
                bottom: parent.bottom
                margins: (parent.minWidth - size) / 2
            }
            source: 'qrc:/img/chat-list/new-chat.svg'
            sourceSize {
                width: size
                height: size
            }

            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                onEntered: toolTip.show(this, qsTr('Create a new chat'));
                onExited: toolTip.hide();
                cursorShape: Qt.PointingHandCursor
            }
        }
    }

    /* Message Area */
    Rectangle {
        id: messageArea
        anchors {
            top: statusBar.bottom
            right: parent.right
            bottom: parent.bottom
            left: chatList.right
        }
        color: Color.base

        /* Placeholder message */
        Rectangle {
            id: placeholderMessage
            anchors.centerIn: parent
            color: Color.grey_10
            radius: 10

            width: placeholderMessageText.contentWidth + 20
            height: placeholderMessageText.contentHeight + 8

            Text {
                id: placeholderMessageText
                text: qsTr('To start messaging open a chat or create a new one')
                anchors.centerIn: parent
                color: Color.text
                font.family: 'JetBrains Mono NL'
                font.pixelSize: 18
                wrapMode: Text.WordWrap
                width: Math.min(implicitWidth, messageArea.width - 50)
                horizontalAlignment: Text.AlignHCenter
            }
        }
    }

    /* Resize the chat list */
    onWidthChanged: chatList.resize()

    /* Tooltip object */
    ToolTip { id: toolTip }
}