#include "imagefileoperationmanager.h"
#include "coregui.h"
#include "UI_API.h"
char *ptr_dir;
char *ptr_cmp;
QByteArray msg,msg2;
char **mtxlistPN;
ImageFileOperationManager::ImageFileOperationManager(QObject *parent)
    : QObject{parent}
{
    mtxlistPN = (char**)malloc(10*sizeof(char*));
    for (int i = 0;i<10;i++)
    {
        mtxlistPN[i] = (char*)malloc(9*sizeof(char));
    }
}

QJsonObject ImageFileOperationManager::getPartnumberFileInfo(QString partnumber, QString filesTransferInfo)
{
    QString key="headerFiles";
    QJsonDocument qJsonDoc = QJsonDocument::fromJson(filesTransferInfo.toUtf8());
    QJsonObject obj=qJsonDoc.object();
    QJsonValue valueJ=obj.value(key);


    QJsonArray pnList=valueJ.toArray();


    foreach (QJsonValue files, pnList) {
        QJsonObject file=files.toObject();
        QJsonValue pn=file.value("loadPartNumberName");

        if(partnumber==pn.toString()){
            return file;
        }
    }

    QJsonObject file_null;
    return file_null;
}


QStringList ImageFileOperationManager::getImageFileList()
{

    QStringList fileImageList;
    //fileImageList<<"PUY123"<<"EMBRAER234"<<"PES345"<<"UFPE4567";

    imagemGUI =*carregar_imagem_GUI(UI_Informacoes_Imagem,&imagemGUI);
    return fileImageList;

}

void ImageFileOperationManager::setImagePath(QString imgPath, QString cmpPath)
{
    //Formatação Qstring para *char
    msg = imgPath.toLocal8Bit();
    ptr_dir = msg.data();
    imagemGUI.dir_img.diretorio_img = ptr_dir;
    //Formatação Qstring para *char
    msg2 = cmpPath.toLocal8Bit();
    ptr_cmp = msg2.data();
    imagemGUI.dir_img.diretorio_cmp = ptr_cmp;
    imagemGUI = *carregar_imagem_GUI(UI_Carregar_Imagem,&imagemGUI);
}

void ImageFileOperationManager::sendImageUpload(QStringList listPN)
{
    int cont = 0;

    foreach (QString q, listPN) {
        //        memset(&mtxlistPN[cont],0x0,9*sizeof(char));
        QByteArray ba = q.toLocal8Bit();
        strcpy(mtxlistPN[cont],ba.data());
        cont++;
    }
    imagemGUI.img_info.tabela_de_img = mtxlistPN;
    imagemGUI.img_info.tam = cont;
    for (int i = 0; i< imagemGUI.img_info.tam;i++)
    {
        qDebug()<< "/r/n BIN: %s /r/n"<<(char*)imagemGUI.img_info.tabela_de_img[i];
    }

    imagemGUI = *transferir_imagem_GUI(UI_Iniciar_Transferencia,&imagemGUI);
}

double ImageFileOperationManager::getLoadListRatio(QString filesTransferInfo)
{
    QString key="loadListRatio";
    QJsonDocument qJsonDoc = QJsonDocument::fromJson(filesTransferInfo.toUtf8());
    QJsonObject obj=qJsonDoc.object();
    QJsonValue valueJ=obj.value(key);

    double loadListRatio=valueJ.toDouble();
    return loadListRatio;
}

double ImageFileOperationManager::getLoadFileRatio(QString partnumber, QString filesTransferInfo)
{
    QJsonObject file=getPartnumberFileInfo(partnumber,filesTransferInfo);

    if(file.isEmpty()){
        return 0;
    }else{
        QJsonValue loadFileRatio=file.value("loadRatio");
        return loadFileRatio.toDouble();
    }
}

int ImageFileOperationManager::getNumberOfHeaderFiles(QString filesTransferInfo)
{
    QString key="numberOfHeaderFiles";
    QJsonDocument qJsonDoc = QJsonDocument::fromJson(filesTransferInfo.toUtf8());
    QJsonObject obj=qJsonDoc.object();
    QJsonValue valueJ=obj.value(key);

    int loadListRatio=valueJ.toDouble();
    return loadListRatio;
}

int ImageFileOperationManager::getUploadOpertationStatusCode(QString filesTransferInfo)
{
    QString key="uploadOperationStatusCode";
    QJsonDocument qJsonDoc = QJsonDocument::fromJson(filesTransferInfo.toUtf8());
    QJsonObject obj=qJsonDoc.object();
    QJsonValue valueJ=obj.value(key);

    int loadListRatio=valueJ.toDouble();
    return loadListRatio;
}

int ImageFileOperationManager::getLoadFileTransferStatus(QString partnumber, QString filesTransferInfo)
{
    QJsonObject file=getPartnumberFileInfo(partnumber,filesTransferInfo);

    if(file.isEmpty()){
        return 0;
    }else{
        QJsonValue loadFileRatio=file.value("loadStatus");
        return loadFileRatio.toDouble();
    }
}
