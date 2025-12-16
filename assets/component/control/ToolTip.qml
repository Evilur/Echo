import QtQuick
import "qrc:/js/color.mjs" as Color

Window {
    width: Math.min(tooltipText.contentWidth + 18, 500)
    height: Math.min(tooltipText.contentHeight + 6, 500)
    flags: Qt.ToolTip
    x: root.x
    y: root.y
    color: Color.grey_05

    function show(item, text) {
        const itemPos = item.mapToGlobal(0, 0);
        tooltipText.text = text;
        this.x = itemPos.x + (item.width - width) / 2;
        this.y = itemPos.y - height - 10;
        this.visible = true;
    }

    function hide() { this.visible = false; }

    Text {
        id: tooltipText
        width: parent.width
        anchors.centerIn: parent
        wrapMode: Text.WordWrap
        color: Color.grey_50
        font {
            family: 'JetBrains Mono NL'
            pixelSize: 18
        }
        horizontalAlignment: Text.AlignHCenter
    }
}
