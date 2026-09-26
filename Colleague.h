// MEDIATOR (Colleague) + COMMAND (Invoker AND Receiver).

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

    // ---- Mediator side ----
    void changed(const std::string& event);                       // colleague -> mediator
    virtual void receive(const std::string& event, Colleague* from) = 0;  // mediator -> colleague

    // ---- Command side (Colleague acting as INVOKER) ----
    void setCommand(Command* c);   // takes ownership
    void triggerCommand();

    // ---- Receiver operations (Colleague acting as RECEIVER) ----
    // Defaults call reportFailure(): not every unit can do everything.
    virtual void dispatchTo(const std::string& location) = 0;
    virtual void lockArea(const std::string& area);
    virtual void unlockArea(const std::string& area);
    virtual void restrictArea(const std::string& area);
    virtual void notifyOf(const std::string& message);

protected:
    // A receiver that cannot perform a command reports it here: logs the reason and
    // tells the mediator (event "COMMAND_FAILED"). No exceptions involved.
    void reportFailure(const std::string& why);

    Mediator* mediator;
    Command*  assignedCommand;

private:
    std::string name;
    Command*    pendingCommand;   // set while a command is executing (re-entrancy guard)
    bool        executing;
};
#endif
