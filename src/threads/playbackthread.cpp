#include "playbackthread.h"
#include "mainwindow.h"

playBackThread::playBackThread(protobuf_reader *pbr, MainWindow *mw)
{
    this->pbr = pbr;
    this->mw = mw;
    packet = new SSL_WrapperPacket();
    currFrame = 0;
    nextFrame = 1;
    packetIsDestroyed = true;
    totalFrames = pbr->getIndexSize();
    paused = true;
    runThread = false;
    timer = new Timer();
}

void playBackThread::run(){
    if (packetIsDestroyed){
        packet = new SSL_WrapperPacket();
        getNextValidDetectionPacket(packet);
    }
    startTime = packet->detection().t_capture();
    timer->start();
    while(currFrame < totalFrames && runThread){
        if (packet->detection().t_capture() <= startTime + (timer->midtime()*speed)){
            mw->updateTimeStep(packet);
            packetIsDestroyed = true;
            currFrame++;
            packet = new SSL_WrapperPacket();
            getNextValidDetectionPacket(packet);
        }
        else{
            Sleep(0.01);//100FPS
        }
    }
    timer->end();
    if (currFrame > totalFrames - 1){
        paused = true;
    }
}

void playBackThread::getNextValidDetectionPacket(SSL_WrapperPacket *packet){
    while (true){
        if (currFrame >= totalFrames){
            break;
        }
        if (pbr->readMessage(currFrame, packet)){
            if (packet->has_detection()) {
                break;
            }
            else if (packet->has_geometry()) {
                mw->updateTimeStep(packet);
                packetIsDestroyed = true;
                packet = new SSL_WrapperPacket();
            }
        }
        currFrame++;
    }
    nextFrame = currFrame + 1;
    packetIsDestroyed = false;
}

void playBackThread::stop(){
    runThread = false;
    this->wait();
}

void playBackThread::pause(){
    if (paused){
        paused = false;
        play();
    }
    else {
        paused = true;
        stop();
    }
}

void playBackThread::play(){
    if (!runThread){
        runThread = true;
        start();
    }
    paused = false;
}

double playBackThread::getSpeed(){
    if (paused){
        return 0;
    }
    return speed;
}

void playBackThread::setSpeed(double newSpeed){
    stop();
    if (newSpeed <= MINSPEED){
        speed = MINSPEED;
    }
    else if (newSpeed >= MAXSPEED){
        speed = MAXSPEED;
    }
    else {
        speed = newSpeed;
    }
    if (!paused){
       play();
    }
}

int playBackThread::getFrame(){
    return currFrame;
}

void playBackThread::setFrame(unsigned int newframe){
    stop();
    if (newframe < totalFrames){
        currFrame = newframe;
    }
    else {
        currFrame = totalFrames - 1;
    }
    packet = new SSL_WrapperPacket();
    getNextValidDetectionPacket(packet);
    if (!paused){
        packetIsDestroyed = false;
        play();
    }
    else{
        mw->updateTimeStep(packet);
        packetIsDestroyed = true;
    }
}

int playBackThread::getTotalFrames(){
    return totalFrames;
}

playBackThread::~playBackThread(){
    runThread = false;
    this->wait();
}
