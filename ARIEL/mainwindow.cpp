#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "dialog_searchfile.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setUpInterface();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setUpInterface()
{
    ui->tw_imgFile->setColumnCount(3);
    QStringList label_imgFile;
    label_imgFile<<"Partnumber"<<"Tamanho"<<"Integridade";
    ui->tw_imgFile->setHeaderLabels(label_imgFile);

    ui->tw_transferImg->setColumnCount(5);
    QStringList label_transferFile;
    label_transferFile<<"Partnumber"<<"Tamanho"<<"Target"<<"Tempo estimado"<<"Progresso";
    ui->tw_transferImg->setHeaderLabels(label_transferFile);

    ui->btn_cancelTransfer->setEnabled(false);
    ui->btn_transferImg->setEnabled(false);
    ui->btn_remove_Img->setEnabled(false);
    ui->btn_addImg->setEnabled(true);
}


void MainWindow::on_btn_addImg_clicked()
{
    Dialog_searchFIle fileManager;
    fileManager.exec();
}

