#include "playbackthread.h"
#include "mainwindow.h"

playBackThread::playBackThread(protobuf_reader *pbr, MainWindow *mw)
{
    this->pbr = pbr;
    this->mw = mw;
    packet = new SSL_WrapperPacket();
    frame = 0;
    totalFrames = pbr->getIndexSize();
    paused = true;
    runThread = false;
    timer = new Timer();
}

void playBackThread::run(){
    if (packet){
        getNextValidDetectionPacket();
    }
    startTime = packet->detection().t_capture();
    timer->start();
    while(frame <= totalFrames && runThread){
        if (packet->detection().t_capture() <= startTime + (timer->midtime()*speed)){
            mw->updateTimeStep(packet);
            getNextValidDetectionPacket();
        }
        else{
            Sleep(0.0);
        }
    }
    timer->end();
    if (frame > totalFrames){
        paused = true;
    }
}

void playBackThread::getNextValidDetectionPacket(){
    while (true){
        if (frame > totalFrames){
            break;
        }
        if (pbr->readMessage(frame, packet)){
            break;
        }
        frame++;
    }
    frame++;
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
    return frame - 1;
}

void playBackThread::setFrame(unsigned int frame){
    std::cout<<"setting frame!"<<std::endl;
    stop();

    if (frame <= totalFrames){
        this->frame = frame;
    }
    else {
        this->frame = totalFrames;
    }
    getNextValidDetectionPacket();
    if (!paused){
        play();
    }
    else{
        peek();
    }
}

int playBackThread::getTotalFrames(){
    return totalFrames;
}

void playBackThread::peek(){
    if (!packet->IsInitialized()){
        getNextValidDetectionPacket();
    }
    mw->updateTimeStep(packet);

    /*if (packet){
        mw->updateTimeStep(packet);
    }*/
}

playBackThread::~playBackThread(){
    runThread = false;
    this->wait();
}
