#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "dialog_selectimage_file.h"
#include <QDebug>
#include "imagefileoperationmanager.h"
#include "UI_API.h"
#include <QMessageBox>

QVector<int> selectedFile;
QStringList  fileImageNameList;
ImageFileOperationManager *imageManager=new ImageFileOperationManager();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setUpInterface();

    //QObject::connect(&coreGUI_thread,&QThread::started,&coreGui,&CoreGUI::start);

    QObject::connect(ui->btn_cancelTransfer,SIGNAL(clicked()),this,SLOT(btn_cancelTransfer_cliked()));
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
    ui->progressBar->setRange(0,100);
    ui->progressBar->setValue(0);

    //Hide "Excluir" and "Status Geral" buttons
    ui->btn_deleteImage->hide();
    ui->pushButton_5->hide();

    ui->btn_transferImage->setEnabled(false);
    ui->btn_cancelTransfer->setEnabled(false);

    //TODO: Add layout to a widget to show/hide both widgets at the same time
    ui->label_3->hide();
    ui->progressBar->hide();
    
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
     QObject::connect(cBox,&QCheckBox::stateChanged,this,&MainWindow::on_cBox_stateChanged);
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

    // ui->progressBar->setValue(0);
    QTreeWidgetItem *treeItem=ui->tw_transferFile->topLevelItem(index);
    statusTransfer=new QProgressBar();
    statusTransfer->setRange(0,100);
    statusTransfer->setValue(valor);
    statusTransfer->setTextVisible(true);
    ui->tw_transferFile->setItemWidget(treeItem,2,statusTransfer);
}

void MainWindow::showLoadTransferProgress(QString filesTransferInfo)
{
    double progress=imageManager->getLoadListRatio(filesTransferInfo);

   /*if(progress==100){
      
      ui->tw_fileImage->setEnabled(true);
   }*/

    // ui->progressBar->setRange(0,100);
    ui->progressBar->setValue(progress);

    qDebug()<<"Progresso geral= "<<progress;
}

int MainWindow::countSelectedImage(QVector<int> listSelectedImage)
{
    int sizeElementSelected=0;
    foreach (int i, listSelectedImage) {
        if(i!=-1){
            sizeElementSelected++;
        }
    }

    return sizeElementSelected;
}

void MainWindow::unSelectedQBoxItem(int indeOfElement)
{
   QTreeWidgetItem *treeItem=ui->tw_fileImage->topLevelItem(indeOfElement);
   cBox=new QCheckBox();
   QObject::connect(cBox,&QCheckBox::stateChanged,this,&MainWindow::on_cBox_stateChanged);
   ui->tw_fileImage->setItemWidget(treeItem,0,cBox);
}

void MainWindow::updateProgressTransfer(QString filesTransferInfo)
{

    int count=0;
    foreach (QString partnumber, fileImageNameList) {

        double loadRatio=imageManager->getLoadFileRatio(partnumber,filesTransferInfo);
        qDebug() << "\n loadRatio: " << loadRatio << "PartNumber: "<< partnumber;
        updateProgressBarrTransferFile(count,loadRatio);
        count++;
    }

    showLoadTransferProgress(filesTransferInfo);
}

void MainWindow::on_cBox_stateChanged(int state)
{

    int elementSize=countSelectedImage(selectedFile);
    qDebug()<<"Number of selectedFile["<<elementSize;

    int currentItem=ui->tw_fileImage->indexOfTopLevelItem(ui->tw_fileImage->currentItem());
        if(state == 2){
            if(elementSize<9){
            selectedFile.replace(currentItem,currentItem);
            }else{
                unSelectedQBoxItem(currentItem);
                QMessageBox msgBox;
                msgBox.setText("Somente 9 arquivo pode ser selecionado de uma vez");
                msgBox.exec();
            }
        }else{
            selectedFile.replace(currentItem,-1);
        }

        bool enableButton=false;
        for (int i = 0; i < selectedFile.size(); ++i) {
            //qDebug()<<"selectedFile["<<i<<"]="<<selectedFile[i];
            if(selectedFile.at(i)!=-1){
                enableButton=true;
                break;
            }
        }
        ui->btn_transferImage->setEnabled(enableButton);

}


void MainWindow::on_btn_transferImage_clicked()
{
    QStringList listPN;

    ui->tw_transferFile->clear();
//    sendImageUpload( );

    fileImageNameList.clear();
    foreach (int i, selectedFile) {

        if(i>=0){
            QTreeWidgetItem *treeItem=ui->tw_fileImage->topLevelItem(i);
            cBox=new QCheckBox();
            QObject::connect(cBox,&QCheckBox::stateChanged,this,&MainWindow::on_cBox_stateChanged);
            ui->tw_fileImage->setItemWidget(treeItem,0,cBox);
            if(selectedFile.at(i) != -1){
//                fileImageNameList.append()
            }
            selectedFile.replace(i,-1);
            QString nameFile=treeItem->text(1);
            QString target="FCL";
            createItemTransferFile(nameFile,target);
            listPN.append(nameFile);
            fileImageNameList.append(nameFile);
            //TODO - Colocar a UI_API aqui pra iniciarTransferencia
        }

    }
    imageManager->sendImageUpload(listPN);
    ui->tw_fileImage->currentItem()->setSelected(false);
    ui->tw_fileImage->setEnabled(false);
    ui->progressBar->setValue(0);
    ui->btn_transferImage->setEnabled(false);
    ui->btn_cancelTransfer->setEnabled(true);
    ui->btn_addImage->setEnabled(false);
    ui->label_3->show();
    ui->progressBar->show();
}


void MainWindow::btn_cancelTransfer_cliked()
{
   imageManager->cancelTransferFile();
   ui->tw_fileImage->setEnabled(true);
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

void MainWindow::updateProgressTransferList(char *json)
{


      QString imageStatusList(json);
      updateProgressTransfer(imageStatusList);


    
}


void MainWindow::alertFailTransfer(unsigned char status)
{
    QMessageBox msgBox;
    if (status == 0)
    {
        msgBox.setText("Falha na transferência");
    }
    else
    {
        msgBox.setText("Transferência realizada com sucesso");
    }
    msgBox.exec();
    ui->tw_fileImage->setEnabled(true);
    ui->btn_cancelTransfer->setEnabled(false);
    ui->tw_transferFile->clear();
    ui->label_3->hide();
    ui->progressBar->hide();

    ui->btn_addImage->setEnabled(true);

}



void MainWindow::updateInterfaceImage(char **images, int tam)
{
    ui->tw_fileImage->clear();
    selectedFile.clear();
//    fileImageNameList.clear();
    for (int i = 0; i< tam;i++)
        {
            QString partNumber = QString::fromUtf8((char*)images[i]);
            createItemFile(partNumber);
//            fileImageNameList.append(partNumber);
            selectedFile.push_back(-1);
        }
}

