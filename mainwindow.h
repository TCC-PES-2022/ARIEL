#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QCheckBox>
#include <QProgressBar>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_addImage_clicked();

    void on_cBox_stateChanged(int state);

    void on_btn_transferImage_clicked();

    void showImageFileList();

    void filesSelected(QString imagePath,QString compatibilityFilePath);



public slots:
    void updateProgressTransferList(char *json);
    //void addNewImageFileResponse(QString filename,bool isAddSuccess);
    void updateInterfaceImage(char **images,int tam);

private:
    void setUpInterface();
    void createItemFile(QString partNumber);
    void createItemTransferFile(QString partNumber, QString TargetHardware);
    void updateProgressBarrTransferFile(int index,double valor);
    void showLoadTransferProgress(QString filesTransferInfo);
public:
    void updateProgressTransfer(QString filesTransferInfo);

private:
    Ui::MainWindow *ui;
    QCheckBox *cBox;
    QProgressBar *statusTransfer;

};
#endif // MAINWINDOW_H
