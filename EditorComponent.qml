import QtQuick 2.0
import QtQuick.Controls 1.4

TabView {
    id: tabView
    anchors.fill: parent

    TextArea {
        id: appEditor
        anchors.fill: parent

        textFormat: Text.PlainText
        wrapMode: Text.Wrap
        selectByMouse: true

        //font.pointSize: 12
        //cursorVisible: true
        focus: true

        text: editLogic.m_text
        onTextChanged: editLogic.m_text = text
    }
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
        onTextChanged: editLogic.m_text = text
    }

} //item
*/
