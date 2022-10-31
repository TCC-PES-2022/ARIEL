#include "dialog_selectimage_file.h"
#include "ui_dialog_selectimage_file.h"
#include <QFileDialog>


Dialog_selectImage_file::Dialog_selectImage_file(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_selectImage_file)
{
    ui->setupUi(this);
    setUpInterface();
}

Dialog_selectImage_file::~Dialog_selectImage_file()
{
    delete ui;
}

void Dialog_selectImage_file::updateArquivoSelected(QString pathFile)
{
    ui->txt_imageFile->setText(pathFile);
}

void Dialog_selectImage_file::updateArquivoCompatibilitySelected(QString pathFile)
{
    ui->txt_compatibilityFile->setText(pathFile);
}

void Dialog_selectImage_file::setUpInterface()
{

    ui->txt_compatibilityFile->setEnabled(false);
    ui->txt_imageFile->setEnabled(false);
    ui->btn_add->setEnabled(false);
}

void Dialog_selectImage_file::on_btn_addImageFile_clicked()
{
#if 0
     fileManager=new Dialog_fileManager();

    fileManager->setTitle("Selecionar arquivo de imagem");
    fileManager->setFileExtension(BIN);
    //fileManager->setIcon(QIcon(":/Ariel/img/Ariel/Icon.png"));
    QObject::connect(fileManager,&Dialog_fileManager::selectedFile,this,&Dialog_selectImage_file::updateArquivoSelected);
    fileManager->exec();
#else
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Image File"), "/", tr("Image Files (*.bin)"));
    ui->txt_imageFile->setText(filePath);
#endif

}


void Dialog_selectImage_file::on_btn_compatibilityFile_clicked()
{
#if 0
    fileManager=new Dialog_fileManager();

   fileManager->setTitle("Selecionar arquivo de compatibilidade");
   fileManager->setFileExtension(XML);
   //fileManager->setIcon(QIcon(":/Ariel/img/Ariel/Icon.png"));
   QObject::connect(fileManager,&Dialog_fileManager::selectedFile,this,&Dialog_selectImage_file::updateArquivoCompatibilitySelected);
   fileManager->exec();
#else
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Compatibility File"), "/", tr("Compatibility Files (*.xml)"));
    ui->txt_compatibilityFile->setText(filePath);
#endif

}


void Dialog_selectImage_file::on_txt_imageFile_textChanged(const QString &arg1)
{
    if(arg1==""||ui->txt_compatibilityFile->text()==""){
        ui->btn_add->setEnabled(false);
    }else ui->btn_add->setEnabled(true);
}


void Dialog_selectImage_file::on_txt_compatibilityFile_textChanged(const QString &arg1)
{
    if(arg1==""||ui->txt_imageFile->text()==""){
        ui->btn_add->setEnabled(false);
    }else ui->btn_add->setEnabled(true);
}


void Dialog_selectImage_file::on_btn_add_clicked()
{
    QString imagePath=ui->txt_imageFile->text();
    QString compatibilityPath=ui->txt_compatibilityFile->text();

    emit selectedFiles(imagePath,compatibilityPath);
    this->close();
}

