#include <QApplication>
#include <QTextCodec>

#include "./MainWindow.h"
#include "./Fm/Common.h"
#include "./Fm/Web/DouBanWeb.h"
#include "./Fm/ActionDispatch.h"
#include "./Fm/Music/Music.h"

#include <QHostInfo>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));

    ////客户端与web通信
    g_douban_web = new DouBanWeb(qApp);
    Q_ASSERT(g_douban_web);

    g_music = new Music();
    Q_ASSERT(g_music);

    g_action_dispatch = new ActionDispatch();
    Q_ASSERT(g_action_dispatch);

    MainWindow* main_window = new MainWindow();
    Q_ASSERT(main_window);
    main_window->setObjectName("main_window");
    main_window->show();

    int re = app.exec();

    SAFE_DELETE(main_window);
    SAFE_DELETE(g_action_dispatch);
    SAFE_DELETE(g_music);
    SAFE_DELETE(g_douban_web);
    return re;
}
