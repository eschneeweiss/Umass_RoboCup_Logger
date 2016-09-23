#include "log_viewer.h"
#include "mainwindow.h"


log_viewer::log_viewer(QWidget *parent, QSize initSize) : QWidget(parent)
{
    mw = (MainWindow*)parent;
    this->initSize = initSize;
    std::cout<<"log_viewer initSize: w"<<this->initSize.width()<<", h"<<this->initSize.height()<<std::endl;

    listWidget = new QListWidget(this);
    strcpy(defaultPath, "../ssl_Logs/");
    strcpy(fileType, ".ssl");
    setPath(defaultPath);

    getLogs();
    QObject::connect(listWidget, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(playBackLog(QListWidgetItem *)));

    QVBoxLayout *vLayout = new QVBoxLayout(this);
    vLayout->addWidget(listWidget);
}

QSize log_viewer::sizeHint(){
    std::cout<<"log_viewer sizeHint called"<<std::endl;
    return initSize;
}

bool log_viewer::playBackLog(QListWidgetItem * fileName){
    //end existing playBackThread, if any
    if (pbt){
        delete pbt;
    }
    if (!setPath(path)){
        return false;
    }
    char fileToOpen[100] = "";
    strcat(fileToOpen, path);
    strcat(fileToOpen, fileName->text().toStdString().c_str());
    try{
        pbr = new protobuf_reader(fileToOpen);
    }
    catch(...){
        return false;
    }
    //start playBackThread
    pbt = new playBackThread(pbr, mw);
    mw->logClicked();
    //temp: should be pbt->peek();
    pbt->setFrame(1);
    return true;
}

bool log_viewer::createNewLogFile(){
    if (!setPath(path))
    {
        return false;
    }
    time_t now = time(0);
    struct tm tstruct;
    char timeStamp[80];
    tstruct = *localtime(&now);
    strftime(timeStamp, sizeof(timeStamp), "%Y-%m-%d.%X", &tstruct);

    char fileToOpen[100] = "";
    strcat(fileToOpen, path);
    strcat(fileToOpen, timeStamp);
    strcat(fileToOpen, fileType);
    if (pbw){
        delete pbw;
    }
    try{
        pbw = new protobuf_writer(fileToOpen);
    }
    catch(...){
        return true;
    }
    return true;
}

void log_viewer::storePacket(SSL_WrapperPacket *packet){
    pbw->writeMessage(packet);
}

bool log_viewer::getLogs(){
    if (!setPath(path)){
        return false;
    }
    DIR *mydir = opendir(path);
    listWidget->clear();
    struct dirent *contents = readdir(mydir);
    while(contents){
        int l1 = strlen(contents->d_name);
        int l2 = strlen(fileType);
        if (l1 >= l2 && strcmp(&contents->d_name[l1 - l2], fileType) == 0){
            listWidget->addItem(contents->d_name);
        }
        contents = readdir(mydir);
    }
    closedir(mydir);
    listWidget->sortItems(Qt::DescendingOrder);
    return true;
}

bool log_viewer::setPath(char *p){
    if (path != p){
        path = p;
    }

    if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
    {
        return true;
    }
    else if (mkdir(path, S_IRWXU | S_IRWXG | S_IRWXO) == 0){
        getLogs();
        return true;
    }
    else if (strcmp(path, defaultPath) == 0){
        return false;
    }
    else{
        path = defaultPath;
        return setPath(path);
    }

}

log_viewer::~log_viewer(){
    //clean up
    delete pbw;
    delete pbr;
    delete pbt;
}

