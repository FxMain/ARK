#ifndef CD_H
#define CD_H

#include <QDialog>

#include "newdoc.h"
#include "archivesdoc.h"
#include "outbound.h"
#include "inventory.h"

#include "fileexport.h"
#include "statistical.h"
#include "usermanagement.h"
#include "organizationmangement.h"

namespace Ui {
class cd;
}

class cd : public QDialog
{
    Q_OBJECT

public:
    explicit cd(QWidget *parent = 0);

    ~cd();

private slots:


    void on_pushButton_newdoc_clicked();

    void on_pushButton_archiveManagement_clicked();

    void on_pushButton_outbound_clicked();

    void on_pushButton_inventory_clicked();

    void on_pushButton_export_clicked();

    void on_pushButton_Statistical_clicked();

    void on_pushButton_userManagement_clicked();

    void on_pushButton_OrganizationMangement_clicked();

private:
    Ui::cd *ui;


    void resizeEvent(QResizeEvent * event);
};

#endif // CD_H
