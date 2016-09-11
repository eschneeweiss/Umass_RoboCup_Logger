#include "textdata_viewer.h"
#include <QtWidgets>

textData_viewer::textData_viewer(QWidget *parent, QSize initSize) : QWidget(parent)
{
    this->initSize = initSize;
    std::cout<<"textData_viewer initSize: w"<<this->initSize.width()<<", h"<<this->initSize.height()<<std::endl;

    QPushButton *update = new QPushButton();
    update->setText(tr("Update"));
    QObject::connect(update, SIGNAL(clicked()), this, SLOT(updateTree()));

    treeWidget = new QTreeWidget();
    //treeWidget->setHeaderLabel(QString("packet data:"));
    QTreeWidgetItem* headerItem = new QTreeWidgetItem();
    headerItem->setText(0,QString("field"));
    headerItem->setText(1,QString("value"));
    treeWidget->setHeaderItem(headerItem);

    SSL_WrapperPacket temp;
    createTree(temp.GetDescriptor(), treeWidget->invisibleRootItem());

    QVBoxLayout *vLayout = new QVBoxLayout(this);
    vLayout->addWidget(update);
    vLayout->addWidget(treeWidget);
}

QSize textData_viewer::sizeHint(){
    std::cout<<"textData_viewer sizeHint called"<<std::endl;
    return initSize;
}

void textData_viewer::updateDisplay(SSL_WrapperPacket *packet){
    this->packet = packet;
    //updateTree();
}

void textData_viewer::updateTree(){
    if (!packet || !packet->IsInitialized()){
        return;
    }
    updateTreeRecursive(packet, treeWidget->invisibleRootItem());
}

void textData_viewer::createTree(const google::protobuf::Descriptor *d, QTreeWidgetItem *parent){
    for(int i = 0; i < d->field_count(); i++){
        const google::protobuf::FieldDescriptor *fd = d->field(i);
        QTreeWidgetItem *treeItem = new QTreeWidgetItem(parent);

        if (fd->is_optional() || fd->is_required()){
            if (fd->cpp_type() == fd->CPPTYPE_MESSAGE){
                treeItem->setText(0, QString::fromStdString(fd->name()));
                createTree(fd->message_type(), treeItem);
            }
            else {
                treeItem->setText(0, QString::fromStdString(fd->name()).append(": "));
            }
        }
        else if(fd->is_repeated()){
            treeItem->setText(0, QString::fromStdString(fd->name()));
            QTreeWidgetItem *repeatedItem = new QTreeWidgetItem(treeItem);

            repeatedItem->setText(0, QString::number(1));
            if (fd->cpp_type() == fd->CPPTYPE_MESSAGE){
                createTree(fd->message_type(), repeatedItem);
            }
            repeatedItem->setTextColor(0, QColor("red"));
        }
        treeItem->setTextColor(0, QColor("red"));
    }
}

