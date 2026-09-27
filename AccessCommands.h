// COMMAND - Access branch: Access (abstract), Lock, Unlock, Restrict.
#ifndef ACCESSCOMMANDS_H
#define ACCESSCOMMANDS_H
#include <string>
#include "Command.h"

class Colleague;

class Access : public Command {
protected:
    Access(Colleague* receiver, const std::string& area);
    Colleague*  receiver;   // NOT owned
    std::string area;
};

class Lock : public Access {
public:
    Lock(Colleague* receiver, const std::string& area);
    void execute();
};
class Unlock : public Access {
public:
    Unlock(Colleague* receiver, const std::string& area);
    void execute();
};
class Restrict : public Access {
public:
    Restrict(Colleague* receiver, const std::string& area);
    void execute();
};
#endif
