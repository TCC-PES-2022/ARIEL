#include "imagefileoperationmanager.h"
#include "coregui.h"
#include "UI_API.h"
char *ptr_dir;
char *ptr_cmp;
QByteArray msg,msg2;
ImageFileOperationManager::ImageFileOperationManager(QObject *parent)
    : QObject{parent}
{

}

QStringList ImageFileOperationManager::getImageFileList()
{

    QStringList fileImageList;
    fileImageList<<"PUY123"<<"EMBRAER234"<<"PES345"<<"UFPE4567";

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
