import QtQuick 2.7
//import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import sparkly.editmodule 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Manuscript")

    EditModule {
        id: editModule
    }

    Item {
        anchors.fill: parent

        TextEdit {
            //x: 8
            //y: 80
            //width: 624
            //height: 379
            anchors.fill: parent

            textFormat: Text.PlainText
            wrapMode: Text.Wrap
            selectByMouse: true

            //font.family: customFont.name
            font.pointSize: 12
            cursorVisible: true
            focus: true

            //text: logic.text
            onTextChanged: editModule.m_text = text
        }
    } //item

}
