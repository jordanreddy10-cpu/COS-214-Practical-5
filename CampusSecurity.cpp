#include "CampusSecurity.h"
#include <iostream>

CampusSecurity::CampusSecurity(Mediator* m, const std::string& n) : Colleague(m, n) {}
std::string CampusSecurity::getRole() const { return "SECURITY"; }

void CampusSecurity::receive(const std::string& event, Colleague* from) {
    if (event == "MEDICAL_DISPATCHED")
        std::cout << "  [" << getName() << "] reacting to " << from->getName()
                  << ": clearing a route for the medics\n";
    else if (event == "AREA_LOCKED" || event == "AREA_RESTRICTED")
        std::cout << "  [" << getName() << "] reacting to " << from->getName()
                  << ": posting a guard at the perimeter\n";
}

void CampusSecurity::dispatchTo(const std::string& location) {
    std::cout << "  [" << getName() << "] patrol unit leaving base\n";
    changed("SECURITY_DISPATCHED");
    std::cout << "  [" << getName() << "] dispatch confirmed for " << location << "\n";
}
