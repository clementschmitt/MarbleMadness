INCLUDEPATH += $$PWD
SOURCES += $$PWD/openglwindow.cpp \
    gamewindow.cpp \
    camera.cpp \
    entity.cpp \
    ball.cpp \
    level.cpp \
    plateform.cpp
HEADERS += $$PWD/openglwindow.h \
    gamewindow.h \
    camera.h \
    entity.h \
    ball.h \
    level.h \
    plateform.h

SOURCES += \
    main.cpp

target.path = .
INSTALLS += target
