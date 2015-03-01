#ifndef RELEASESWIDGET_H
#define RELEASESWIDGET_H

#include <QWidget>
#include <QTreeWidget>
#include <QAction>
#include <QScriptValue>
#include <QScriptValueIterator>

#include "xwidgets/xstatusbar.h"
class XStatusBar;

#include "xobjects/servercall.h"

class ReleasesWidget : public QWidget
{
    Q_OBJECT
public:

    enum COLS{
        C_NAME = 0,
        C_ID,
        C_STATUS,
        C_DESCRIPTION,
        C_MANDATORY,
        C_ITEM_TYPE

    };

    explicit ReleasesWidget(QWidget *parent = 0);

    QAction *actEdit;
    QTreeWidget *tree;

    ServerCall *server;
    XStatusBar *statusBar;

signals:


public slots:

    void fetch_server();

    void on_add();
    void on_edit();
    void on_delete();

    void on_server_data(QScriptValue);
};

#endif // RELEASESWIDGET_H
