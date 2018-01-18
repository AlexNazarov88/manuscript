TEMPLATE = app

QT += qml quick widgets quickcontrols2
CONFIG += c++11

SOURCES += main.cpp \
    editlogic.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    editlogic.h


#Application version
VERSION_MAJOR = 0
VERSION_MINOR = 1
VERSION_BUILD = 10

DEFINES += "VERSION_MAJOR=$$VERSION_MAJOR"\
       "VERSION_MINOR=$$VERSION_MINOR"\
       "VERSION_BUILD=$$VERSION_BUILD"

#Target version
VERSION = $${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_BUILD}


RC_ICONS1 = icons/scroll.ico
