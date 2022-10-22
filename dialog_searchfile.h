#ifndef DIALOG_SEARCHFILE_H
#define DIALOG_SEARCHFILE_H

#include <QTreeWidgetItem>
#include <QDialog>
#include <QDir>

namespace Ui {
class Dialog_searchFIle;
}

class Dialog_searchFIle : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_searchFIle(QWidget *parent = nullptr);
    ~Dialog_searchFIle();

private slots:
    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_treeWidget_itemExpanded(QTreeWidgetItem *item);

    void on_treeWidget_itemSelectionChanged();

    void on_btn_cancel_clicked();

    void on_btn_selectionImg_clicked();

private:
    Ui::Dialog_searchFIle *ui;
    void setUpInterface();
    void listDrivers();
    void addTreeRoot(QString name,QString pathFile,bool isFIle);
    void addTreeChild(QTreeWidgetItem *parent,QString pathFIleFather);
    void listFileDrives(QDir unity);
};

#endif // DIALOG_SEARCHFILE_H
