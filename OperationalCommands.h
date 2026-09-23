//  COMMAND - Operational branch
#ifndef OPERATIONALCOMMANDS_H
#define OPERATIONALCOMMANDS_H
#include <string>
#include "Command.h"

class Colleague;

class Operational : public Command {
protected:
    Operational(Colleague* receiver, const std::string& text);
    Colleague*  receiver;   // NOT owned
    std::string text;       // location or message
};

class Dispatch : public Operational {
public:
    Dispatch(Colleague* receiver, const std::string& location);
    void execute();
};

class Notify : public Operational {
public:
    Notify(Colleague* receiver, const std::string& message);
    void execute();
};
#endif
