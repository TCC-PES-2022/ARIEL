#ifndef IMAGEFILEOPERATIONMANAGER_H
#define IMAGEFILEOPERATIONMANAGER_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVector>
class ImageFileOperationManager : public QObject
{
    Q_OBJECT
public:
    explicit ImageFileOperationManager(QObject *parent = nullptr);

signals:
private:
    QJsonObject getPartnumberFileInfo(QString partnumber,QString filesTransferInfo);
public:
    QStringList getImageFileList(QVector<int> imageIndex, QStringList filePN);
    void setImagePath(QString imgPath,QString cmpPath);
    void sendImageUpload(QStringList  listPN);
    double getLoadListRatio(QString filesTransferInfo);
    double getLoadFileRatio(QString partnumber,QString filesTransferInfo);
    int getNumberOfHeaderFiles(QString filesTransferInfo);
    int getUploadOpertationStatusCode(QString filesTransferInfo);
    int getLoadFileTransferStatus(QString partnumber,QString filesTransferInfo);

};

#endif // IMAGEFILEOPERATIONMANAGER_H
