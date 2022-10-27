#include "imagefileoperationmanager.h"

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
