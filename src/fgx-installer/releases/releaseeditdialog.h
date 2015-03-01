#ifndef RELEASEEDITDIALOG_H
#define RELEASEEDITDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>

class ReleaseEditDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ReleaseEditDialog(QWidget *parent = 0);

    QLineEdit *txtName;
    QLineEdit *txtDescription;
    QComboBox *comboType;
    QCheckBox *checkBoxMandatory;


signals:

public slots:

};

#endif // RELEASEEDITDIALOG_H
