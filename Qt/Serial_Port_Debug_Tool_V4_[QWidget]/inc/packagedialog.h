#ifndef PACKAGEDIALOG_H
#define PACKAGEDIALOG_H

#include <QDialog>

namespace Ui {
class PackageDialog;
}

class PackageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PackageDialog(QWidget *parent = nullptr);
    ~PackageDialog();
    void setpackOption(bool);

private slots:
    void on_rBtnDefault_clicked();
    void on_rBtnCustomize_clicked();
    void on_btnSelect_clicked();
    void on_btnTargetPath_clicked();
    void on_btnReset_clicked();
    void on_btnOK_clicked();
    void on_btnCancel_clicked();
    void on_PackageDialog_finished(int);

private:
    Ui::PackageDialog *ui;
    QStringList packfiles;
};

#endif // PACKAGEDIALOG_H
