QT += 3dcore 3drender 3dquick 3dinput 3dextras qml quick 3dquickextras sql designer


CONFIG += c++11

SOURCES += main.cpp \
    user.cpp \
    sqlquerymodel.cpp \
    task.cpp \
    contoller.cpp \
    ./Network/host.cpp \
    ./Network/networkmodel.cpp \
    ./Network/networkxml.cpp \
    ./Network/task_network.cpp \
    Network/dns.cpp \
    CustomLibrary/vstandarditemmodel.cpp \
    Network/networkattributes.cpp \
    Domain/domainxml.cpp \
    Domain/domainmodel.cpp \
    Domain/domainattributes.cpp \
    Domain/Elements/os.cpp

RESOURCES += qml.qrc \

LIBS += -lvirt


# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = /home/dravigon/qt/Qvirinterface


# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    user.h \
    sqlquerymodel.h \
    task.h \
    contoller.h \
    ./Network/host.h \
    ./Network/networkmodel.h \
    ./Network/networkxml.h \
    Network/dns.h \
    CustomLibrary/vstandarditemmodel.h \
    Network/networkattributes.h \
    Domain/domainxml.h \
    Domain/domainmodel.h \
    Domain/domainattributes.h \
    Domain/Elements/os.h

DISTFILES += \
    requirments \
    ../LICENSE \
    ../README.md

SUBDIRS += QMLTermWidgets

LIBGL_ALWAYS_SOFTWARE=1
