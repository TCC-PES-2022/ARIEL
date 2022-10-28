#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "dialog_selectimage_file.h"
#include <QDebug>
#include "imagefileoperationmanager.h"


QVector<int> selectedFile;
QStringList  fileImageNameList;
ImageFileOperationManager *imageManager=new ImageFileOperationManager();

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


void MainWindow::on_btn_addImage_clicked()
{
    Dialog_selectImage_file dialogBox;
    QObject::connect(&dialogBox,&Dialog_selectImage_file::selectedFiles,this,&MainWindow::filesSelected);
    dialogBox.exec();
}


void MainWindow::setUpInterface()
{
    QStringList filesImagem;
    ui->tw_fileImage->setColumnCount(2);
    QStringList labels;
    labels<<"Selecionar"<<"Partnumber";
    ui->tw_fileImage->setHeaderLabels(labels);


    showImageFileList();



    ui->tw_transferFile->setColumnCount(3);
    QStringList labelsTransfer;
    labelsTransfer<<"Partnumber"<<"Target"<<"Progresso";
    ui->tw_transferFile->setHeaderLabels(labelsTransfer);
}

void MainWindow::createItemFile(QString partNumber)
{


    QTreeWidgetItem *treeItem=new QTreeWidgetItem(ui->tw_fileImage);
    treeItem->setText(1,partNumber);
     cBox=new QCheckBox();
     QObject::connect(cBox,&QCheckBox::stateChanged,this,&MainWindow::cBox_stateChanged);
     ui->tw_fileImage->setItemWidget(treeItem,0,cBox);

}

void MainWindow::createItemTransferFile(QString partNumber, QString TargetHardware)
{

    QTreeWidgetItem *treeItem=new QTreeWidgetItem(ui->tw_transferFile);
    statusTransfer=new QProgressBar();
    statusTransfer->setRange(0,100);
    statusTransfer->setValue(0);
    statusTransfer->setTextVisible(true);

    treeItem->setText(0,partNumber);
    treeItem->setText(1,TargetHardware);
    ui->tw_transferFile->setItemWidget(treeItem,2,statusTransfer);


}

void MainWindow::updateProgressBarrTransferFile(int index, double valor)
{
    QTreeWidgetItem *treeItem=ui->tw_transferFile->topLevelItem(index);
    statusTransfer=new QProgressBar();
    statusTransfer->setRange(0,100);
    statusTransfer->setValue(valor);
    statusTransfer->setTextVisible(true);
    ui->tw_transferFile->setItemWidget(treeItem,2,statusTransfer);
}




void MainWindow::cBox_stateChanged(int state)
{

    int currentItem=ui->tw_fileImage->indexOfTopLevelItem(ui->tw_fileImage->currentItem());
    if(state==2){
        selectedFile.replace(currentItem,currentItem);
    }else{

        selectedFile.replace(currentItem,-1);

    }

    //qDebug()<< "itens selecionados são "<<selectedFile;
}


void MainWindow::on_btn_transferImage_clicked()
{
    foreach (int i, selectedFile) {

        if(i>=0){


            QTreeWidgetItem *treeItem=ui->tw_fileImage->topLevelItem(i);
            cBox=new QCheckBox();
            QObject::connect(cBox,&QCheckBox::stateChanged,this,&MainWindow::cBox_stateChanged);
            ui->tw_fileImage->setItemWidget(treeItem,0,cBox);
            selectedFile.replace(i,-1);
            QString nameFile=treeItem->text(1);
            QString target="FCL";
            createItemTransferFile(nameFile,target);
        }
    }

    ui->tw_fileImage->currentItem()->setSelected(false);
    ui->tw_fileImage->setEnabled(false);
}

void MainWindow::showImageFileList()
{
   fileImageNameList = imageManager->getImageFileList();

   foreach (QString fileName, fileImageNameList) {
       createItemFile(fileName);
   }


   for (int var = 0; var < ui->tw_fileImage->topLevelItemCount(); ++var) {
       selectedFile.push_back(-1);
   }


}

void MainWindow::filesSelected(QString imagePath, QString compatibilityFilePath)
{
    imageManager->setImagePath(imagePath,compatibilityFilePath);

}

void MainWindow::updateInterfaceImage(char **images, int tam)
{
    printf("cheguei");
}

