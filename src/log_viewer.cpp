#include "log_viewer.h"
#include "mainwindow.h"


log_viewer::log_viewer(QWidget *parent) : QWidget(parent)
{
    mw = (MainWindow*)parent;

    listWidget = new QListWidget(this);
    strcpy(defaultPath, "ssl_Logs/");
    strcpy(fileType, ".ssl");
    setPath(defaultPath);

    QObject::connect(listWidget, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(playBackLog(QListWidgetItem *)));

    QVBoxLayout *vLayout = new QVBoxLayout(this);
    vLayout->addWidget(listWidget);
}

bool log_viewer::playBackLog(QListWidgetItem *fileName){
    //end existing playBackThread, if any
    if (pbt){
        delete pbt;
    }
    if (!isValidPath(path)){
        return false;
    }
    char fileToOpen[100] = "";
    strcat(fileToOpen, path);
    strcat(fileToOpen, fileName->text().toStdString().c_str());
    if (isValidLog((char*)fileName->text().toStdString().c_str())) {
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
    else {
        std::cout<<"invalid file name"<<std::endl;
        getLogs();
        return false;
    }
}

bool log_viewer::playBackLog(char *fileName, unsigned int frame, double speed){
    //end existing playBackThread, if any
    if (pbt){
        delete pbt;
    }
    if (!isValidPath(path)){
        return false;
    }
    char fileToOpen[100] = "";
    strcat(fileToOpen, path);
    strcat(fileToOpen, fileName);
    std::cout<<"about to attempt to open a file"<<std::endl;
    if (isValidLog(fileName)) {
        try{
            pbr = new protobuf_reader(fileToOpen);
        }
        catch(...){
            return false;
        }
        //start playBackThread
        pbt = new playBackThread(pbr, mw);
        std::cout<<"about to say log clicked"<<std::endl;
        mw->logClicked();
        pbt->setFrame(frame);
        pbt->setSpeed(speed);
        return true;
    }
    else {
        std::cout<<"invalid file name"<<std::endl;
        getLogs();
        return false;
    }
}

bool log_viewer::isValidLog(char *log){
    if (!isValidPath(path)){
        return false;
    }
    DIR *mydir = opendir(path);
    struct dirent *contents = readdir(mydir);
    while(contents){
        int l1 = strlen(contents->d_name);
        int l2 = strlen(fileType);
        if (l1 >= l2 && strcmp(&contents->d_name[l1 - l2], fileType) == 0){
            if (strcmp(contents->d_name, log) == 0) {
                return true;
            }
        }
        contents = readdir(mydir);
    }
    closedir(mydir);
    return false;
}

bool log_viewer::createNewLogFile(){
    if (!isValidPath(path)){
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
    mw->trashCan->throwAway(packet);
}

bool log_viewer::getLogs(){
    if (!isValidPath(path)){
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

    if (isValidPath(path)){
        getLogs();
        return true;
    }
    else if (mkdir(path, S_IRWXU | S_IRWXG | S_IRWXO) == 0){
        getLogs();
        return true;
    }
    else if (strcmp(path, defaultPath) == 0){
        getLogs();
        return false;
    }
    else{
        path = defaultPath;
        return setPath(path);
    }

}

bool log_viewer::isValidPath(char *p){
    if (stat(p, &sb) == 0 && S_ISDIR(sb.st_mode)){
        return true;
    }
    else {
        return false;
    }
}

log_viewer::~log_viewer(){
    //clean up
    delete pbw;
    delete pbr;
    delete pbt;
}

