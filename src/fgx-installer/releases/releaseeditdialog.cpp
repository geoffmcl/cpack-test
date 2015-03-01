
#include "releaseeditdialog.h"

#include <QVBoxLayout>
#include <QGroupBox>
#include <QGridLayout>
#include <QLabel>


ReleaseEditDialog::ReleaseEditDialog(QWidget *parent) :
    QDialog(parent)
{

    setMinimumWidth(400);
    setWindowTitle("Item");

    int m = 20;
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(m,m,m,m);
    setLayout(mainLayout);

    QGroupBox *groupReleaseItem = new QGroupBox("Item Details");
    mainLayout->addWidget(groupReleaseItem);
    QGridLayout *gridRelease = new QGridLayout();
    groupReleaseItem->setLayout(gridRelease);

    int row = 0;
    gridRelease->addWidget(new QLabel("Name"), row, 0, 1, 1, Qt::AlignRight);
    txtName = new QLineEdit();
    gridRelease->addWidget(txtName, row, 1, 1, 1);

    row++;
    gridRelease->addWidget(new QLabel("Description"), row, 0, 1, 1, Qt::AlignRight);
    txtDescription = new QLineEdit();
    gridRelease->addWidget(txtDescription, row, 1, 1, 2);

    row++;
    //gridRelease->addWidget(new QLabel("Mandatory"), row, 0, 1, 1, Qt::AlignRight);
    checkBoxMandatory = new QCheckBox();
    checkBoxMandatory->setText("This item is mandatory");
    gridRelease->addWidget(checkBoxMandatory, row, 1, 1, 2);

    row++;
    gridRelease->addWidget(new QLabel("Type"), row, 0, 1, 1, Qt::AlignRight);
    comboType = new QComboBox();
    //comboType->setText("This item is mandatory");
    gridRelease->addWidget(comboType, row, 1, 1, 2);
    comboType->addItem("-- select --");
    comboType->addItem("Binary");
    comboType->addItem("Zip");
    comboType->setCurrentIndex(0);
}
