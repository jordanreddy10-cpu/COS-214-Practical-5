#include "Colleague.h"
#include "Command.h"
#include <iostream>

Colleague::Colleague(Mediator* m, const std::string& n)
    : mediator(m), assignedCommand(0), name(n), pendingCommand(0), executing(false) {}

Colleague::~Colleague() {
    delete assignedCommand;
    delete pendingCommand;
}

const std::string& Colleague::getName() const { return name; }

void Colleague::changed(const std::string& event) {
    if (!mediator) {
        std::cout << "  [" << name << "] ERROR: no mediator set, cannot report '" << event << "'\n";
        return;
    }
    mediator->notify(this, event);
}

void Colleague::setCommand(Command* c) {
    if (c == assignedCommand) return;
#ifndef CAMPUSGUARD_REENTRANCY_BUG
    if (executing) {
        delete pendingCommand;
        pendingCommand = c;
        return;
    }
#endif
    delete assignedCommand;
    assignedCommand = c;
}

void Colleague::triggerCommand() {
    if (!assignedCommand) {
        std::cout << "  [" << name << "] ERROR: no command assigned, nothing to trigger\n";
        return;
    }
    if (executing) {
        std::cout << "  [" << name << "] ERROR: already executing a command, ignoring trigger\n";
        return;
    }
    executing = true;
    assignedCommand->execute();
    executing = false;

    if (pendingCommand) {                
        delete assignedCommand;
        assignedCommand = pendingCommand;
        pendingCommand = 0;
    }
}

void Colleague::reportFailure(const std::string& why) {
    std::cout << "  [" << name << "] COMMAND FAILED: " << why << "\n";
    changed("COMMAND_FAILED");
}

void Colleague::lockArea(const std::string&) {
    reportFailure(getRole() + " units cannot control building access");
}
void Colleague::unlockArea(const std::string&) {
    reportFailure(getRole() + " units cannot control building access");
}
void Colleague::restrictArea(const std::string&) {
    reportFailure(getRole() + " units cannot control building access");
}
void Colleague::notifyOf(const std::string& message) {
    std::cout << "  [" << name << "] notice received: " << message << "\n";
    changed("NOTICE_SENT");
}
