INCLUDEPATH += $$PWD
SOURCES += $$PWD/openglwindow.cpp \
    gamewindow.cpp \
    camera.cpp \
    entity.cpp \
    ball.cpp \
    level.cpp
HEADERS += $$PWD/openglwindow.h \
    gamewindow.h \
    camera.h \
    entity.h \
    ball.h \
    level.h

SOURCES += \
    main.cpp

target.path = .
INSTALLS += target

