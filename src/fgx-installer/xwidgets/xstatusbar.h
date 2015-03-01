#ifndef XSTATUSBAR_H
#define XSTATUSBAR_H

#include <QStatusBar>
#include <QToolButton>


class XStatusBar : public QStatusBar
{
Q_OBJECT
public:
    explicit XStatusBar(QWidget *parent = 0);

    QToolButton *buttRefresh;

signals:
    void refresh_server();


public slots:
    void on_refresh_clicked();
    void on_server_status(QString status);
};

#endif // XSTATUSBAR_H
