

#include <QtDebug>

#include <QTimer>
#include <QList>

#include <QIcon>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QToolBar>
#include <QHeaderView>
#include <QPushButton>

#include "xobjects/xsettings.h"
#include "aircraft/aircrafttreewidget.h"

AircraftTreeWidget::AircraftTreeWidget(QWidget *parent) :
    QWidget(parent)
{



    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(0,0,0,0);
    setLayout(mainLayout);


    /*
    QToolBar *toolbar = new QToolBar();
    mainLayout->addWidget(toolbar);

    toolbar->addAction( QIcon(":/icon/rel_add"), "Add", this,  SLOT(on_add()) );
    actEdit = toolbar->addAction( QIcon(":/icon/rel_edit"), "Edit", this,  SLOT(on_edit()) );
    //actEdit->setDisabled(true);
    toolbar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    */
    QString tree_style("QTreeView::item:hover {background-color: #dddddd;}");
    tree = new QTreeWidget();
    mainLayout->addWidget(tree);

    tree->setUniformRowHeights(true);
    tree->setAlternatingRowColors(true);
    tree->setRootIsDecorated(false);
    tree->setStyleSheet(tree_style);

    tree->headerItem()->setText(C_AERO, "Aero");
    tree->headerItem()->setText(C_DESCRIPTION, "Description");
    tree->headerItem()->setText(C_STATUS, "Status");
    tree->headerItem()->setText(C_ZIP_SIZE, "Size");
    tree->headerItem()->setText(C_ZIP_MD5, "Hash");
    tree->headerItem()->setText(C_ZIP_FILE, "Zip File");
    tree->headerItem()->setText(C_ID, "ID");
    tree->headerItem()->setText(C_AUTHOR, "Author");
    tree->headerItem()->setText(C_SUB_DIR, "Dir");
    tree->headerItem()->setText(C_XML_SET, "XML File");
    tree->headerItem()->setText(C_LAST_UPDATED, "Updated");
    tree->headerItem()->setText(C_ACTION, "Action");
    tree->headerItem()->setText(C_ACTION_LBL, "Package Status");
    tree->header()->setStretchLastSection(true);

    tree->setColumnWidth(C_SUB_DIR, 80);
    tree->setColumnWidth(C_AERO, 120);
    tree->setColumnWidth(C_DESCRIPTION, 200);
    tree->setColumnWidth(C_ZIP_SIZE, 60);
    tree->setColumnWidth(C_ZIP_MD5, 160);
    tree->setColumnWidth(C_STATUS, 80);
    tree->setColumnWidth(C_ID, 50);

    tree->setColumnHidden(C_ID, true);
    tree->setColumnHidden(C_ZIP_MD5, true);
    tree->setColumnHidden(C_ZIP_FILE, false);
    tree->setColumnHidden(C_SUB_DIR, true);
    tree->setColumnHidden(C_XML_SET, true);

    //====================================================
    //== Downloaded panel

    /*
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
    progressBar->setVisible(false);
    progressBar->setFixedHeight(16);
    progLay->addWidget(progressBar, 1);
    */


    //==========================================
    //== Status Bar
    statusBar = new XStatusBar(this);
    mainLayout->addWidget(statusBar);
    connect(statusBar, SIGNAL(refresh_server()), this, SLOT(fetch_server()));


    downManWidget = new DownloadManagerWidget();
    mainLayout->addWidget(downManWidget);
    connect(downManWidget, SIGNAL(status_update(QString,QString)),
                            this, SLOT(on_status_update(QString, QString)));

    //========================================
    //= Server Call
    server = new ServerCall(this);
    server->attach_statusbar(statusBar);
    connect(server, SIGNAL(data(QScriptValue)),
            this, SLOT(on_server_data(QScriptValue)));



    //=================================
    //== Buttons groups
    buttGroupInstall = new QButtonGroup(this);
    connect(    buttGroupInstall, SIGNAL(buttonClicked(QAbstractButton*)),
                this, SLOT(on_install_button_clicked(QAbstractButton*))
    );

    buttGroupInfo = new QButtonGroup(this);
    connect(    buttGroupInfo, SIGNAL(buttonClicked(QAbstractButton*)),
                this, SLOT(on_info_button_clicked(QAbstractButton*))
    );

    QTimer::singleShot(500, this, SLOT(fetch_server()));
}


//=================================================================
//== Fetch Server
void AircraftTreeWidget::fetch_server()
{
    server->get("http://download.fgx.ch/aircraft/index.json");
}

