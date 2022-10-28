#ifndef COREGUI_H
#define COREGUI_H



#include <QObject>
#include <QDebug>
#include "UI_API.h"

static st_ui_aut auteticationGUI;                // Struct for authentication status managing
static st_ui_conexao conexaoGUI;
static st_ui_image imagemGUI;
class CoreGUI : public QObject
{
    Q_OBJECT
public:
    explicit CoreGUI(QObject *parent = nullptr);

signals:
    void loginWindowsUpdate(int authetincationStatus);                   // signal with authentication response for loginWindow GUI update;
    void imageFileUpdate(char **images,int tam);
public slots:
     void start();


private:
    bool isRun;
};

#endif // COREGUI_H
