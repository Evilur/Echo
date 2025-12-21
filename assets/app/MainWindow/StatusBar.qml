import QtQuick
import 'qrc:/component/control'
import 'qrc:/js/color.mjs' as Color

Rectangle {
    /* Move the window by dragging the status bar */
    MouseArea {
        anchors.fill: parent
        cursorShape: Qt.OpenHandCursor

        property int clickPosX
        property int clickPosY

        /* Save the cursor position on the status bar */
        onPressed: (mouse) => {
            this.clickPosX = mouse.x;
            this.clickPosY = mouse.y;
        }

        /* Move the window */
        onPositionChanged: (mouse) => {
            root.x += mouse.x - this.clickPosX;
            root.y += mouse.y - this.clickPosY;
        }
    }

    /* Burger */
    Button {
        anchors {
            top: parent.top
            bottom: parent.bottom
            left: parent.left
            leftMargin: 22
        }
        width: size
        scale: pressed ? 0.8 : 1
        hoverEnabled: true

        readonly property int size: 30

        Image {
            anchors.centerIn: parent
            sourceSize {
                width: parent.size - 4
                height: parent.size - 4
            }
            source: 'qrc:/img/status-bar/burger.svg'
        }

        onEntered: ToolTip.show(this, qsTr('Menu'))
        onExited: ToolTip.hide()
        onClicked: burgerMenu.show();
    }

    /* Action Buttons */
    Row {
        component ActionButton: Button {
            anchors {
                top: parent.top
                bottom: parent.bottom
            }
            width: height * 2
            hoverEnabled: true

            property string hoverColor: Color.GREY_05
            property alias source: image.source

            Rectangle {
                anchors.fill: parent
                color: parent.containsMouse ? parent.hoverColor : 'transparent'
            }

            Image {
                id: image
                anchors.centerIn: parent
                fillMode: Image.PreserveAspectFit
            }
        }
        anchors {
            top: parent.top
            bottom: parent.bottom
            right: parent.right
        }
        ActionButton {
            source: 'qrc:/img/status-bar/collapse.svg'
            onClicked: console.log('Collapse button is clicked')
        }
        ActionButton {
            source: 'qrc:/img/status-bar/maximize.svg'
            onClicked: console.log('Maximize button is clicked')
        }
        ActionButton {
            hoverColor: Color.RED
            source: 'qrc:/img/status-bar/close.svg'
            onClicked: console.log('Close button is clicked')
        }
    }
}