import QtQuick 2.0
import QtQuick.Controls 1.4

MenuBar {
    id: appMenuBar
    Menu {
        id: fileMenu
        title: qsTr("File")
        MenuItem {
            text: qsTr("Open...")
            shortcut: "Ctrl+O"
        }
        MenuItem {
            text: qsTr("Save")
            shortcut: "Ctrl+S"
        }
        MenuItem {
            text: qsTr("Save as...")
        }

        MenuSeparator {}
        MenuItem {
            text: qsTr("Quit")
            shortcut: "Ctrl+Q"
        }
    } // file

    Menu {
        id: editMenu
        title: qsTr("Edit")
        MenuItem {
            text: qsTr("Undo")
            shortcut: "Ctrl+Z"
        }

        MenuSeparator {}
        MenuItem {
            text: qsTr("Cut")
            shortcut: "Ctrl+X"
        }
        MenuItem {
            text: qsTr("Copy")
            shortcut: "Ctrl+C"
        }
        MenuItem {
            text: qsTr("Paste")
            shortcut: "Ctrl+V"
        }

        MenuSeparator {}
        MenuItem {
            text: qsTr("Find...")
            shortcut: "Ctrl+F"
        }
        MenuItem {
            text: qsTr("Replace...")
            shortcut: "Ctrl+H"
        }

        MenuSeparator {}
        MenuItem {
            text: qsTr("Select all")
            shortcut: "Ctrl+A"
        }
        MenuItem {
            text: qsTr("Date and time")
            shortcut: "F5"
        }
    } // edit

    Menu {
        id: optionsMenu
        title: qsTr("Options")
        MenuItem {
            text: qsTr("Settings...")

        }
    } // options

    Menu {
        id: helpMenu
        title: qsTr("Help")
        MenuItem {
            text: qsTr("About Manuscript")

        }
    }
}