//=================================================================
//== Load Server Data
void AircraftTreeWidget::on_server_data(QScriptValue data)
{
    //qDebug() << data.toString();
    if ( data.property("aircraft").isArray() )
    {
        QScriptValueIterator it(data.property("aircraft"));
        while (it.hasNext()) {
            it.next();
            if (it.flags() & QScriptValue::SkipInEnumeration){
                continue;
            }

            QTreeWidgetItem *item = new QTreeWidgetItem();
            /*
            item->setIcon(C_AERO, QIcon(":/icon/rel"));
            QFont f = item->font(C_AERO);
            f.setBold(true);
            item->setFont(C_AERO, f);
            item->setText(C_AERO, it.value().property("aero").toString());
            */
            item->setText(C_ID, it.value().property("id").toString() );
            item->setText(C_SUB_DIR, it.value().property("sub_dir").toString() );
            item->setText(C_XML_SET, it.value().property("xml_set").toString() );
            item->setText(C_LAST_UPDATED, it.value().property("last_updated").toString());
            item->setText(C_STATUS, it.value().property("status").toString());
            item->setText(C_AUTHOR, it.value().property("author").toString());
            item->setText(C_DESCRIPTION, it.value().property("description").toString());
            item->setText(C_ZIP_FILE, it.value().property("zip_file").toString());
            item->setText(C_ZIP_MD5 , it.value().property("zip_md5").toString());
            item->setText(C_ZIP_SIZE, it.value().property("zip_size").toString() );
            item->setText(C_STATUS, it.value().property("status").toString());

            item->setText(C_ACTION_LBL, "Available for download");
            //item->setText(C_STATUS, it.value().property("status").toString());

            //= only after adding item to tree can we add the buttons..
            tree->addTopLevelItem(item);

            QToolButton *buttInfo = new QToolButton();
            buttInfo->setText(it.value().property("aero").toString());
            buttInfo->setProperty("id", it.value().property("id").toString());
            buttInfo->setProperty("zip_file", it.value().property("zip_file").toString());
            buttInfo->setIcon(QIcon(":/icon/rel"));
            buttInfo->setAutoRaise(true);
            buttInfo->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
            //buttInfo->setProperty("state", "none");
            buttInfo->setStyleSheet("font-weight: bold; text-align: left;");
            tree->setItemWidget(item, C_AERO, buttInfo);
            buttGroupInfo->addButton(buttInfo);

            QPushButton *buttInstall = new QPushButton();
            buttInstall->setText("Download");
            buttInstall->setProperty("id", it.value().property("id").toString());
            buttInstall->setProperty("zip_file", it.value().property("zip_file").toString());
            buttInstall->setProperty("state", "available");
            tree->setItemWidget(item, C_ACTION, buttInstall);
            buttGroupInstall->addButton(buttInstall);
        }
    }
}


//======================================================
// Info Button
void AircraftTreeWidget::on_info_button_clicked(QAbstractButton *butt)
{
    emit open_aero(butt->property("id").toInt());
    qDebug() << "emit" << butt->property("id").toInt();

}


//======================================================
// Install Button
void AircraftTreeWidget::on_install_button_clicked(QAbstractButton *butt)
{

    //#if ( downloadQueue.contains(""))
   // qDebug() << "qidx=" << downloadQueue.indexOf(butt->property("id").toString());
    QString state = butt->property("state").toString();

    //qDebug() << "on_install id/state = " << butt->property("id") << state;
    //d//ownManWidget->add_download(butt->property("zip_file").toString(),
     //                           XSettings::getInstance().server_url("/download/aircraft/zip/"),
    //                            XSettings::temp(QString("/aero/")));

   // return;

    QString zip_file = butt->property("zip_file").toString();

    if(  state == "available" ){

        /*
        QList<QAbstractButton *> butts = buttGroupInstall->buttons();
        for(int i = 0; i < butts.count(); i++){
           QAbstractButton *b = butts.at(i);
           if( zip_file == b->property("zip_file").toString()){
               b->setText("Remove");
               b->setProperty("state", "queued");
               b->setStyleSheet("color: #000099; font-weight: bold;");
           }
        }
        QList<QTreeWidgetItem *> items = tree->findItems(zip_file, Qt::MatchExactly, C_ZIP_FILE);
        for(int i = 0; i < items.count(); i++){
            QTreeWidgetItem *item = items.at(i);
            item->setText(C_ACTION_LBL, "Queued for download");
        }
        */
        downManWidget->add_download(zip_file,
                                   XSettings::getInstance().server_url("/download/aircraft/zip/"),
                                    XSettings::temp(QString("/aero/")));



    }else if(state == "queued"){
        //downloadQueue.remove_file(zip_file);
        downManWidget->remove_download(zip_file,
                                   XSettings::getInstance().server_url("/download/aircraft/zip/"),
                                    XSettings::temp(QString("/aero/")));

    }
    //progressBar->setVisible(true);
}


void AircraftTreeWidget::on_status_update(QString zip_file, QString status)
{
    QString butt_label = "na";
    QString status_label = "na";
    QString style = "";
    bool disabled = false;

    if(status == "available"){
        butt_label = "Download";
        status_label = "Available for download";

    }else if(status == "queued"){
        butt_label = "Queued";
        status_label = "Queued for download";
        style = "font-weight: bold; color: #009900;";
        disabled = true;

    }



    QList<QTreeWidgetItem *> items = tree->findItems(zip_file, Qt::MatchExactly, C_ZIP_FILE);
    for(int i = 0; i < items.count(); i++){
        QTreeWidgetItem *item = items.at(i);
        item->setText(C_ACTION_LBL, status_label);
    }

    QList<QAbstractButton *> butts = buttGroupInstall->buttons();
    for(int i = 0; i < butts.count(); i++){
       QAbstractButton *b = butts.at(i);
       if( zip_file == b->property("zip_file").toString()){
           b->setText(butt_label);
           b->setProperty("state", status);
           b->setStyleSheet(style);
           b->setDisabled(disabled);
       }
    }
}

