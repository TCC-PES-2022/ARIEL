#include "dialog_searchfile.h"
#include "ui_dialog_searchfile.h"
#include <QDir>


QString fIleIcon=":/img/icon/img/FileISO_ICON.png";
QString dirIcon=":/img/icon/img/Dir_blue_Icon.png";
QString fileExtension=".bin";


Dialog_searchFIle::Dialog_searchFIle(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_searchFIle)
{
    ui->setupUi(this);
    setUpInterface();
}

Dialog_searchFIle::~Dialog_searchFIle()
{
    delete ui;
}

void Dialog_searchFIle::setUpInterface()
{
     listDrivers();
     ui->treeWidget->setColumnCount(2);
     QStringList labels;
     labels<<"Nome"<<"Local";
     ui->treeWidget->setHeaderLabels(labels);

     ui->btn_selectionImg->setEnabled(false);

}

void Dialog_searchFIle::listDrivers()
{
    QDir driversUnity;
    foreach (QFileInfo qfi, driversUnity.drives()) {
        ui->comboBox->addItem(qfi.absoluteFilePath());
    }
}

void Dialog_searchFIle::addTreeRoot(QString name, QString pathFile, bool isFIle)
{
     QTreeWidgetItem *treeItem=new QTreeWidgetItem(ui->treeWidget);
     treeItem->setText(0,name);
     treeItem->setText(1,pathFile);

     if(isFIle){
         treeItem->setIcon(0,QIcon(fIleIcon));

     }else{
         treeItem->setIcon(0,QIcon(dirIcon));
         addTreeChild(treeItem,pathFile);
     }
}

void Dialog_searchFIle::addTreeChild(QTreeWidgetItem *parent, QString pathFIleFather)
{
     QDir unity(pathFIleFather);
     foreach (QFileInfo qfi, unity.entryInfoList()) {
         QTreeWidgetItem *treeItem=new QTreeWidgetItem();
         treeItem->setText(0,qfi.fileName());
         treeItem->setText(1,qfi.filePath());

         if(qfi.isDir()){
             treeItem->setIcon(0,QIcon(dirIcon));
             parent->addChild(treeItem);

         }else if(qfi.isFile() && qfi.fileName().endsWith(fileExtension)){
             treeItem->setIcon(0,QIcon(fIleIcon));
             parent->addChild(treeItem);
         }

     }
}

void Dialog_searchFIle::listFileDrives(QDir unity)
{
    foreach (QFileInfo qfi, unity.entryInfoList()) {

        addTreeRoot(qfi.fileName(),qfi.filePath(),qfi.isFile());

    }
}

void Dialog_searchFIle::on_comboBox_currentTextChanged(const QString &arg1)
{
    ui->treeWidget->clear();
    QDir content(arg1);
    listFileDrives(content);
}


void Dialog_searchFIle::on_treeWidget_itemExpanded(QTreeWidgetItem *item)
{
    int numberChildren=item->childCount();
    QList<QTreeWidgetItem*> children;
    for(int i=0;i<numberChildren;i++){
        children.append(item->child(i));
    }

    foreach (QTreeWidgetItem *father, children) {
        father->takeChildren();
        addTreeChild(father,father->text(1));
    }
}


void Dialog_searchFIle::on_treeWidget_itemSelectionChanged()
{
    QTreeWidgetItem *item=ui->treeWidget->currentItem();
    if(item->text(1).endsWith(fileExtension)){
        ui->btn_selectionImg->setEnabled(true);
    }else{
        ui->btn_selectionImg->setEnabled(false);
    }
}


void Dialog_searchFIle::on_btn_cancel_clicked()
{
    this->close();
}


void Dialog_searchFIle::on_btn_selectionImg_clicked()
{
    QTreeWidgetItem *item=ui->treeWidget->currentItem();

    QString filepath=item->text(1);

    //emit sinal para a tela principal
}

