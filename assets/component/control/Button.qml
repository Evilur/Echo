// noinspection IncorrectFormatting

import QtQuick 6.5

Rectangle {
    signal clicked()

    MouseArea {
        anchors.fill: parent
        onClicked: parent.clicked()
    }
}