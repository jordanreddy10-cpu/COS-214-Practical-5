#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <string>

class Communicator {
public:
    virtual ~Communicator() = default;
    virtual void sendMessage(const std::string& message) = 0;
};

#endif