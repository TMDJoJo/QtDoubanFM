QT += network \
      phonon
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
    Jsoncpp/json_internalarray.inl \
    Fm/IAction.cpp \
    Fm/IActor.cpp \
    Fm/ActionFactory.cpp \
    Fm/SongAction.cpp \
    Fm/Web/DouBanWeb.cpp \
    Fm/ActionDispatch.cpp \
    Fm/Music/Music.cpp

HEADERS += \
    MainWindow.h \
    Scene/PlayScene.h \
    Net/Web.h \
    Fm/IAction.h \
    Fm/IActor.h \
    Fm/Common.h \
    Fm/ActionFactory.h \
    Fm/SongAction.h \
    Fm/Web/DouBanWeb.h \
    Fm/ActionDispatch.h \
    Fm/Type/DouBanSong.h \
    Fm/Music/Music.h

FORMS += \
    MainWindow.ui \
    Scene/PlayScene.ui

OTHER_FILES += \
    Resource/Qss/MainWindow.css \
    Resource/Qss/PlayScene.css

RESOURCES += \
    Resource.qrc

