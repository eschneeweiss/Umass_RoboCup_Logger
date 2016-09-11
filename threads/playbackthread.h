#ifndef PLAYBACKTHREAD_H
#define PLAYBACKTHREAD_H

#include <QThread>
#include "protobuf_reader.h"
#include "util/timer.h"
#include "proto/cpp/messages_robocup_ssl_wrapper.pb.h"

class MainWindow;

class playBackThread : public QThread
{
protected:
    void run();

public:
    playBackThread(protobuf_reader *pbr, MainWindow *mw);
    void stop();
    void pause();
    void play();
    double getSpeed();
    void setSpeed(double newSpeed);
    int getFrame();
    void setFrame(unsigned int frame);
    int getTotalFrames();
    void peek();
    const double MAXSPEED = 64;//2^6
    const double MINSPEED = 0.015625;//(1/2)^6
    bool paused;
    ~playBackThread();
private:
    bool runThread;
    protobuf_reader *pbr;
    MainWindow *mw;
    SSL_WrapperPacket *packet;
    unsigned int frame;
    unsigned int totalFrames;
    Timer *timer;
    double startTime = 0;
    double speed = 1;

    void getNextValidDetectionPacket();
};

#endif // PLAYBACKTHREAD_H
