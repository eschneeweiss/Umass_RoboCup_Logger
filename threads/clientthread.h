#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H

#include <QThread>
#include "util/timer.h"
#include "proto/cpp/messages_robocup_ssl_wrapper.pb.h"
#include "net/robocup_ssl_client.h"

class MainWindow;

class clientThread : public QThread
{
protected:
    void run();

public:
    clientThread(MainWindow *mw);
    ~clientThread();
private:
    bool runThread = true;
    MainWindow *mw;
    RoboCupSSLClient client;
    SSL_WrapperPacket *packet;
};

#endif // CLIENTTHREAD_H
