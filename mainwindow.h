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
file    mainwindow.h
brief   C++ interface: MainWindow
author  Eddy Schneeweiss (C) 2016
*/
//========================================================================

#include <QMainWindow>
#include "log_viewer.h"
#include "timestep_viewer.h"
#include "graph_viewer.h"
#include "textdata_viewer.h"
#include "proto/cpp/messages_robocup_ssl_wrapper.pb.h"
#include "threads/clientthread.h"

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    log_viewer *lv;
    timestep_viewer *tv;
    graph_viewer *gv;
    textData_viewer *tdv;

    explicit MainWindow(char *path, char *filename, unsigned int frame, double speed, char *configFile);
    ~MainWindow();

    //parameters: packet
    //Emits displayTimeStep signal and sends packet to logger if recording
    void updateTimeStep(SSL_WrapperPacket *packet);

    //Updates the state of the mainwindow for playback
    //Called by the log_viewer object after a user selects a perticular log file for playback
    void logClicked();

public slots:
    //Updates the state of the window for when the playLive button is pressed
    void playLiveClicked();
    //Updates the state of the window for when the record button is pressed
    void recordClicked();

signals:
    //parameters: packet
    //When Emitted sends the packet to all Highlevel packet displaying widgets
    void displayTimeStep(SSL_WrapperPacket *packet);

private:
    bool recording = false;
    bool playingLiveFeed = false;
    bool playingLogFile = false;
    clientThread *ct;
};

#endif // MAINWINDOW_H
