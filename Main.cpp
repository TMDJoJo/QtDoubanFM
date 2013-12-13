#include <QApplication>

#include "./MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow* main_window = new MainWindow();
    Q_ASSERT(main_window);
    main_window->setObjectName("main_window");
    main_window->show();

    return app.exec();
}
