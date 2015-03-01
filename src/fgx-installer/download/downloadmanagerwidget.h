#ifndef DOWNLOADMANAGERWIDGET_H
#define DOWNLOADMANAGERWIDGET_H

#include <QWidget>
#include <QProgressBar>
#include <QLabel>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QGroupBox>
#include <QButtonGroup>
#include <QAbstractButton>

#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkReply>
#include <QTime>
#include <QQueue>
#include <QFile>



class DownloadManagerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DownloadManagerWidget(QWidget *parent = 0);

    enum C_COLS{
        C_FILE,
        C_ACTION,
        C_URL,
        C_TEMP,
        C_Q
    };

    static const QString SEP;

    QNetworkAccessManager netMan;
    QQueue<QString> downloadQueue;
    QNetworkReply *netReply;
    QString saveFileName;
    QTime downloadTime;
    bool downloading;
    QFile fileOut;


    QLabel *lblQueuedCount;
    QLabel *lblStatus;

    QLabel *lblProgress;
    QProgressBar *progressBar;

    QTreeWidget *tree;
    QButtonGroup *buttGrpAction;

    QString make_q_string(QString file_name, QString url_prefix, QString save_dir);

signals:
    //void q_count(int);
    //void finished();
    void status_update(QString zip_file, QString status);

public slots:
    void startNextDownload();
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void downloadFinished();
    void downloadReadyRead();

    //void check_q();
    void add_download(QString file_name, QString url_prefix, QString save_dir);
    void remove_download(QString file_name, QString url_prefix, QString save_dir);
    void on_action_button(QAbstractButton *butt);


};

#endif // DOWNLOADMANAGERWIDGET_H
