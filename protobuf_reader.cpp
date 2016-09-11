#include "protobuf_reader.h"

protobuf_reader::protobuf_reader(char *fileName)
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    input.open(fileName, ios::in | ios::binary);
    if (!input){
        throw "failed to open file";
    }
    createIndex();
}

unsigned int protobuf_reader::getIndexSize(){
    return index.size();
}

bool protobuf_reader::readMessage(unsigned int timeStep, google::protobuf::Message *message) {
    if (timeStep >= index.size()){
        message = NULL;
        return false;
    }
    input.seekg(index[timeStep]);

    char *bytes = new char[sizeof(int)];
    input.read(bytes, sizeof(int));
    unsigned int messageSize = *((int *)bytes);

    bytes = new char[messageSize];
    input.seekg(index[timeStep] + sizeof(int));
    input.read(bytes, messageSize);

    if (!message->ParseFromArray(bytes, messageSize)){
        message = NULL;
        return false;
    }
    return true;
}

void protobuf_reader::createIndex(){
    unsigned int position = 0;
    unsigned int messageSize = 0;
    char *bytes = new char[sizeof(int)];

    input.seekg (0, ios::end);
    unsigned int end = input.tellg();

    while (position < end){
        input.seekg(position);

        input.read(bytes, sizeof(int));
        messageSize = *((int *)bytes);

        index.push_back(position);
        position += sizeof(int) + messageSize;
    }
}

protobuf_reader::~protobuf_reader(){
    input.close();
    google::protobuf::ShutdownProtobufLibrary();
}
