#ifndef SERVERCALL_H
#define SERVERCALL_H

#include <QObject>
#include <QString>
#include <QHash>

#include <QScriptValue>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include "xwidgets/xstatusbar.h"
class XStatusBar;

//#include "xobjects/mainobject.h"
//class MainObject;

class ServerCall : public QObject
{
Q_OBJECT
public:
    explicit ServerCall(QObject *parent = 0);


    XStatusBar *statusBar;

    QNetworkAccessManager *netMan;
    QNetworkReply *reply;
    QString serverString;

    void get_record(QString url, int id);

    void get(QString url, QHash<QString, QString> vars);
    void get(QString url);
    void post(QString url, QHash<QString, QString> payload);

    void attach_statusbar(XStatusBar *statusbar);
   // void set_feedback_widget(XStatusBar *statusBar);


signals:
    void data(QScriptValue json);
    void server_status(QString status);
public slots:
    void on_server_ready_read();
    void on_server_read_finished();
    void on_server_error(QNetworkReply::NetworkError);
};

#endif // SERVERCALL_H

/*

    connect(self.reply, QtCore.SIGNAL( 'error(QNetworkReply::NetworkError)'), self.on_network_error)
    self.connect(self.reply, QtCore.SIGNAL( 'readyRead()'), self.on_server_ready_read)
    self.connect(self.reply, QtCore.SIGNAL( 'finished()'), self.on_server_read_finished)

    */
