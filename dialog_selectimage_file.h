#ifndef DIALOG_SELECTIMAGE_FILE_H
#define DIALOG_SELECTIMAGE_FILE_H

#include <QDialog>
// #include "dialog_filemanager.h"

namespace Ui {
class Dialog_selectImage_file;
}

class Dialog_selectImage_file : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_selectImage_file(QWidget *parent = nullptr);
    ~Dialog_selectImage_file();

signals:
    void selectedFiles(QString imagePath,QString compatibilityFilePath);

public slots:
    void updateArquivoSelected(QString pathFile);
    void updateArquivoCompatibilitySelected(QString pathFile);

private slots:
    void on_btn_addImageFile_clicked();

    void on_btn_compatibilityFile_clicked();

    void on_txt_imageFile_textChanged(const QString &arg1);

    void on_txt_compatibilityFile_textChanged(const QString &arg1);

    void on_btn_add_clicked();

private:
    Ui::Dialog_selectImage_file *ui;
    void setUpInterface();
    // Dialog_fileManager *fileManager;
};

#endif // DIALOG_SELECTIMAGE_FILE_H
