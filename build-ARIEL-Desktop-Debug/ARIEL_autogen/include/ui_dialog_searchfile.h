/********************************************************************************
** Form generated from reading UI file 'dialog_searchfile.ui'
**
** Created by: Qt User Interface Compiler version 6.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_SEARCHFILE_H
#define UI_DIALOG_SEARCHFILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog_searchFIle
{
public:
    QComboBox *comboBox;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QTreeWidget *treeWidget;
    QPushButton *btn_selectionImg;
    QPushButton *btn_cancel;

    void setupUi(QDialog *Dialog_searchFIle)
    {
        if (Dialog_searchFIle->objectName().isEmpty())
            Dialog_searchFIle->setObjectName("Dialog_searchFIle");
        Dialog_searchFIle->resize(807, 563);
        comboBox = new QComboBox(Dialog_searchFIle);
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(0, 10, 791, 29));
        scrollArea = new QScrollArea(Dialog_searchFIle);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setGeometry(QRect(0, 50, 791, 431));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 789, 429));
        treeWidget = new QTreeWidget(scrollAreaWidgetContents);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName("treeWidget");
        treeWidget->setGeometry(QRect(0, 0, 791, 431));
        scrollArea->setWidget(scrollAreaWidgetContents);
        btn_selectionImg = new QPushButton(Dialog_searchFIle);
        btn_selectionImg->setObjectName("btn_selectionImg");
        btn_selectionImg->setGeometry(QRect(10, 500, 371, 30));
        btn_cancel = new QPushButton(Dialog_searchFIle);
        btn_cancel->setObjectName("btn_cancel");
        btn_cancel->setGeometry(QRect(420, 500, 371, 30));

        retranslateUi(Dialog_searchFIle);

        QMetaObject::connectSlotsByName(Dialog_searchFIle);
    } // setupUi

    void retranslateUi(QDialog *Dialog_searchFIle)
    {
        Dialog_searchFIle->setWindowTitle(QCoreApplication::translate("Dialog_searchFIle", "Dialog", nullptr));
        btn_selectionImg->setText(QCoreApplication::translate("Dialog_searchFIle", "Selecionar Imagem", nullptr));
        btn_cancel->setText(QCoreApplication::translate("Dialog_searchFIle", "Cancelar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_searchFIle: public Ui_Dialog_searchFIle {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_SEARCHFILE_H
