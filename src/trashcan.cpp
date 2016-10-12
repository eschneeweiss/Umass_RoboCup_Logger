#include "trashcan.h"
//temp
#include <iostream>

TrashCan::TrashCan() {

}

void TrashCan::addToTrashCan(SSL_WrapperPacket *packet, unsigned int numUsers){
    trashItems.push_back(TrashItem(packet, numUsers));
    //std::cout<<"trashItems size: "<<trashItems.size()<<std::endl;
}

bool TrashCan::throwAway(SSL_WrapperPacket *packet){
    for (unsigned int i = 0; i < trashItems.size(); i++) {
        if (trashItems[i].packet == packet) {
            if (--(trashItems[i].numUsers) < 1) {
                delete packet;
                trashItems.erase(trashItems.begin() + i);
            }
            //std::cout<<"trashItems size: "<<trashItems.size()<<std::endl;
            return true;
        }
    }
    return false;
}
