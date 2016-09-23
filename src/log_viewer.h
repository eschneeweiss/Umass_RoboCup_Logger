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
    explicit log_viewer(QWidget *parent, QSize initSize);
    ~log_viewer();

    void storePacket(SSL_WrapperPacket *packet);
    bool createNewLogFile();
    bool setPath(char *p);
    bool getLogs();
    virtual QSize sizeHint();

    playBackThread *pbt = NULL;

public slots:

    bool playBackLog(QListWidgetItem * file);

private:

    MainWindow *mw;
    QSize initSize;
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
