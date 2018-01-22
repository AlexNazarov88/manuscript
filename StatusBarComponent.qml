import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0

StatusBar {
    id: statusBar
    anchors.fill: parent //

    RowLayout {
        anchors.fill: parent
        Label {}
            //text: "Line: " + cppeditor.document().textCursor.blockNumber } //
    }
}
