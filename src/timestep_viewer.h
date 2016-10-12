#ifndef TIMESTEP_VIEWER_H
#define TIMESTEP_VIEWER_H

#include <QWidget>
#include "proto/cpp/messages_robocup_ssl_wrapper.pb.h"
#include "soccerview.h"
#include "threads/playbackthread.h"
#include "fspinbox.h"
#include "fslider.h"
#include "trashcan.h"
//temp
#include <iostream>

class MainWindow;

class timestep_viewer : public QWidget
{
    Q_OBJECT
public:
    QPushButton *playLive;
    QPushButton *record;
    QHBoxLayout *hLayout1;
    QPushButton *jumpBack;
    QPushButton *slowDown;
    QPushButton *pauseNplay;
    QPushButton *speedUp;
    QPushButton *jumpForward;
    QHBoxLayout *hLayout2;
    fSpinBox *frameSpinBox;
    fSlider *frameSlider;
    //QSpinBox *speedSpinBox;
    //QSlider *speedSlider;
    QVBoxLayout *vLayout;
    QHBoxLayout *hLayout3;

    GLSoccerView *view;

    explicit timestep_viewer(QWidget *parent);
    ~timestep_viewer();

    void hidePlayBackcontrol();
    void showPlayBackcontrol(playBackThread *pbt);

    void updateButtons(bool recording, bool playingLiveFeed, bool playingLogFile);

private:
    MainWindow *mw;
    playBackThread *pbt = NULL;

signals:

private slots:
    void jumpBackClicked();
    void slowDownClicked();
    void pauseNplayClicked();
    void speedUpClicked();
    void jumpForwardClicked();
    void jumpToFrame(int frame);
    void stop();

public slots:
    void updateDisplay(SSL_WrapperPacket *packet);

};

#endif // TIMESTEP_VIEWER_H
