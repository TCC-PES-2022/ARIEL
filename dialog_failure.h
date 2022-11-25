#ifndef DIALOG_FAILURE_H
#define DIALOG_FAILURE_H

#include <QDialog>

namespace Ui {
class Dialog_failure;
}

class Dialog_failure : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_failure(QWidget *parent = nullptr);
    ~Dialog_failure();

private slots:
    void on_btn_ok_clicked();

private:
    Ui::Dialog_failure *ui;
};

#endif // DIALOG_FAILURE_H
