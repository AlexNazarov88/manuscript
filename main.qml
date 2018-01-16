import QtQuick 2.7
import QtQuick.Controls 1.4
import sparkly.editmodule 0.1

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Manuscript")


    menuBar: MenuModule {}

    EditModule { id: editModule}

    Item {
        //Content area
        anchors.fill: parent

        TextEdit {
            anchors.fill: parent

            textFormat: Text.PlainText
            wrapMode: Text.Wrap
            selectByMouse: true

            //font.family: customFont.name
            font.pointSize: 12
            cursorVisible: true
            focus: true

            //color: "white"


            //text: logic.text
            onTextChanged: editModule.m_text = text
        }
    } //item

}
