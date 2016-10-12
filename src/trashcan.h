#ifndef TRASHCAN_H
#define TRASHCAN_H

#include <vector>
#include "proto/cpp/messages_robocup_ssl_wrapper.pb.h"

using namespace std;

class TrashItem
{
public:
    void *packet;
    unsigned int numUsers;
    TrashItem(SSL_WrapperPacket *packet, unsigned int numUsers) {
        this->packet = packet;
        this->numUsers = numUsers;
    }
};

class TrashCan
{
public:
    TrashCan();
    void addToTrashCan(SSL_WrapperPacket *packet, unsigned int numUsers);
    bool throwAway(SSL_WrapperPacket *packet);

protected:
    vector<TrashItem> trashItems;
};

#endif // TRASHCAN_H
