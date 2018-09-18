#ifndef ORGANIZATIONMANGEMENT_H
#define ORGANIZATIONMANGEMENT_H

#include <QDialog>

namespace Ui {
class organizationmangement;
}

class organizationmangement : public QDialog
{
    Q_OBJECT

public:
    explicit organizationmangement(QWidget *parent = 0);
    ~organizationmangement();

private:
    Ui::organizationmangement *ui;
};

#endif // ORGANIZATIONMANGEMENT_H
