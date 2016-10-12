#include "timestep_viewer.h"
#include "mainwindow.h"

timestep_viewer::timestep_viewer(QWidget *parent) : QWidget(parent)
{
    mw =  (MainWindow *)parent;

    playLive = new QPushButton();
    playLive->setText(tr("Playing Live ..."));
    QObject::connect(playLive, SIGNAL(clicked()), parent, SLOT(playLiveClicked()));

    record = new QPushButton();
    record->setText(tr("Record"));
    QObject::connect(record, SIGNAL(clicked()), parent, SLOT(recordClicked()));

    hLayout1 = new QHBoxLayout();
    hLayout1->addWidget(playLive);
    hLayout1->addWidget(record);
    
    jumpBack = new QPushButton();
    jumpBack->setText(tr("Jump Back"));
    QObject::connect(jumpBack, SIGNAL(clicked()), this, SLOT(jumpBackClicked()));

    slowDown = new QPushButton();
    slowDown->setText(tr("Slow Down"));
    QObject::connect(slowDown, SIGNAL(clicked()), this, SLOT(slowDownClicked()));

    pauseNplay = new QPushButton();
    pauseNplay->setText(tr("Play"));
    QObject::connect(pauseNplay, SIGNAL(clicked()), this, SLOT(pauseNplayClicked()));

    speedUp = new QPushButton();
    speedUp->setText(tr("Speed Up"));
    QObject::connect(speedUp, SIGNAL(clicked()), this, SLOT(speedUpClicked()));

    jumpForward = new QPushButton();
    jumpForward->setText(tr("Jump Forward"));
    QObject::connect(jumpForward, SIGNAL(clicked()), this, SLOT(jumpForwardClicked()));

    hLayout2 = new QHBoxLayout();
    hLayout2->addWidget(jumpBack);
    hLayout2->addWidget(slowDown);
    hLayout2->addWidget(pauseNplay);
    hLayout2->addWidget(speedUp);
    hLayout2->addWidget(jumpForward);

    frameSpinBox = new fSpinBox();

    frameSlider = new fSlider();

    hLayout3 = new QHBoxLayout();
    hLayout3->addWidget(frameSpinBox);
    hLayout3->addWidget(frameSlider);

    //speedSpinBox = new QSpinBox();
    //speedSpinBox->setRange(((MainWindow*)parent)->lv->pbt->MINSPEED, ((MainWindow*)parent)->lv->pbt->MAXSPEED);

    view = new GLSoccerView();

    vLayout = new QVBoxLayout(this);
    vLayout->addLayout(hLayout1);
    vLayout->addLayout(hLayout2);
    vLayout->addLayout(hLayout3);
    vLayout->addWidget(view);

    this->show();

    hidePlayBackcontrol();
}

void timestep_viewer::updateDisplay(SSL_WrapperPacket *packet){
    if (pbt){
        int frame = pbt->getFrame();
        if (frame != frameSpinBox->value())
            frameSpinBox->setValue(frame);
        if (frame != frameSlider->value())
            frameSlider->setValue(frame);
    }

    if (packet->has_detection()){
        view->updateDetection(packet->detection());
        //std::cout<<"view updated"<<std::endl;
    }
    if (packet->has_geometry()){
        view->updateFieldGeometry(packet->geometry().field());
    }
    mw->trashCan->throwAway(packet);
}

void timestep_viewer::updateButtons(bool recording, bool playingLiveFeed, bool playingLogFile){
    if (recording) {
        record->setText(tr("Recording ..."));
    }
    else {
        record->setText(tr("Record"));
    }

    if (playingLiveFeed) {
        playLive->setText(tr("Playing Live ..."));
    }
    else {
        playLive->setText(tr("Play Live"));
    }

    if (playingLogFile) {
        if (pbt){
            if (pbt->paused){
                pauseNplay->setText(tr("Play"));
            }
            else {
                pauseNplay->setText(tr("Pause"));
            }
        }
    }
    else {
        pauseNplay->setText(tr("Play"));
    }
}

void timestep_viewer::jumpBackClicked(){
    if (pbt){
        unsigned int newFrame = pbt->getFrame();
        if (newFrame < 200){
            newFrame = 0;
        }
        else{
            newFrame -= 200;
        }
        pbt->setFrame(newFrame);
    }
}

void timestep_viewer::slowDownClicked(){
    if (pbt){
        pbt->setSpeed(pbt->getSpeed()/2);
    }
}

void timestep_viewer::pauseNplayClicked(){
    if (pbt){
        pbt->pause();
        if (pbt->paused){
            pauseNplay->setText(tr("Play"));
        }
        else {
            pauseNplay->setText(tr("Pause"));
        }
    }
}

void timestep_viewer::speedUpClicked(){
    if (pbt){
        pbt->setSpeed(pbt->getSpeed()*2);
    }
}

void timestep_viewer::jumpForwardClicked(){
    if (pbt){
        pbt->setFrame(pbt->getFrame() + 200);
    }
}

void timestep_viewer::jumpToFrame(int frame){
    std::cout<<"frameChanged signal recieved"<<std::endl;
    if (pbt){
        if (!pbt->paused)
            pbt->pause();
        pbt->setFrame(frame);
    }
}

void timestep_viewer::stop(){
    if (pbt){
        if (!pbt->paused){
            pbt->pause();
        }
    }
}

void timestep_viewer::hidePlayBackcontrol(){
    pbt = NULL;
    jumpBack->hide();
    slowDown->hide();
    pauseNplay->hide();
    speedUp->hide();
    jumpForward->hide();

    if (frameSpinBox){
        frameSpinBox->hide();
    }
    if (frameSlider){
        frameSlider->hide();
    }
}

void timestep_viewer::showPlayBackcontrol(playBackThread *pbt){
    this->pbt = pbt;
    frameSpinBox->setRange(0, pbt->getTotalFrames());
    //QObject::connect(frameSpinBox, SIGNAL(valueChanged(int)), frameSlider, SLOT(setValue(int)));
    QObject::connect(frameSpinBox, SIGNAL(frameChanged(int)), this, SLOT(jumpToFrame(int)));

    frameSlider->setRange(0, pbt->getTotalFrames());
    //QObject::connect(frameSlider, SIGNAL(valueChanged(int)), frameSpinBox, SLOT(setValue(int)));
    QObject::connect(frameSlider, SIGNAL(frameChanged(int)), this, SLOT(jumpToFrame(int)));

    jumpBack->show();
    slowDown->show();
    pauseNplay->show();
    speedUp->show();
    jumpForward->show();
    frameSpinBox->show();
    frameSlider->show();
}

timestep_viewer::~timestep_viewer(){
}
