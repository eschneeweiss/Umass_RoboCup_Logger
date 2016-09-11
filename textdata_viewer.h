#ifndef TEXTDATA_VIEWER_H
#define TEXTDATA_VIEWER_H

#include <QWidget>
#include "proto/cpp/messages_robocup_ssl_wrapper.pb.h"
#include <QTreeWidget>
//temp
#include <iostream>

class textData_viewer : public QWidget
{
    Q_OBJECT
public:
    explicit textData_viewer(QWidget *parent, QSize initSize);
    ~textData_viewer();

    virtual QSize sizeHint();

private:
    QSize initSize;
    SSL_WrapperPacket *packet = NULL;
    QTreeWidget *treeWidget;
    void updateTreeRecursive(const google::protobuf::Message *m, QTreeWidgetItem *parent);
    void updateTreeRecursiveV2(const google::protobuf::Message *m, QTreeWidgetItem *parent);
    void createTree(const google::protobuf::Descriptor *d, QTreeWidgetItem *parent);
    void fillTreeRed(QTreeWidgetItem *tree);
    
signals:

private slots:
    void updateTree();
    
public slots:
    void updateDisplay(SSL_WrapperPacket *packet);
};

#endif // TEXTDATA_VIEWER_H
