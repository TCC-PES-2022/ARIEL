/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QTreeWidget *tw_imgFile;
    QPushButton *btn_addImg;
    QPushButton *btn_remove_Img;
    QPushButton *btn_transferImg;
    QLabel *label_2;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QTreeWidget *tw_transferImg;
    QPushButton *btn_cancelTransfer;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(866, 657);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 30, 181, 21));
        scrollArea = new QScrollArea(centralwidget);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setGeometry(QRect(0, 60, 651, 291));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 649, 289));
        tw_imgFile = new QTreeWidget(scrollAreaWidgetContents);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        tw_imgFile->setHeaderItem(__qtreewidgetitem);
        tw_imgFile->setObjectName("tw_imgFile");
        tw_imgFile->setGeometry(QRect(0, 0, 651, 291));
        scrollArea->setWidget(scrollAreaWidgetContents);
        btn_addImg = new QPushButton(centralwidget);
        btn_addImg->setObjectName("btn_addImg");
        btn_addImg->setGeometry(QRect(660, 70, 201, 30));
        btn_remove_Img = new QPushButton(centralwidget);
        btn_remove_Img->setObjectName("btn_remove_Img");
        btn_remove_Img->setGeometry(QRect(660, 110, 201, 30));
        btn_transferImg = new QPushButton(centralwidget);
        btn_transferImg->setObjectName("btn_transferImg");
        btn_transferImg->setGeometry(QRect(660, 160, 201, 30));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 380, 221, 21));
        scrollArea_2 = new QScrollArea(centralwidget);
        scrollArea_2->setObjectName("scrollArea_2");
        scrollArea_2->setGeometry(QRect(10, 410, 651, 151));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName("scrollAreaWidgetContents_2");
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 649, 149));
        tw_transferImg = new QTreeWidget(scrollAreaWidgetContents_2);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem();
        __qtreewidgetitem1->setText(0, QString::fromUtf8("1"));
        tw_transferImg->setHeaderItem(__qtreewidgetitem1);
        tw_transferImg->setObjectName("tw_transferImg");
        tw_transferImg->setGeometry(QRect(0, 0, 651, 151));
        scrollArea_2->setWidget(scrollAreaWidgetContents_2);
        btn_cancelTransfer = new QPushButton(centralwidget);
        btn_cancelTransfer->setObjectName("btn_cancelTransfer");
        btn_cancelTransfer->setGeometry(QRect(670, 460, 191, 30));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 866, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "ARIEL", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Arquivos de Imagens", nullptr));
        btn_addImg->setText(QCoreApplication::translate("MainWindow", "Adicionar Imagem", nullptr));
        btn_remove_Img->setText(QCoreApplication::translate("MainWindow", "Excluir Imagem", nullptr));
        btn_transferImg->setText(QCoreApplication::translate("MainWindow", "Transferir Imagem", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Transfer\303\252ncia de Imagens", nullptr));
        btn_cancelTransfer->setText(QCoreApplication::translate("MainWindow", "Cancelar ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
