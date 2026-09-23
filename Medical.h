// MEDIATOR colleague / COMMAND receiver.
// Talks to the outside world through a Communicator (non-owning association;
// the application owns the concrete Communicator).
#ifndef MEDICAL_H
#define MEDICAL_H
#include "Colleague.h"

class Communicator;

class Medical : public Colleague {
public:
    Medical(Mediator* m, const std::string& name);
    std::string getRole() const;
    void setCommunicator(Communicator* c);
    void receive(const std::string& event, Colleague* from);
    void dispatchTo(const std::string& location);
    void notifyOf(const std::string& message);
private:
    Communicator* communicator;   // NOT owned
};
#endif
