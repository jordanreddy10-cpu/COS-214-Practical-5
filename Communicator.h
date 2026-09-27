#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

class Communicator {
public:
    virtual ~Communicator() = default;
    virtual void sendMessage(const std::string& message) = 0;
};

#endif