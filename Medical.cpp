#include "Medical.h"
#include "Communicator.h"
#include <iostream>

Medical::Medical(Mediator* m, const std::string& n) : Colleague(m, n), communicator(0) {}
std::string Medical::getRole() const { return "MEDICAL"; }
void Medical::setCommunicator(Communicator* c) { communicator = c; }

void Medical::receive(const std::string& event, Colleague* from) {
    if (event == "SECURITY_DISPATCHED")
        std::cout << "  [" << getName() << "] reacting to " << from->getName()
                  << ": pre-alerting the ambulance crew\n";
    else if (event == "AREA_LOCKED")
        std::cout << "  [" << getName() << "] reacting to " << from->getName()
                  << ": requesting a stretcher-access override\n";
}

void Medical::dispatchTo(const std::string& location) {
    std::cout << "  [" << getName() << "] ambulance crew leaving\n";
    changed("MEDICAL_DISPATCHED");
    std::cout << "  [" << getName() << "] dispatch confirmed for " << location << "\n";
}

void Medical::notifyOf(const std::string& message) {
    if (!communicator) {
        reportFailure("no radio link configured");
        return;
    }
    communicator->sendMessage("[" + getName() + "] " + message);
    changed("NOTICE_SENT");
}
