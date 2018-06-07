TEMPLATE = app
QT += widgets #uitools
include(libs/FakeVim/fakevim/fakevim.pri)

CONFIG += c++11

#CONFIG += static
#LIBS +=
#LIBS += linux-vdso \
#        libQt5Widgets \
#        libQt5Gui \
#        libQt5Core \
#        libstdc++ \
#        libgcc_s \
#        libc \
#        libpthread \
#        libGL \
#        libm \
 #       libz \
  #      libicui18n \
   #     libicuuc \
#        libicudata \
#        libdl \
#        libgthread-2.0 \
#        libglib-2.0 \
#        ld-linux-x86-64	 \
#        libX11 \
#        libXext \
#        libpcre \
#        libxcb \
#        libXau \
#        libXdmcp \
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


# Additional import path used to resolve QML modules in Qt Creator's code model
#QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


#Application version
VERSION_MAJOR = 0
VERSION_MINOR = 1
VERSION_BUILD = 15

DEFINES += "VERSION_MAJOR=$$VERSION_MAJOR"\
       "VERSION_MINOR=$$VERSION_MINOR"\
       "VERSION_BUILD=$$VERSION_BUILD"

#Target version
VERSION = $${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_BUILD}


RC_ICONS1 = icons/scroll.ico

#DISTFILES +=

SUBDIRS += \
    fakevim



#unix:!macx: LIBS += -L/usr/lib/x86_64-linux-gnu -lX11 \
#                    -L/usr/lib/x86_64-linux-gnu -lxcb-glx \
#                    -L/usr/lib/x86_64-linux-gnu -lxcb
