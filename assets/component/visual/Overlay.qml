import QtQuick

Rectangle {
    anchors.fill: parent
    color: 'transparent'
    visible: color.a > 0 ? true : false

    function show() {
        showed();
        this.color = Qt.rgba(0, 0, 0, 0.3);
    }

    signal closed();
    signal showed();

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true

        /* Swallow events */
        onClicked: {}
        onReleased: {}
        onDoubleClicked: {}
        onPositionChanged: {}
        onEntered: {}
        onWheel: {}
        onExited: {}

        /* Close the dimmer */
        onPressed: {
            closed()
            parent.color = 'transparent'
        }
    }

    /* Animation */
    Behavior on color { ColorAnimation { duration: 75 } }
}