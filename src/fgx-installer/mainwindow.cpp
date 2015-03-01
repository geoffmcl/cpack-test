

#include <QtDebug>

#include <QApplication>
#include <QStyleFactory>
#include <QLabel>
#include <QVBoxLayout>
//#include <QDockWidget>
#include <QPushButton>
#include <QToolButton>
#include <QTabBar>
#include <QVariant>

#include "mainwindow.h"

#include "info/machineinfowidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{

    QApplication::setStyle( QStyleFactory::create("Cleanlooks") );



    move(50,50);
    setMinimumWidth(1000);
    setMinimumHeight(700);

    setWindowIcon(QIcon(":/icon/fgx-installer"));


    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(0,0,0,0);
    setLayout(mainLayout);

    //##QWidget *centralWidget = new QWidget();
    //setCentralWidget(centralWidget);


    //====================================
    QLabel *labelHeader = new QLabel("FGx Installer");
    labelHeader->setStyleSheet("background-color: black; color: white; font-size: 32pt; padding: 5px; font-family: courier");
    mainLayout->addWidget(labelHeader);

    mainWin = new QMainWindow();
    mainLayout->addWidget(mainWin);

    QWidget *centralWidget = new QWidget();
    mainWin->setCentralWidget(centralWidget);

    QVBoxLayout *centralLayout = new QVBoxLayout();
    centralWidget->setLayout(centralLayout);

    //====================================
    tabBar = new QTabBar();
    centralLayout->addWidget(tabBar, 0);

    stackedWidget = new QStackedWidget();
    centralLayout->addWidget(stackedWidget, 200);

    connect(tabBar, SIGNAL(currentChanged(int)), this, SLOT(on_tab_index_changed(int)));

    grpButtCloseTabs = new QButtonGroup();
    connect(grpButtCloseTabs, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(on_close_tab_button(QAbstractButton*)));
    //====================================
    aircraftTreeWidget = new AircraftTreeWidget();
    tabBar->addTab(QIcon(":/icon/refresh"), "Aircraft");
    stackedWidget->addWidget(aircraftTreeWidget);
    connect(aircraftTreeWidget, SIGNAL(open_aero(int)),
            this, SLOT(on_open_aero(int))
    );

    /*
    //====================================
    releasesWidget = new ReleasesWidget();
    tabWidget->addTab(releasesWidget,"Release Admin");


    //====================================
    treeWidget = new QTreeWidget();
    tabWidget->addTab(treeWidget,"Packages");

    treeWidget->headerItem()->setText(C_NAME, "Package Name");
    treeWidget->headerItem()->setText(C_DESCRIPTION, "Description");
    treeWidget->headerItem()->setText(C_FILENAME, "Filename");
    treeWidget->headerItem()->setText(C_DATED, "Dated");
    treeWidget->headerItem()->setText(C_VERSION, "Version");
    */

    //=================================================
    /*
    QDockWidget *dockWidget = new QDockWidget("Machine Info", this);
    dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    MachineInfoWidget *machineInfoWidget = new MachineInfoWidget();
    dockWidget->setWidget(machineInfoWidget);
    mainWin->addDockWidget(Qt::RightDockWidgetArea, dockWidget);

    dockWidget->setFixedWidth(150);
    */
}

MainWindow::~MainWindow()
{

}

void MainWindow::on_open_aero(int id)
{

    QWidget *w = new QWidget();
    int idx = tabBar->addTab(QIcon(":/icon/refresh"), "Foo");
    //tabWidget->set
    QToolButton *p = new QToolButton();
    p->setContentsMargins(0,0,0,0);
    p->setIcon(QIcon(":/icon/close_tab"));
    p->setIconSize(QSize(12,12));
    p->setFixedHeight(16);
    p->setAutoRaise(true);
    p->setProperty("aero_id", QString::number(id));
    tabBar->setTabButton(idx, QTabBar::RightSide, p);

    grpButtCloseTabs->addButton(p);


}

void MainWindow::on_tab_index_changed(int idx)
{
    stackedWidget->setCurrentIndex(idx);
}

void MainWindow::on_close_tab_button(QAbstractButton *butt)
{
    QString id = butt->property("aero_id").toString();
    qDebug() << butt->property("aero_id").toString();

    if(id.length() == 0){
        return;
    }

    qDebug() << id;

    for(int i = 0; i < tabBar->count(); i++){
        qDebug() << i;
        //QWidget *butt = tabBar->tabButton(i, QTabBar::RightSide); //->property("aero_id");
        QToolButton *butt = qobject_cast<QToolButton *>(tabBar->tabButton(i, QTabBar::RightSide));
        qDebug() << "butt=" << butt ;
        QVariant v = butt->property("aero_id");
        //qDebug() << "valid=" << v.isValid();
        //if(== id  ){tabBar->tabButton(i, QTabBar::RightSide)->property("aero_id").toString()
        //    qDebug() << "YES";
        //}
    }
}
