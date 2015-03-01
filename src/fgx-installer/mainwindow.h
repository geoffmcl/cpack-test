#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui/QTabBar>
#include <QtGui/QTreeWidget>
#include <QtGui/QStackedWidget>
#include <QtGui/QButtonGroup>

#include "releases/releaseswidget.h"
#include "aircraft/aircrafttreewidget.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:

    enum COLS{
        C_NAME = 0,
        C_DESCRIPTION = 1,
        C_FILENAME = 2,
        C_DATED = 3,
        C_VERSION = 4

    };


    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QMainWindow *mainWin;

     QTabBar *tabBar;
     QStackedWidget *stackedWidget;
     QButtonGroup *grpButtCloseTabs;

     QTreeWidget *treeWidget;


     AircraftTreeWidget *aircraftTreeWidget;
     ReleasesWidget *releasesWidget;

public slots:

     void on_open_aero(int id);

     void on_tab_index_changed(int idx);

     void on_close_tab_button(QAbstractButton *);
};

#endif // MAINWINDOW_H
