#include "mainwindow.h"
#include <QApplication>
#include<QWebEngineView>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
    QCoreApplication::setApplicationVersion("alpha 0.3.2");
    QApplication a(argc, argv);
    MainWindow w;

    w.setWindowState(Qt::WindowMaximized);
    w.show();
    return a.exec();
}
