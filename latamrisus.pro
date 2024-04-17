SOURCES += main.cpp \
    MainWindow.cpp \
    plot.cpp

HEADERS += \
    MainWindow.h \
    plot.h

QT += widgets \
    datavisualization
requires(qtConfig(combobox))
