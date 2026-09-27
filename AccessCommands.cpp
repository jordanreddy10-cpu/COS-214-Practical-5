#include "AccessCommands.h"
#include "Colleague.h"
#include <iostream>
#include <stdexcept>

Access::Access(Colleague* r, const std::string& a) : receiver(r), area(a) {
    if (!r) throw std::invalid_argument("Access command needs a receiver");
}

Lock::Lock(Colleague* r, const std::string& a) : Access(r, a) {}
void Lock::execute() {
    std::cout << "  [Lock] -> " << receiver->getName() << " : lock " << area << "\n";
    receiver->lockArea(area);
}

Unlock::Unlock(Colleague* r, const std::string& a) : Access(r, a) {}
void Unlock::execute() {
    std::cout << "  [Unlock] -> " << receiver->getName() << " : unlock " << area << "\n";
    receiver->unlockArea(area);
}

Restrict::Restrict(Colleague* r, const std::string& a) : Access(r, a) {}
void Restrict::execute() {
    std::cout << "  [Restrict] -> " << receiver->getName() << " : restrict " << area << "\n";
    receiver->restrictArea(area);
}
