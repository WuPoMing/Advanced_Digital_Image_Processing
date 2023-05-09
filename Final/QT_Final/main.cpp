#include "Interface.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Interface window;
    window.resize(700, 900);
    window.show();

    return app.exec();
}