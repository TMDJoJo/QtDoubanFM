QT += network \
      phonon
SOURCES += \
    Main.cpp \
    MainWindow.cpp \
    Scene/PlayScene.cpp \
    Jsoncpp/json_writer.cpp \
    Jsoncpp/json_valueiterator.inl \
    Jsoncpp/json_value.cpp \
    Jsoncpp/json_reader.cpp \
    Jsoncpp/json_internalmap.inl \
    Jsoncpp/json_internalarray.inl \
    Fm/Web/DouBanWeb.cpp \
    Fm/ActionDispatch.cpp \
    Fm/Music/Music.cpp \
    Scene/PlayTimeSlider.cpp \
    Scene/ChannelScene.cpp \
    Scene/Channel.cpp \
    Scene/ChannelScrollArea.cpp

HEADERS += \
    MainWindow.h \
    Scene/PlayScene.h \
    Fm/Common.h \
    Fm/Web/DouBanWeb.h \
    Fm/ActionDispatch.h \
    Fm/Type/DouBanSong.h \
    Fm/Music/Music.h \
    Scene/PlayTimeSlider.h \
    Fm/Type/DouBanChannel.h \
    Scene/ChannelScene.h \
    Scene/Channel.h \
    Scene/ChannelScrollArea.h

FORMS += \
    MainWindow.ui \
    Scene/PlayScene.ui \
    Scene/ChannelScene.ui \
    Scene/Channel.ui

OTHER_FILES += \
    Resource/Qss/MainWindow.css \
    Resource/Qss/PlayScene.css \
    Resource/Qss/ChannelScene.css \
    Resource/Qss/Channel.css

RESOURCES += \
    Resource.qrc

RC_FILE = QtDoubanFm.rc

INCLUDEPATH += \
    Include
