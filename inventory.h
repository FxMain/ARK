#ifndef INVENTORY_H
#define INVENTORY_H

#include <QDialog>

namespace Ui {
class inventory;
}

class inventory : public QDialog
{
    Q_OBJECT

public:
    explicit inventory(QWidget *parent = 0);
    ~inventory();

private:

    Ui::inventory *ui;
};

#endif // INVENTORY_H