void textData_viewer::updateTreeRecursive(const google::protobuf::Message *m, QTreeWidgetItem *parent){
    const google::protobuf::Descriptor *md = m->GetDescriptor();
    const google::protobuf::Reflection *mr = m->GetReflection();

    if (md->field_count() != parent->childCount()){
        throw;
    }

    for(int i = 0; i < md->field_count(); i++){
        const google::protobuf::FieldDescriptor *mfd = md->field(i);
        QTreeWidgetItem *treeItem = parent->child(i);

        if (mfd->is_optional() || mfd->is_required()){
            if (mr->HasField(*m, mfd)){
                switch((int)mfd->cpp_type()){
                    case 1: treeItem->setText(1, QString::number(mr->GetInt32(*m, mfd)));break;//mfd->CPPTYPE_INT32
                    case 2: treeItem->setText(1, QString::number(mr->GetInt64(*m, mfd)));break;//mfd->CPPTYPE_INT64
                    case 3: treeItem->setText(1, QString::number(mr->GetUInt32(*m, mfd)));break;//mfd->CPPTYPE_UINT32
                    case 4: treeItem->setText(1, QString::number(mr->GetUInt64(*m, mfd)));break;//mfd->CPPTYPE_UINT64
                    case 5: treeItem->setText(1, QString::number(mr->GetDouble(*m, mfd)));break;//mfd->CPPTYPE_DOUBLE
                    case 6: treeItem->setText(1, QString::number(mr->GetFloat(*m, mfd)));break;//mfd->CPPTYPE_FLOAT
                    case 7: treeItem->setText(1, QString::number(mr->GetBool(*m, mfd)));break;//mfd->CPPTYPE_BOOL
                    case 8: break;//mfd->CPPTYPE_ENUM
                    case 9: treeItem->setText(1, QString::fromStdString(mr->GetString(*m, mfd)));break;//mfd->CPPTYPE_STRING
                    case 10: updateTreeRecursive(&mr->GetMessage(*m, mfd), treeItem);break;//mfd->CPPTYPE_MESSAGE
                }
                treeItem->setTextColor(0, QColor("blue"));
                treeItem->setTextColor(1, QColor("blue"));
            }
            else {
                fillTreeRed(treeItem);
            }
        }
        else if(mfd->is_repeated()){
            fillTreeRed(treeItem);
            if (mr->FieldSize(*m, mfd) > 0){
                treeItem->setTextColor(0, QColor("blue"));
                int j;//was working here last
                for (j = 0; j < mr->FieldSize(*m, mfd); j++){
                    QTreeWidgetItem *repeatedItem;
                    if (j < treeItem->childCount()){
                        repeatedItem = treeItem->child(j);
                    }
                    else {
                        repeatedItem = new QTreeWidgetItem(treeItem);
                        repeatedItem->setText(0, QString::number(j + 1));
                    }
                    switch((int)mfd->cpp_type()){
                        case 1: treeItem->setText(1, QString::number(mr->GetRepeatedInt32(*m, mfd, j)));break;//mfd->CPPTYPE_INT32
                        case 2: treeItem->setText(1, QString::number(mr->GetRepeatedInt64(*m, mfd, j)));break;//mfd->CPPTYPE_INT64
                        case 3: treeItem->setText(1, QString::number(mr->GetRepeatedUInt32(*m, mfd, j)));break;//mfd->CPPTYPE_UINT32
                        case 4: treeItem->setText(1, QString::number(mr->GetRepeatedUInt64(*m, mfd, j)));break;//mfd->CPPTYPE_UINT64
                        case 5: treeItem->setText(1, QString::number(mr->GetRepeatedDouble(*m, mfd, j)));break;//mfd->CPPTYPE_DOUBLE
                        case 6: treeItem->setText(1, QString::number(mr->GetRepeatedFloat(*m, mfd, j)));break;//mfd->CPPTYPE_FLOAT
                        case 7: treeItem->setText(1, QString::number(mr->GetRepeatedBool(*m, mfd, j)));break;//mfd->CPPTYPE_BOOL
                        case 8: ;break;//mfd->CPPTYPE_ENUM
                        case 9: treeItem->setText(1, QString::fromStdString(mr->GetRepeatedString(*m, mfd, j)));break;//mfd->CPPTYPE_STRING
                        case 10: updateTreeRecursive(&mr->GetRepeatedMessage(*m, mfd, j), repeatedItem);break;//mfd->CPPTYPE_MESSAGE
                    }
                    repeatedItem->setTextColor(0, QColor("blue"));
                    repeatedItem->setTextColor(1, QColor("blue"));
                }
                for (int k = j; k < treeItem->childCount(); k++){
                    fillTreeRed(treeItem->child(k));
                }
            }
        }
    }
}

void textData_viewer::fillTreeRed(QTreeWidgetItem *tree){
    if (tree->textColor(0) == QColor("red")){
        return;
    }
    tree->setTextColor(0, QColor("red"));
    tree->setTextColor(1, QColor("red"));
    for (int i = 0; i < tree->childCount(); i++){
        fillTreeRed(tree->child(i));
    }
}

textData_viewer::~textData_viewer(){
    //clean up
    delete treeWidget;
}
