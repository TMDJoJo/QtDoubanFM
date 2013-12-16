QT += network
SOURCES += \
    Main.cpp \
    MainWindow.cpp \
    Scene/PlayScene.cpp \
    Net/Web.cpp \
    Jsoncpp/json_writer.cpp \
    Jsoncpp/json_valueiterator.inl \
    Jsoncpp/json_value.cpp \
    Jsoncpp/json_reader.cpp \
    Jsoncpp/json_internalmap.inl \
    Jsoncpp/json_internalarray.inl

HEADERS += \
    MainWindow.h \
    Scene/PlayScene.h \
    Net/Web.h \
    Common.h

FORMS += \
    MainWindow.ui \
    Scene/PlayScene.ui

OTHER_FILES += \
    Resource/Qss/MainWindow.css \
    Resource/Qss/PlayScene.css

RESOURCES += \
    Resource.qrc

