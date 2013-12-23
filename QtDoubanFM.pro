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
    Fm/Web/DouBanWeb.cpp \
    Fm/ActionDispatch.cpp \
    Fm/Music/Music.cpp \
    Scene/PlayTimeSlider.cpp

HEADERS += \
    MainWindow.h \
    Scene/PlayScene.h \
    Net/Web.h \
    Fm/Common.h \
    Fm/Web/DouBanWeb.h \
    Fm/ActionDispatch.h \
    Fm/Type/DouBanSong.h \
    Fm/Music/Music.h \
    Scene/PlayTimeSlider.h

FORMS += \
    MainWindow.ui \
    Scene/PlayScene.ui

OTHER_FILES += \
    Resource/Qss/MainWindow.css \
    Resource/Qss/PlayScene.css

RESOURCES += \
    Resource.qrc

RC_FILE = QtDoubanFm.rc
