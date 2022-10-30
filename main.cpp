#include "mainwindow.h"
#include "loginwindow.h"
#include <QSplashScreen>
#include <QTimer>
#include <QThread>
#include "coregui.h"
#include "corecontroller.h"

#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    QSplashScreen *splashScreen=new QSplashScreen;
    splashScreen->setPixmap(QPixmap(":/Embraer/img/Embraer/Embraer_E2.jpg"));
    splashScreen->show();

    LoginWindow loginScreen;
    MainWindow mainScreen;

    QThread coreGUI_thread;                                                                                                  // Thread que vai rodar o coreGui
    QThread coreController_thread;                                                                                          // Thread que vai rodar o coreController

    CoreGUI coreGui;                                                                                                       // Objeto da classe coreGUI
    CoreController coreController;                                                                                        // Objeto da classe coreController

    coreGui.moveToThread(&coreGUI_thread);                                                                               // Mover o objeto coreGui para a respectiva thread
    coreController.moveToThread(&coreController_thread);                                                                // Mover o objeto coreGui para a respectiva thread

    QObject::connect(&coreGui,&CoreGUI::loginWindowsUpdate,&loginScreen,&LoginWindow::updateAuthenticationRequest);

    QObject::connect(&coreController_thread,&QThread::started,&coreController,&CoreController::start);
    QObject::connect(&coreGUI_thread,&QThread::started,&coreGui,&CoreGUI::start);


    QObject::connect(&loginScreen,&LoginWindow::loginSucessAuthentication,&mainScreen,&MainWindow::show);

    QObject::connect(&coreGui,&CoreGUI::imageFileUpdate,&mainScreen,&MainWindow::updateInterfaceImage);

    QObject::connect(&coreGui,&CoreGUI::getStatusImageTransfer,&mainScreen,&MainWindow::updateProgressTransfer);


    QObject::connect(&coreGui,&CoreGUI::signalFailTransfer,&mainScreen,&MainWindow::alertFailTransfer);

        //QObject::connect(&a,&QApplication::aboutToQuit,&coreGui,&CoreGUI::quit);
        //QObject::connect(&a,&QApplication::aboutToQuit,&coreController,&CoreController::quit);



          coreController_thread.start();
          coreGUI_thread.start();



    QTimer::singleShot(2000,splashScreen,SLOT(close()));
    //QTimer::singleShot(2000,&loginScreen,SLOT(show()));
    QTimer::singleShot(2000,&loginScreen,SLOT(show()));
    return a.exec();
}
