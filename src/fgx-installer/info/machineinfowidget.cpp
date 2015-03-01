

#include "machineinfowidget.h"
#include "xobjects/xsettings.h"

#include <QVBoxLayout>
#include <QHeaderView>


MachineInfoWidget::MachineInfoWidget(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(0,0,0,0);
    setLayout(mainLayout);



    tree = new QTreeWidget();
    mainLayout->addWidget(tree);

    //tree->header()-setVisible(false);
    tree->headerItem()->setText(C_NODE, "-");
    tree->headerItem()->setText(C_VAL1, "-");
    tree->headerItem()->setText(C_VAL2, "-");
    tree->header()->setStretchLastSection(true);

    this->init();
}

void MachineInfoWidget::init()
{
    tree->model()->removeRows(0, tree->model()->rowCount());

    QTreeWidgetItem *machNode = new QTreeWidgetItem();
    machNode->setText(C_NODE, "Workstation Info");
    tree->addTopLevelItem(machNode);
    tree->setItemExpanded(machNode, true);
    machNode->setFirstColumnSpanned(true); // call After adding to tree,, a gotcha

    //= Operating System
    QTreeWidgetItem *osNode = new QTreeWidgetItem(machNode);
    osNode->setText(C_NODE, "OS");
    osNode->setText(C_VAL1, XSettings::osString());

    //tree->he

}
