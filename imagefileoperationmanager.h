#ifndef IMAGEFILEOPERATIONMANAGER_H
#define IMAGEFILEOPERATIONMANAGER_H

#include <QObject>

class ImageFileOperationManager : public QObject
{
    Q_OBJECT
public:
    explicit ImageFileOperationManager(QObject *parent = nullptr);

signals:

public:
    QStringList getImageFileList();
    void setImagePath(QString imgPath,QString cmpPath);
    void sendImageUpload(QStringList  listPN);
};

#endif // IMAGEFILEOPERATIONMANAGER_H
