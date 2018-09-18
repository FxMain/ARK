#ifndef STATISTICAL_H
#define STATISTICAL_H

#include <QDialog>

namespace Ui {
class statistical;
}

class statistical : public QDialog
{
    Q_OBJECT

public:
    explicit statistical(QWidget *parent = 0);
    ~statistical();

private:
    Ui::statistical *ui;
};

#endif // STATISTICAL_H
