#ifndef AIRCRAFTTREEWIDGET_H
#define AIRCRAFTTREEWIDGET_H

#include <QWidget>
#include <QTreeWidget>
#include <QButtonGroup>
#include <QAbstractButton>
#include <QLabel>
#include <QProgressBar>
#include <QAction>
//#include <QTabBar>
#include <QStackedWidget>



#include <QScriptValue>
#include <QScriptValueIterator>

#include "xwidgets/xstatusbar.h"
class XStatusBar;

#include "xobjects/servercall.h"
#include "download/downloadmanagerwidget.h"

class AircraftTreeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AircraftTreeWidget(QWidget *parent = 0);

    enum COLS{
        C_SUB_DIR = 0,
        C_AERO,
        //C_INFO,
        C_DESCRIPTION,
        C_LAST_UPDATED,
        C_ID,
        C_STATUS,
        C_AUTHOR,
        C_ZIP_FILE,
        C_ZIP_MD5,
        C_ZIP_SIZE,
        C_XML_SET,
        C_ACTION,
        C_ACTION_LBL
    };


    //QAction *actEdit;
    QTreeWidget *tree;
    QTabBar *tabBar;

    DownloadManagerWidget *downManWidget;

    ServerCall *server;
    XStatusBar *statusBar;
    QButtonGroup *buttGroupInstall;
    QButtonGroup *buttGroupInfo;



signals:
    void open_aero(int id);

public slots:

    void fetch_server();
    void on_server_data(QScriptValue);

    void on_install_button_clicked(QAbstractButton*);
    void on_info_button_clicked(QAbstractButton*);

    void on_status_update(QString zip_file, QString status);
    //void on_q_count(int count);
    //void on_add();
    //void on_edit();
    //void on_delete();



};

#endif // AIRCRAFTTREEWIDGET_H
