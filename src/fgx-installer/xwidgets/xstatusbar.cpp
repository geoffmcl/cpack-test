#include "xwidgets/xstatusbar.h"

XStatusBar::XStatusBar(QWidget *parent) :
    QStatusBar(parent)
{
     setContentsMargins(0,0,0,0);
     setSizeGripEnabled(false);
     buttRefresh = new QToolButton();
     buttRefresh->setIcon(QIcon(":/icon/refresh2"));
     buttRefresh->setAutoRaise(true);
     buttRefresh->setIconSize(QSize(16,16));
     buttRefresh->setStyleSheet("padding: 0; margin: 0;");
     addPermanentWidget(buttRefresh);
     connect(buttRefresh, SIGNAL(clicked()), this, SLOT(on_refresh_clicked()));

     showMessage("Idle");
}

void XStatusBar::on_refresh_clicked()
{
    emit refresh_server();
}


void XStatusBar::on_server_status(QString status)
{

}
