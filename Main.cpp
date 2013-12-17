#include <QApplication>

#include "./MainWindow.h"
#include "./Net/Web.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow* main_window = new MainWindow();
    Q_ASSERT(main_window);
    main_window->setObjectName("main_window");
    main_window->show();

    ////TODO: connect不能用再单例中，否则崩溃
    Web::Instance().Init();

    return app.exec();
}
