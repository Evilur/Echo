import QtQuick
import 'qrc:/component/control'
import 'qrc:/component/visual'
import 'qrc:/js/color.mjs' as Color
import 'qrc:/js/chat_type.mjs' as ChatType

Button {
    id: chat
    anchors {
        left: parent.left
        right: parent.right
    }
    height: chatList.minWidth
    hoverEnabled: true

    readonly property real margin: 12.5

    property bool isActive: false

    property alias title: title.text
    property double lastMessageTimestamp
    property int membersNumber
    property int chatType

    /* Background */
    Rectangle {
        color: parent.isActive ? Color.BLUE_BRIGHT :
            parent.containsMouse ? Color.GREY_00 : 'transparent'
        anchors.fill: parent
    }

    /* Avatar */
    Rectangle {
        id: avatar
        anchors {
            left: parent.left
            top: parent.top
            margins: parent.margin
        }
        width: 50
        height: 50
        radius: width / 2
        color: Color.CRUST
    }

    /* Title */
    AppText {
        id: title
        anchors {
            top: avatar.top
            left: avatar.right
            leftMargin: parent.margin
            right: chat.right
            rightMargin: parent.margin
        }
        elide: Text.ElideRight
        color: Color.TEXT
        font {
            pixelSize: 20
            bold: true
        }
    }

    /* Chat type image */
    Image {
        id: typeImage
        anchors {
            verticalCenter: memberNumberText.verticalCenter
            left: title.left
        }
        source: {
            let imageName;
            switch (parent.chatType) {
                case ChatType.NOTES:
                    imageName = 'notes';
                    break;
                case ChatType.CHAT:
                    imageName = parent.membersNumber <= 2 ? 'person' : 'group';
                    break;
                case ChatType.SERVER:
                    imageName = 'server';
                    break;
                case ChatType.CHANNEL:
                    imageName = 'channel';
            }
            return `qrc:/img/chat-list/${imageName}.svg`;
        }
        sourceSize {
            width: 16
            height: 16
        }
    }

    /* Number of chat members */
    AppText {
        id: memberNumberText
        anchors {
            top: title.bottom
            right: lastMessageDate.left
            left: typeImage.right
            rightMargin: parent.margin
            leftMargin: 5
        }
        elide: Text.ElideRight
        text: qsTr('%n chat member(s)', '', chat.membersNumber)
        font.pixelSize: 18
    }

    /* Last message date */
    AppText {
        id: lastMessageDate
        visible: !chatList.collapsed
        anchors {
            right: chat.right
            rightMargin: parent.margin
            bottom: memberNumberText.bottom
        }
        text: {
            /* Get dates */
            const currentDate = new Date();
            const messageDate = new Date(parent.lastMessageTimestamp);

            /* Last 12 hours */
            if (currentDate.getTime() - parent.lastMessageTimestamp < 43200000)
                return messageDate.toLocaleTimeString(Locale.ShortFormat);

            /* Get rid of the time and save only the dates */
            currentDate.setHours(0, 0, 0, 0);
            messageDate.setHours(0, 0, 0, 0);
            const currentDateDay = currentDate.getTime() / 86400000;
            const messageDateDay = messageDate.getTime() / 86400000;

            /* Today */
            if (currentDateDay === messageDateDay)
                return qsTr('Today');

            /* Yesterday */
            const dayDelta = currentDateDay - messageDateDay;
            if (dayDelta === 1)
                return qsTr('Yesterday');

            /* Last 7 days */
            if (dayDelta <= 7)
                return qsTr('%n day(s) ago', '', dayDelta);

            /* Default result */
            return messageDate.toLocaleDateString(Locale.ShortFormat);
        }
        color: Color.GREY_75

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true

            onEntered: {
                const date = new Date(parent.parent.lastMessageTimestamp);
                ToolTip.show(this, date.toLocaleString(Locale.ShortFormat));
            }

            onExited: ToolTip.hide()
        }
    }

    onClicked: {
        /* Make the last active chat unactive */
        if (chatList.activeChat)
            chatList.activeChat.isActive = false;

        /* Make this chat active */
        this.isActive = true;
        chatList.activeChat = this;
    }
}
