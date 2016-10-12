#include "clientthread.h"
#include "mainwindow.h"

clientThread::clientThread(MainWindow *mw)
{
    this->mw = mw;
    packet = new SSL_WrapperPacket();
}

void clientThread::run(){
    static const double minDuration = 0.01; //100FPS
    client.open(false);
    while(runThread) {
        while (client.receive(*packet)) {
            if(packet->IsInitialized()){
                mw->updateTimeStep(packet);
            }
            else{
                std::cout<<"packet not properly initulized"<<std::endl;
            }
            packet = new SSL_WrapperPacket();
        }
        Sleep(minDuration);
    }
}

clientThread::~clientThread(){
    runThread = false;
    this->wait();
}
