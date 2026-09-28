#include "Broadcaster.h"
#include "Colleague.h"
#include "IncidentState.h"
#include "Strategy.h"
#include <algorithm>
#include <iostream>

Broadcaster::Broadcaster()
    : currentState(0), strategy(0), inUpdate(false) {}

Broadcaster::~Broadcaster() {
    delete currentState;
    delete strategy;
    flushRetiredStates();
}

void Broadcaster::addColleague(Colleague* c) {
    if (!c) return;
    if (isRegistered(c)) {
        std::cout << "[Mediator] " << c->getName() << " already registered, ignored\n";
        return;
    }
    colleagues.push_back(c);
    std::cout << "[Mediator] registered " << c->getName() << " (" << c->getRole() << ")\n";
}

const std::vector<Colleague*>& Broadcaster::getColleagues() const { return colleagues; }

bool Broadcaster::isRegistered(Colleague* c) const {
    return std::find(colleagues.begin(), colleagues.end(), c) != colleagues.end();
}

void Broadcaster::notify(Colleague* sender, const std::string& event) {
    if (!sender || !isRegistered(sender)) {
        std::cout << "[Mediator] REJECTED '" << event << "' from an unregistered colleague\n";
        return;
    }
    lastEvent = event;
    std::cout << "[Mediator] " << sender->getName() << " reported " << event
              << " -> relaying to the other colleagues\n";

    // Snapshot
    std::vector<Colleague*> snapshot = colleagues;
    for (size_t i = 0; i < snapshot.size(); ++i)
        if (snapshot[i] != sender)
            snapshot[i]->receive(event, sender);

    // Let the State pattern react to the event 
    if (currentState) {
        inUpdate = true;
        currentState->handleUpdate(this);
        inUpdate = false;
        flushRetiredStates();
    }
}

void Broadcaster::setState(IncidentState* state) {
    if (state == currentState) return;
    if (currentState) {
        if (inUpdate) retiredStates.push_back(currentState);  // its handleUpdate() is still running
        else          delete currentState;
    }
    currentState = state;
    if (currentState)
        std::cout << "[Mediator] incident status -> " << currentState->getStatusName() << "\n";
}

void Broadcaster::flushRetiredStates() {
    for (size_t i = 0; i < retiredStates.size(); ++i) delete retiredStates[i];
    retiredStates.clear();
}

void Broadcaster::setStrategy(ResponseStrategy* s) {
    if (s == strategy) return;
    delete strategy;
    strategy = s;
}

void Broadcaster::executeResponse() {
    if (!strategy) {
        std::cout << "[Mediator] ERROR: no response strategy selected, nothing to execute\n";
        return;
    }
    strategy->determineResponse(this);
}

const std::string& Broadcaster::getLastEvent() const { return lastEvent; }
void Broadcaster::setLocation(const std::string& l) { location = l; }
const std::string& Broadcaster::getLocation() const { return location; }
std::string Broadcaster::getStatusName() const {
    return currentState ? currentState->getStatusName() : "NONE";
}

Colleague* Broadcaster::getSecurityTeam() {
    for (Colleague* c : colleagues) {
        if (c->getRole() == "SECURITY") {
            return c;
        }
    }
    return nullptr;
}

Colleague* Broadcaster::getMedicalTeam() {
    for (Colleague* c : colleagues) {
        if (c->getRole() == "MEDICAL") {
            return c;
        }
    }
    return nullptr;
}

Colleague* Broadcaster::getStaffTeam() {
    for (Colleague* c : colleagues) {
        if (c->getRole() == "FACILITIES") { 
            return c;
        }
    }
    return nullptr;
}
