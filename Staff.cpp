#include "Staff.h"
#include <iostream>

Staff::Staff(Mediator* m, const std::string& n) : Colleague(m, n) {}
std::string Staff::getRole() const { return "FACILITIES"; }

void Staff::receive(const std::string& event, Colleague* from) {
    if (event == "SECURITY_DISPATCHED" || event == "MEDICAL_DISPATCHED")
        std::cout << "  [" << getName() << "] reacting to " << from->getName()
                  << ": standing by to secure the area\n";
}

void Staff::dispatchTo(const std::string& location) {
    std::cout << "  [" << getName() << "] facilities team leaving\n";
    changed("FACILITIES_DISPATCHED");
    std::cout << "  [" << getName() << "] dispatch confirmed for " << location << "\n";
}

std::string Staff::getAreaStatus(const std::string& area) const {
    std::map<std::string, std::string>::const_iterator it = areas.find(area);
    return it == areas.end() ? "OPEN" : it->second;
}

void Staff::lockArea(const std::string& area) {
    if (getAreaStatus(area) == "LOCKED") {
        reportFailure(area + " is already locked");
        return;
    }
    areas[area] = "LOCKED";
    std::cout << "  [" << getName() << "] " << area << " is now LOCKED\n";
    changed("AREA_LOCKED");
}

void Staff::unlockArea(const std::string& area) {
    if (getAreaStatus(area) == "OPEN") {
        reportFailure(area + " is already open, nothing to unlock");
        return;
    }
    areas.erase(area);
    std::cout << "  [" << getName() << "] " << area << " is now OPEN\n";
    changed("AREA_UNLOCKED");
}

void Staff::restrictArea(const std::string& area) {
    if (getAreaStatus(area) == "RESTRICTED") {
        reportFailure(area + " is already restricted");
        return;
    }
    areas[area] = "RESTRICTED";
    std::cout << "  [" << getName() << "] " << area << " is now RESTRICTED (authorised only)\n";
    changed("AREA_RESTRICTED");
}
