#include <QApplication>

#include "./MainWindow.h"
#include "./Fm/Common.h"
#include "./Fm/Web/DouBanWeb.h"
#include "./Fm/ActionDispatch.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow* main_window = new MainWindow();
    Q_ASSERT(main_window);
    main_window->setObjectName("main_window");
    main_window->show();

    ////客户端与web通信
    g_douban_web = new DouBanWeb(qApp);
    Q_ASSERT(g_douban_web);

    g_action_dispatch = new ActionDispatch();
    Q_ASSERT(g_action_dispatch);

    int re = app.exec();

    SAFE_DELETE(g_action_dispatch);
    SAFE_DELETE(g_douban_web);
    return re;
}
