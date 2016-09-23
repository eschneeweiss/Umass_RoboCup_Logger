#include "protobuf_writer.h"


protobuf_writer::protobuf_writer(char *fileName)
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    output.open(fileName, ios::out | ios::app | ios::binary );
    if (!output){
        throw "failed to open file";
    }
}

bool protobuf_writer::writeMessage(google::protobuf::Message *message){
    if (message == NULL || !message->IsInitialized()){
        return false;
    }
    unsigned int messageSize = message->ByteSize();
    output.write((char *)&messageSize, sizeof(int));
    message->SerializeToOstream(&output);
    return true;
}

protobuf_writer::~protobuf_writer(){
    output.flush();
    output.close();
    google::protobuf::ShutdownProtobufLibrary();
}

