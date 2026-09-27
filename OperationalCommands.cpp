#include "OperationalCommands.h"
#include "Colleague.h"
#include <iostream>
#include <stdexcept>

Operational::Operational(Colleague* r, const std::string& t) : receiver(r), text(t) {
    if (!r) throw std::invalid_argument("Operational command needs a receiver");
}

Dispatch::Dispatch(Colleague* r, const std::string& location) : Operational(r, location) {}
void Dispatch::execute() {
    std::cout << "  [Dispatch] -> " << receiver->getName() << " : go to " << text << "\n";
    receiver->dispatchTo(text);
}

Notify::Notify(Colleague* r, const std::string& message) : Operational(r, message) {}
void Notify::execute() {
    std::cout << "  [Notify] -> " << receiver->getName() << " : \"" << text << "\"\n";
    receiver->notifyOf(text);
}
