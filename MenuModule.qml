import QtQuick 2.0
import QtQuick.Controls 1.4

MenuBar {

    Menu {
        title: "File"
        MenuItem { text: "Open..." }
        MenuItem { text: "Close" }
    }

    Menu {
        title: "Edit"
        MenuItem { text: "Cut" }
        MenuItem { text: "Copy" }
        MenuItem { text: "Paste" }
    }
}

