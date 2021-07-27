TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += \
    src/buffer.h \
    src/console_colors.h \
    src/master_mind.h \
    src/response.h

SOURCES += \
    src/simple_mastermind.cpp

OTHER_FILES += \
    README.md \
    .gitignore \
    CMakeLists.txt
