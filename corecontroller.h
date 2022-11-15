#ifndef CORECONTROLLER_H
#define CORECONTROLLER_H

#include <QObject>
#include <QThread>
#include "UI_API.h"
#include <QDebug>
#include "iimagemanager.h"
#include "icommunicationmanager.h"
#include "iauthentication.h"
#include "ilogger.h"

using namespace std;
class CoreController : public QObject
{
    Q_OBJECT
public:
    explicit CoreController(QObject *parent = nullptr);

signals:
    //void authenticationResponse(int authetincationStatus);

public slots:

    void start();                   // loop principal da coreController

private:
    void parseFindStub();

    bool isRun;                     // variável que controlar se a coreController está no loop principal ou não
    ImageHandlerPtr imageHandler;
    CommunicationHandlerPtr comHandler;

    string homePath;
    char **images = NULL;
    int images_size = 0;
    string targetIp;
    unsigned short targetPort;
};


#endif // CORECONTROLLER_H
