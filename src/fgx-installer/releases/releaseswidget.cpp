
#include <QtDebug>

#include <QTimer>

#include <QIcon>
#include <QVBoxLayout>
#include <QToolBar>
#include <QHeaderView>

#include "releases/releaseswidget.h"
#include "releases/releaseeditdialog.h"


ReleasesWidget::ReleasesWidget(QWidget *parent) :
    QWidget(parent)
{




    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(0,0,0,0);
    setLayout(mainLayout);



    QToolBar *toolbar = new QToolBar();
    mainLayout->addWidget(toolbar);

    toolbar->addAction( QIcon(":/icon/rel_add"), "Add", this,  SLOT(on_add()) );
    actEdit = toolbar->addAction( QIcon(":/icon/rel_edit"), "Edit", this,  SLOT(on_edit()) );
    //actEdit->setDisabled(true);
    toolbar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);


    tree = new QTreeWidget();
    mainLayout->addWidget(tree);

    tree->setUniformRowHeights(true);
    tree->setAlternatingRowColors(true);
    tree->setRootIsDecorated(false);

    tree->headerItem()->setText(C_NAME, "Name");
    tree->headerItem()->setText(C_DESCRIPTION, "Description");
    tree->headerItem()->setText(C_STATUS, "Status");
    tree->headerItem()->setText(C_ITEM_TYPE, "Type");
    tree->headerItem()->setText(C_MANDATORY, "Required");
    tree->headerItem()->setText(C_ID, "ID");
    tree->header()->setStretchLastSection(true);

    tree->setColumnWidth(C_NAME, 150);
    tree->setColumnWidth(C_DESCRIPTION, 150);
    tree->setColumnWidth(C_ITEM_TYPE, 100);
    tree->setColumnWidth(C_MANDATORY, 60);
    tree->setColumnWidth(C_STATUS, 120);
    tree->setColumnWidth(C_ID, 50);
    tree->setColumnHidden(C_ID, true);

    statusBar = new XStatusBar(this);
    mainLayout->addWidget(statusBar);

    server = new ServerCall(this);
    server->attach_statusbar(statusBar);
    connect(server, SIGNAL(data(QScriptValue)),
            this, SLOT(on_server_data(QScriptValue)));


    QTimer::singleShot(500, this, SLOT(fetch_server()));
}

//=================================================================
//== Fetch Server
void ReleasesWidget::fetch_server()
{
    server->get("http://127.0.0.1:8000/ajax/releases");
}

//=================================================================
//== On Server Data
void ReleasesWidget::on_server_data(QScriptValue data)
{
    //qDebug() << data.toString();
    if ( data.property("releases").isArray() )
    {
        QScriptValueIterator it(data.property("releases"));
        while (it.hasNext()) {
            it.next();
            if (it.flags() & QScriptValue::SkipInEnumeration){
                continue;
            }

            QTreeWidgetItem *item = new QTreeWidgetItem();
            item->setIcon(C_NAME, QIcon(":/icon/rel"));
            QFont f = item->font(C_NAME);
            f.setBold(true);
            item->setFont(C_NAME, f);
            item->setText(C_NAME, it.value().property("name").toString());
            item->setText(C_STATUS, "Not Installed");
            item->setText(C_DESCRIPTION, it.value().property("description").toString());
            item->setText(C_ITEM_TYPE, it.value().property("item_type").toString());
            item->setText(C_MANDATORY, it.value().property("mandatory").toBool() ? "Yes" : "-");
            item->setText(C_ID, it.value().property("id").toString() );

            tree->addTopLevelItem(item);

        }
    }
}


//=================================================================
// CRUD
void ReleasesWidget::on_add()
{
    ReleaseEditDialog *dial = new ReleaseEditDialog(this);
    dial->show();
}
void ReleasesWidget::on_edit()
{
    ReleaseEditDialog *dial = new ReleaseEditDialog(this);
    dial->show();
}

void ReleasesWidget::on_delete()
{
   //server->get("http://127.0.0.1:8000/ajax/releases");
}

