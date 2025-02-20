#include "widget.h"
#include <QApplication>
#include <QScreen>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QScreen *screen = a.primaryScreen();
    if (!screen)
        return -1;

    QRect screenGeometry = screen->geometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();

    Widget w;
    w.resize(screenWidth, screenHeight);
    w.showFullScreen();

    return a.exec();
}
