import QtQuick 2.7
import QtQuick.Controls 1.4

TextArea {
    id: qmlEditor
    anchors.fill: parent

    textFormat: Text.PlainText
    wrapMode: Text.Wrap
    selectByMouse: true

    //font.pointSize: 12
    //cursorVisible: true
    focus: true

    //text: EditorLogic.toPlainText()
    //textDocument: EditorLogic.document() //
    //onTextChanged: EditorLogic.setPlainText(text)
}



/*
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
        onTextChanged: EditorLogic.m_text = text
    }

} //item
*/
