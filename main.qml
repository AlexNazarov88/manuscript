import QtQuick 2.7
import QtQuick.Controls 1.4
import sparkly.editorlogic 0.1

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Manuscript")


    menuBar: MenuComponent {}

    EditorLogic { id: cppeditor } // c++
    EditorComponent {}

    statusBar: StatusBarComponent { }
}


