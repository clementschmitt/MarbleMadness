INCLUDEPATH += $$PWD
SOURCES += $$PWD/openglwindow.cpp \
    gamewindow.cpp \
    camera.cpp \
    objet3d.cpp \
    model.cpp \
    entity.cpp \
    ball.cpp
HEADERS += $$PWD/openglwindow.h \
    gamewindow.h \
    camera.h \
    objet3d.h \
    model.h \
    entity.h \
    ball.h

SOURCES += \
    main.cpp

target.path = .
INSTALLS += target

RESOURCES += \
    gestionnaire.qrc
