#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QApplication::setOrganizationName("FGx");
    QApplication::setOrganizationDomain("fgx.ch");
    QApplication::setApplicationName("FGx FlightGear Installer");
    QApplication::setApplicationVersion("0.1-dev");

    MainWindow w;
    w.show();

    return app.exec();
}
