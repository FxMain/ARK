#ifndef FILEEXPORT_H
#define FILEEXPORT_H

#include <QDialog>

namespace Ui {
class fileexport;
}

class fileexport : public QDialog
{
    Q_OBJECT

public:
    explicit fileexport(QWidget *parent = 0);
    ~fileexport();

private:
    Ui::fileexport *ui;
};

#endif // FILEEXPORT_H
