#ifndef PROTOBUF_WRITER_H
#define PROTOBUF_WRITER_H
#include <google/protobuf/message.h>
#include <iostream>
#include <fstream>

using namespace std;

class protobuf_writer
{
public:
    explicit protobuf_writer(char *fileName);
    ~protobuf_writer();

    bool writeMessage(google::protobuf::Message *message);

private:

    ofstream output; 
};

#endif // PROTOBUF_WRITER_H
