import QtQuick
import QtQuick.Controls
import '../../js/color.mjs' as Color

Item {
    clip: true

    property Item scrollable

    /**
     * Scroll the scrollable item to delta
     * @param delta number of pixel to scroll
     */
    function scroll(delta) {
        /* Scroll the object */
        scrollable.y += delta;

        /* Create the stoppers */
        const minY = this.height - scrollable.height;
        if (scrollable.y < minY) scrollable.y = minY;
        if (scrollable.y > 0) scrollable.y = 0;

        /* Show the scrollbar */
        scrollbar.show();
    }

    /* Scrollbar */
    Rectangle {
        id: scrollbar
        anchors.right: parent.right
        y: -scrollable.y * parent.height / scrollable.height
        z: 9999
        width: 6
        height: parent.height * parent.height / scrollable.height
        radius: 3
        opacity: 0
        visible: opacity > 0 && parent.height < scrollable.height
        color: Color.GREY_25

        /**
         * Show the scrollbar and hide with the timer
         */
        function show() {
            this.opacity = 1;
            timer.restart();
        }

        /* Scroll with the mouse dragging */
        MouseArea {
            id: mouseArea
            anchors.fill: parent
            cursorShape: Qt.ArrowCursor
            hoverEnabled: true

            property int clickPos

            onPressed: (mouse) => {
                timer.stop();
                this.clickPos = mouse.y;
            }

            onEntered: timer.stop();

            onExited: if (!pressed) timer.restart();

            onPositionChanged: (mouse) => {
                if (pressed) parent.parent.scroll(this.clickPos - mouse.y);
            }
        }

        /* Hide the scrollbar */
        Timer {
            id: timer
            interval: 2000
            repeat: false
            onTriggered: scrollbar.opacity = 0
        }

        /* Animation */
        Behavior on opacity { NumberAnimation { duration: 75 } }
    }

    /* Scroll with a mouse */
    MouseArea {
        anchors.fill: parent
        onWheel: (wheel) => { parent.scroll(wheel.angleDelta.y) }
    }
}