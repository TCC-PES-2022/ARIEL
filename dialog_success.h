#ifndef DIALOG_SUCCESS_H
#define DIALOG_SUCCESS_H

#include <QDialog>

namespace Ui {
class Dialog_success;
}

class Dialog_success : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_success(QWidget *parent = nullptr);
    ~Dialog_success();
    void showUp(QString title,QString mensage);

private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialog_success *ui;
};

#endif // DIALOG_SUCCESS_H
