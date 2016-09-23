//========================================================================
//  This software is free: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License Version 3,
//  as published by the Free Software Foundation.
//
//  This software is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  Version 3 in the file COPYING that came with this distribution.
//  If not, see <http://www.gnu.org/licenses/>.
//========================================================================
/*!
file    mainwindow.cpp
brief   C++ Implementation: MainWindow
author  Eddy Schneeweiss (C) 2016
*/
//========================================================================

#include "mainwindow.h"
#include <QtWidgets>

MainWindow::MainWindow(char *path, char *filename, unsigned int frame, double speed, char *configFile)// : QMainWindow(parent)
{
    printf("path: %s, filename: %s, frame: %u, speed: %f, configFile: %s\n", path, filename, frame, speed, configFile);
    int initH = 720;
    int initW = 1080;
    setWindowTitle(tr("UMass SSL Logger"));

    //resize(initW, initH);

    ct = new clientThread(this);
    playingLiveFeed = true;
    ct->start();


    lv = new log_viewer(this, QSize(initW*0.25,initH*0.25));
    QDockWidget *LVdock = new QDockWidget(tr("Log"), this);
    LVdock->setAllowedAreas(Qt::BottomDockWidgetArea | Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);
    LVdock->setWidget(lv);
    LVdock->setMinimumSize(QSize(initW*0.25,initH*0.25));
    addDockWidget(Qt::RightDockWidgetArea, LVdock);
    //LVdock->resize(initW*0.25,initH*0.25);

    tdv = new textData_viewer(this, QSize(initW*0.25,initH*0.75));
    QDockWidget *TDVdock = new QDockWidget(tr("Text Data"), this);
    TDVdock->setAllowedAreas(Qt::BottomDockWidgetArea | Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);
    TDVdock->setWidget(tdv);
    TDVdock->setMinimumSize(QSize(initW*0.25,initH*0.75));
    addDockWidget(Qt::RightDockWidgetArea, TDVdock);
    //TDVdock->resize(initW*0.25,initH*0.75);
    connect(this, SIGNAL(displayTimeStep(SSL_WrapperPacket*)), tdv, SLOT(updateDisplay(SSL_WrapperPacket*)));

    tv = new timestep_viewer(this, QSize(initW*0.75, initH*0.75));
    QDockWidget *TVdock = new QDockWidget(tr("Time-step"), this);
    TVdock->setAllowedAreas(Qt::BottomDockWidgetArea | Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);
    TVdock->setWidget(tv);
    TVdock->setMinimumSize(QSize(initW*0.75, initH*0.75));
    addDockWidget(Qt::LeftDockWidgetArea, TVdock);
    //TVdock->resize(initW*0.75, initH*0.75);
    connect(this, SIGNAL(displayTimeStep(SSL_WrapperPacket*)), tv, SLOT(updateDisplay(SSL_WrapperPacket*)));

    gv = new graph_viewer(this, QSize(initW*0.75, initH*0.25));
    QDockWidget *GVdock = new QDockWidget(tr("Graph"), this);
    GVdock->setAllowedAreas(Qt::BottomDockWidgetArea | Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);
    GVdock->setWidget(gv);
    GVdock->setMinimumSize(QSize(initW*0.75, initH*0.25));
    addDockWidget(Qt::LeftDockWidgetArea, GVdock);
    //GVdock->resize(initW*0.75, initH*0.25);
    connect(this, SIGNAL(displayTimeStep(SSL_WrapperPacket*)), gv, SLOT(updateDisplay(SSL_WrapperPacket*)));

    //resizeDocks({TVdock, LVdock}, {(int)initW*0.75, (int)initW*0.25}, Qt::Horizontal);
}

MainWindow::~MainWindow()
{
    delete ct;
    delete lv;
    delete tv;
    delete gv;
    delete tdv;
}

void MainWindow::logClicked(){
    playingLiveFeed = false;
    delete ct;
    ct = NULL;
    playingLogFile = true;
    tv->showPlayBackcontrol(lv->pbt);
}

void MainWindow::playLiveClicked(){
    if (playingLiveFeed){
        playingLiveFeed = false;
        delete ct;
        ct = NULL;
        if (lv->pbt){
            playingLogFile = true;
            tv->showPlayBackcontrol(lv->pbt);
            lv->pbt->play();
        }
    }
    else{
        if (playingLogFile){
            lv->pbt->stop();
            playingLogFile = false;
        }
        playingLiveFeed = true;
        tv->hidePlayBackcontrol();
        ct = new clientThread(this);
        ct->start();
    }
}

void MainWindow::recordClicked(){
    if (recording){
        recording = false;
        lv->getLogs();
    }
    else{
        recording = true;
        lv->createNewLogFile();
    }
}

void MainWindow::updateTimeStep(SSL_WrapperPacket *packet){
    if (packet == NULL){
        return;
    }
    if (recording){
        lv->storePacket(packet);
    }
    if (playingLiveFeed || playingLogFile){
        emit displayTimeStep(packet);
        std::cout << "succesfully displaying packet with frame number: " << packet->detection().frame_number() << std::endl;
    }
}
