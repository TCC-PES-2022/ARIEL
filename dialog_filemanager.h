#ifndef DIALOG_FILEMANAGER_H
#define DIALOG_FILEMANAGER_H

#include <QDialog>
#include <QTreeWidget>
#include <QDir>


enum fileExtension{
    ALL=0,
    XML=1,
    BIN=2,
    PDF=3,
 };

namespace Ui {
class Dialog_fileManager;
}

class Dialog_fileManager : public QDialog
{
    Q_OBJECT

public:
    void setTitle(const QString &newTitle);

    void setIcon(const QIcon &newIcon);

    void setFileExtension(const fileExtension filetypeExtension);

    explicit Dialog_fileManager(QWidget *parent = nullptr);
    ~Dialog_fileManager();

private:
    void setUpInterface();
    void listarDrives();
    void addTreeRoot(QString name, QString pathFile,bool isFile);
    void addTreeChild(QTreeWidgetItem *parent, QString pathFileFather);
    void listarDriverFileDir(QDir unidades);

signals:

    void selectedFile(QString filePath);

private slots:
    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_treeWidget_itemExpanded(QTreeWidgetItem *item);

    void on_treeWidget_itemSelectionChanged();

    void on_btn_cancel_clicked();

    void on_btn_selectImage_clicked();

private:
    Ui::Dialog_fileManager *ui;
    QString title;
    QIcon icon;
    QString fileType;
    QString iconeFile;
    QString dirIcon;
};

#endif // DIALOG_FILEMANAGER_H
