// MEDIATOR (Colleague) + COMMAND (Invoker, Receiver).

//   A Colleague OWNS its assignedCommand (setCommand takes ownership).
//   A Colleague does NOT own the Mediator (non-owning pointer).

#ifndef COLLEAGUE_H
#define COLLEAGUE_H
#include <string>
#include "Mediator.h"

class Command;

class Colleague {
public:
    Colleague(Mediator* mediator, const std::string& name);
    virtual ~Colleague();
    Colleague(const Colleague&) = delete;
    Colleague& operator=(const Colleague&) = delete;

    const std::string& getName() const;
    virtual std::string getRole() const = 0;

    // Mediator 
    void changed(const std::string& event);                       // colleague to mediator
    virtual void receive(const std::string& event, Colleague* from) = 0;  // mediator to colleague

    // Command
    void setCommand(Command* c);   // takes ownership
    void triggerCommand();

    // Receiver
    virtual void dispatchTo(const std::string& location) = 0;
    virtual void lockArea(const std::string& area);
    virtual void unlockArea(const std::string& area);
    virtual void restrictArea(const std::string& area);
    virtual void notifyOf(const std::string& message);

protected:
    // A receiver that cannot perform a command reports it here
    void reportFailure(const std::string& why);

    Mediator* mediator;
    Command*  assignedCommand;

private:
    std::string name;
    Command*    pendingCommand;   // set while a command is executing 
    bool        executing;
};
#endif
