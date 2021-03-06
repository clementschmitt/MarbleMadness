INCLUDEPATH += $$PWD
SOURCES += $$PWD/openglwindow.cpp \
    gamewindow.cpp \
    camera.cpp \
    entity.cpp \
    ball.cpp \
    level.cpp \
    plateform.cpp \
    staticConstant.cpp \
    light.cpp \
    face.cpp
HEADERS += $$PWD/openglwindow.h \
    gamewindow.h \
    camera.h \
    entity.h \
    ball.h \
    level.h \
    plateform.h \
    staticConstant.h \
    light.h \
    face.h

SOURCES += \
    main.cpp

target.path = .
INSTALLS += target

RESOURCES += \
    gestionnaire.qrc
