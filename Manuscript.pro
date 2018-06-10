TEMPLATE = app
QT += widgets #uitools
include(libs/FakeVim/fakevim/fakevim.pri)

CONFIG += c++11 x11

#Resources
RC_ICONS1 = icons/scroll.ico

#Subprojects
SUBDIRS += \
    fakevim

#static { # Everything below takes effect with CONFIG += static
#    CONFIG += static
#    #QTPLUGIN += qsqloci qgif
#    DEFINES += STATIC #// Equivalent to "#define STATIC" in source code
#    message("Static build.")
#}

HEADERS += \
    mainwindow.h \
    editor.h \
    core.h

SOURCES += main.cpp \
    editormodule.cpp \
    mainwindow.cpp \
    core.cpp

RESOURCES += \
    app_res.qrc

LIBS += -L"/opt/$${TARGET}/libs"
        -lQt5Widgets
        -lQt5Gui
        -lQt5Core
        -lstdc++
        -lgcc_s
        -lc
        -lpthread
        -lgobject-2.0
        -lg-l-2.0
        -lX11
        -lm
        -lpng12
        -lharfbuzz
        -lz
        -lGL
        -licui18n
        -licuuc
        -lpcre16
        -ldl
        -lrt
        -ld-linux-x86-64
        -lffi
        -lpcre
        -lxcb
        -lfreetype
        -lgraphite2
        -lexpat
        -lxcb-dri3
        -lxcb-present
        -lxcb-sync
        -lxshmfence
        -lglapi
        -lXext
        -lXdamage
        -lXfixes
        -lX11-xcb
        -lxcb-glx
        -lxcb-dri2
        -lXxf86vm
        -ldrm
        -licudata
        -lXau
        -lXdmcp

#
#BUILD
#
#build files directory
OBJECTS_DIR = $$OUT_PWD/tmp
MOC_DIR = $$OUT_PWD/tmp
RCC_DIR = $$OUT_PWD/tmp

# copy files to build directory
copydata.commands = $(COPY_DIR) $$PWD/libs/ \
             $$PWD/LICENSE \
             $$PWD/Manuscript.sh \
             $$PWD/README.pdf \
             $$PWD/changelog.txt $$OUT_PWD
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata

#
#DEPLOYMENT
#
# Default rules for deployment.
libs.path = /opt/$${TARGET}
libs.files = $$OUT_PWD/libs/

other_files.path = /opt/$${TARGET}
other_files.files = $$OUT_PWD/LICENSE \
             $$OUT_PWD/README.pdf \
             $$OUT_PWD/changelog.txt

script.path = /opt/$${TARGET}/bin
script.files = $$OUT_PWD/Manuscript.sh

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target libs other_files script


# Modify rpath by adding gcc command
QMAKE_LFLAGS += -Wl,-rpath,"'\$$ORIGIN/../libs'"



#Application version
VERSION_MAJOR = 0
VERSION_MINOR = 1
VERSION_BUILD = 15

DEFINES += "VERSION_MAJOR=$$VERSION_MAJOR"\
       "VERSION_MINOR=$$VERSION_MINOR"\
       "VERSION_BUILD=$$VERSION_BUILD"

#Target version
VERSION = $${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_BUILD}
