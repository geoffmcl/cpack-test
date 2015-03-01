#ifndef MACHINEINFOWIDGET_H
#define MACHINEINFOWIDGET_H

#include <QWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>

class MachineInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MachineInfoWidget(QWidget *parent = 0);

    enum COLS{
        C_NODE = 0,
        C_VAL1 = 1,
        C_VAL2 = 1
    };
    QTreeWidget *tree;


signals:

public slots:
    void init();
};

#endif // MACHINEINFOWIDGET_H
