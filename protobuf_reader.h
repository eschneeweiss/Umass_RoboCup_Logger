#ifndef PROTOBUF_READER_H
#define PROTOBUF_READER_H
#include <google/protobuf/message.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class protobuf_reader
{
public:
    explicit protobuf_reader(char *fileName);
    ~protobuf_reader();

    bool readMessage(unsigned int readIndex, google::protobuf::Message *message);
    unsigned int getIndexSize();

private:
    void createIndex();

    ifstream input;
    vector<unsigned int> index;
};

#endif // PROTOBUF_READER_H
