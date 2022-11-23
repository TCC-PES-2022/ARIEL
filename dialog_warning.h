#ifndef DIALOG_WARNING_H
#define DIALOG_WARNING_H

#include <QDialog>

namespace Ui {
class Dialog_warning;
}

class Dialog_warning : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_warning(QWidget *parent = nullptr);
    ~Dialog_warning();
    void showUp(QString title,QString mensage);

private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialog_warning *ui;
    QString title;
    QString msg;
};

#endif // DIALOG_WARNING_H
