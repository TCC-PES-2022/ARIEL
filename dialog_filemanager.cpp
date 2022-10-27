#include "dialog_filemanager.h"
#include "ui_dialog_filemanager.h"

void Dialog_fileManager::setTitle(const QString &newTitle)
{
    title = newTitle;
    this->setWindowTitle(this->title);
}

void Dialog_fileManager::setIcon(const QIcon &newIcon)
{
    icon = newIcon;
    this->setIcon(icon);
}

void Dialog_fileManager::setFileExtension(const fileExtension filetypeExtension)
{
    switch (filetypeExtension) {
    case ALL:

        break;
    case XML:
        this->fileType = ".xml";
        iconeFile=":/icon/img/icon/Icon_xml.png";
        break;
    case BIN:
        this->fileType = ".bin";
        iconeFile=":/icon/img/icon/FileISO_ICON.png";
        break;
    default:
        break;
    }
}



Dialog_fileManager::Dialog_fileManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_fileManager)
{
    ui->setupUi(this);
    setUpInterface();
}

Dialog_fileManager::~Dialog_fileManager()
{
    delete ui;
}

void Dialog_fileManager::setUpInterface()
{
    dirIcon=":/icon/img/icon/Dir_blue_Icon.png";
    ui->treeWidget->setColumnCount(2);
    QStringList labels;
    labels<<"Name"<<"Path";
    ui->treeWidget->setHeaderLabels(labels);
    ui->btn_selectImage->setEnabled(false);


    listarDrives();
}

void Dialog_fileManager::listarDrives()
{
    QDir unidades;

    foreach(QFileInfo qfi,unidades.drives()){

        ui->comboBox->addItem(qfi.absoluteFilePath());
    }
}

void Dialog_fileManager::addTreeRoot(QString name, QString pathFile, bool isdir)
{
    if(isdir && !name.endsWith(".")){
        QTreeWidgetItem *treeItem=new QTreeWidgetItem(ui->treeWidget);


        treeItem->setText(0,name);
        treeItem->setText(1,pathFile);
            treeItem->setIcon(0,QIcon(dirIcon));
            addTreeChild(treeItem,pathFile);

        } else if( name.endsWith(fileType)){

        QTreeWidgetItem *treeItem=new QTreeWidgetItem(ui->treeWidget);


        treeItem->setText(0,name);
        treeItem->setText(1,pathFile);
        treeItem->setIcon(0,QIcon(iconeFile));
    }
}

void Dialog_fileManager::addTreeChild(QTreeWidgetItem *parent, QString pathFileFather)
{
    QDir subunidade(pathFileFather);

    foreach(QFileInfo qfi,subunidade.entryInfoList()){

        QTreeWidgetItem *treeItem=new QTreeWidgetItem();
        treeItem->setText(0,qfi.fileName());

        treeItem->setText(1,qfi.filePath());
        //parent->addChild(treeItem);

        if(qfi.isDir()&& !qfi.fileName().endsWith(".")){

            treeItem->setIcon(0,QIcon(dirIcon));
            parent->addChild(treeItem);

        }else if(qfi.isFile() && qfi.fileName().endsWith(fileType)){

            treeItem->setIcon(0,QIcon(iconeFile));
            parent->addChild(treeItem);

        }

    }
}

void Dialog_fileManager::listarDriverFileDir(QDir unidades)
{
    foreach(QFileInfo qfi,unidades.entryInfoList()){


        addTreeRoot(qfi.fileName(),qfi.filePath(),qfi.isDir());

    }
}

void Dialog_fileManager::on_comboBox_currentTextChanged(const QString &arg1)
{
    ui->treeWidget->clear();
    QDir conteudo(arg1);    //local do diretório escolhido no comboBox.
    listarDriverFileDir(conteudo);
}


void Dialog_fileManager::on_treeWidget_itemExpanded(QTreeWidgetItem *item)
{
    int numberChildren=item->childCount();
    QList<QTreeWidgetItem*> children;//= item->takeChildren();

             for (int i=0; i<numberChildren; i++){
                 children.append(item->child(i));
             }

    foreach(QTreeWidgetItem *father,children){

        father->takeChildren();
        addTreeChild(father,father->text(1));
    }
}


void Dialog_fileManager::on_treeWidget_itemSelectionChanged()
{
    QTreeWidgetItem *item=ui->treeWidget->currentItem();

     if(item->text(1).endsWith(fileType)){
         ui->btn_selectImage->setEnabled(true);
     }else{

         ui->btn_selectImage->setEnabled(false);
     }
}


void Dialog_fileManager::on_btn_cancel_clicked()
{
    this->close();
}


void Dialog_fileManager::on_btn_selectImage_clicked()
{
    QTreeWidgetItem *item=ui->treeWidget->currentItem();
    emit selectedFile(item->text(1));
    this->close();
}

