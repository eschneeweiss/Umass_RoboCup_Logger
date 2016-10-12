#ifndef LOG_VIEWER_H
#define LOG_VIEWER_H

#include <QWidget>
#include "proto/cpp/messages_robocup_ssl_wrapper.pb.h"
#include "protobuf_writer.h"
#include "protobuf_reader.h"
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <QThread>
#include "util/timer.h"
#include <string>
#include "threads/playbackthread.h"
#include <QListWidget>
#include "trashcan.h"
//#include "mainwindow.h"
//temp
#include <iostream>
#include <QSize>

using namespace std;

class MainWindow;

class log_viewer : public QWidget
{
    Q_OBJECT

public:
    explicit log_viewer(QWidget *parent);
    ~log_viewer();

    void storePacket(SSL_WrapperPacket *packet);
    bool playBackLog(char *fileName, unsigned int frame, double speed);
    bool createNewLogFile();
    bool setPath(char *p);
    bool getLogs();
    bool isValidLog(char *log);
    bool isValidPath(char *p);

    playBackThread *pbt = NULL;

public slots:

    bool playBackLog(QListWidgetItem * file);

private:

    MainWindow *mw;
    protobuf_reader *pbr = NULL;
    protobuf_writer *pbw = NULL;
    char defaultPath[80]; //char *defaultPath = "../ssl_Logs/";
    char *path = NULL;
    char fileType[80]; //char *fileType = ".ssl";
    QListWidget *listWidget;
    struct stat sb;


signals:

public slots:

};

#endif // LOG_VIEWER_H
