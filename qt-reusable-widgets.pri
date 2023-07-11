INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

QT *= widgets

HEADERS += $$files($$PWD/*.h, false)
SOURCES += $$files($$PWD/*.cpp, false)
