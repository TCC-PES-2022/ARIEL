#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QObject>
#include "UI_API.h"
#include "coregui.h"


class userManager : public QObject
{
    Q_OBJECT
public:
    explicit userManager(QObject *parent = nullptr);

public:
   void authenticarUser(QString userName,QString password);
   void confirmeReceivedAuthenticationResponse();
signals:

};

#endif // USERMANAGER_H
