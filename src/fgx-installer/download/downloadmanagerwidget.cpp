

#include <QtDebug>


#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QPushButton>

#include "download/downloadmanagerwidget.h"
#include "xobjects/xsettings.h"

const QString DownloadManagerWidget::SEP = QString("~|~");


DownloadManagerWidget::DownloadManagerWidget(QWidget *parent) :
    QWidget(parent)
{
    downloading = false;
    //netMan = new QNetworkAccessManager(this);


    QVBoxLayout *mainLayout = new QVBoxLayout();
    this->setLayout(mainLayout);

    //===========================================
    tree = new QTreeWidget();
    mainLayout->addWidget(tree);

    tree->setAlternatingRowColors(true);
    tree->setRootIsDecorated(false);
    tree->setUniformRowHeights(true);
    tree->header()->setStretchLastSection(true);

    tree->headerItem()->setText(C_FILE, "File to download");
    tree->headerItem()->setText(C_URL, "Url target");
    tree->headerItem()->setText(C_TEMP, "Local Stash dir");
    tree->headerItem()->setText(C_ACTION, "Action");
    tree->headerItem()->setText(C_Q, "Q");

    tree->setColumnWidth(C_FILE, 150);
    tree->setColumnWidth(C_URL, 350);
    tree->setColumnWidth(C_ACTION, 80);
    //tree->setColumnWidth(C_Q, 80);

    buttGrpAction = new QButtonGroup(this);
    connect(buttGrpAction, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(on_action_button(QAbstractButton*)));

    //====================================================
    //== Downloaded panel

    QGroupBox *grpDownloader = new QGroupBox();
    mainLayout->addWidget(grpDownloader);

    QHBoxLayout *grpDownLay = new QHBoxLayout();
    grpDownloader->setLayout(grpDownLay);

    grpDownLay->addWidget(new QLabel("Queued:"), 0);
    lblQueuedCount = new QLabel("None");
    lblQueuedCount->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    grpDownLay->addWidget(lblQueuedCount, 1);


    grpDownLay->addWidget(new QLabel("Status:"), 0);
    lblStatus = new QLabel("Idle");
    lblStatus->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    grpDownLay->addWidget(lblStatus, 1);

    QWidget *progContainer = new QWidget(); // Need a container to fix width of progress.. sighns
    grpDownLay->addWidget(progContainer);
    progContainer->setFixedWidth(200);
    QHBoxLayout *progLay = new QHBoxLayout();
    progLay->setContentsMargins(0,0,0,0);
    progContainer->setLayout(progLay);
    progressBar = new QProgressBar();
    progressBar->setRange(0, 100);
    progressBar->setValue(0);
    progressBar->setVisible(true);
    progressBar->setFixedHeight(16);
    progLay->addWidget(progressBar, 1);


}



//========================================================================================
//== Add Download
void DownloadManagerWidget::add_download(QString file_name, QString url_prefix, QString save_dir)
{
    QString s = make_q_string(file_name,  url_prefix , save_dir );
    if(downloadQueue.contains(s)){
        return;
    }

    QTreeWidgetItem *item = new QTreeWidgetItem();

    item->setText(C_FILE, file_name );
    QFont fnt = item->font(C_FILE);
    fnt.setBold(true);
    item->setFont(C_FILE, fnt);

    item->setText(C_URL, url_prefix);
    item->setText(C_TEMP, save_dir );
    item->setText(C_Q, s );

    tree->addTopLevelItem(item);

    QPushButton *butt = new QPushButton();
    butt->setText("Remove");
    tree->setItemWidget(item, C_ACTION, butt);
    buttGrpAction->addButton(butt);

    downloadQueue.enqueue(s);
    emit status_update(file_name, "queued");

    this->startNextDownload();
}

//========================================================================================
//== Remove Download
void DownloadManagerWidget::remove_download(QString file_name, QString url_prefix, QString save_dir)
{

    QString s = make_q_string(file_name,  url_prefix , save_dir );
    //qDebug() << "remove" <<  s;
    if(downloadQueue.contains(s)){
       // qDebug() << "nuked";
        downloadQueue.removeAll(s);
        QList<QTreeWidgetItem *> fitems = tree->findItems(s, Qt::MatchExactly, C_Q);
        for(int i = 0; i < fitems.count(); i++){
            QTreeWidgetItem *item = fitems.at(i);
            tree->invisibleRootItem()->removeChild(item);
        }
        emit status_update(file_name, "available");

        return;
    }

}
QString DownloadManagerWidget::make_q_string(QString file_name, QString url_prefix, QString save_dir)
{
    return QString(file_name).append( SEP ).append( url_prefix ).append( SEP ).append( save_dir );
}


//======================================================
// Check Queue
void DownloadManagerWidget::startNextDownload()
{


    qDebug() << "check_q=" <<  downloadQueue.count();
    return;
    //lblQueuedCount->setText(downloadQueue.isEmpty() ? "None" : QString::number(downloadQueue.count()));
    //emit q_count(items);

    //= get outta here, no items
    if( downloadQueue.isEmpty() ){
        qDebug() << "no items";
        //emit status_update();
        return;
    }

    //= get outta here if were already downloading something
    if(downloading){
        qDebug() << "is downloading";
        return;
    }


    QString s = downloadQueue.dequeue();
    QStringList list = s.split(SEP);
    QString file_name = list.at(0);
    QString url_path = list.at(1);
    QString temp_path = list.at(2);

    //QString filename = saveFileName(url);
    fileOut.setFileName(temp_path.append(file_name));
    if (!fileOut.open(QIODevice::WriteOnly)) {
        qDebug() << "ERROR cannot open";

        startNextDownload();
        return;                 // skip this download
    }

    QUrl url( XSettings::server_url( url_path, file_name) );
    qDebug() << url.toString();
    QNetworkRequest req(url);

    netReply = netMan.get(req);
    connect(netReply, SIGNAL(downloadProgress(qint64,qint64)),
            this,   SLOT(downloadProgress(qint64,qint64)));
    connect(netReply, SIGNAL(finished()),
            this,   SLOT(downloadFinished()));
    connect(netReply, SIGNAL(readyRead()),
            this,   SLOT(downloadReadyRead()));
}











void DownloadManagerWidget::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    /*
    //progressBar-> .setStatus(bytesReceived, bytesTotal);
    progressBar->setMaximum(bytesTotal);
    progressBar->setValue(bytesReceived);
    // calculate the download speed
    double speed = bytesReceived * 1000.0 / downloadTime.elapsed();
    QString unit;
    if (speed < 1024) {
        unit = "bytes/sec";
    } else if (speed < 1024*1024) {
        speed /= 1024;
        unit = "kB/s";
    } else {
        speed /= 1024*1024;
        unit = "MB/s";
    }
    */
    //progressBar.setMessage(QString::fromLatin1("%1 %2")
     //                      .arg(speed, 3, 'f', 1).arg(unit));
    //progressBar.update();
}

void DownloadManagerWidget::downloadFinished()
 {
    // progressBar->setVisible(false);
     fileOut.close();

     if (netReply->error()) {
         // download failed
         //fprintf(stderr, "Failed: %s\n", qPrintable(netReply->errorString()));
     } else {
         //printf("Succeeded.\n");
         //++downloadedCount;
     }

     netReply->deleteLater();
     startNextDownload();
 }

 void DownloadManagerWidget::downloadReadyRead()
 {
     fileOut.write( netReply->readAll() );
 }


 void DownloadManagerWidget::on_action_button(QAbstractButton *butt)
 {
     qDebug() << "on cancel";
 }
