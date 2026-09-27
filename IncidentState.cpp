// [Lwandiso] STATE - concrete state transition logic.
#include "IncidentState.h"
#include "Broadcaster.h"
#include <iostream>

void ReportedState::handleUpdate(Broadcaster* context) {
    const std::string& event = context->getLastEvent();
    if (event == "SECURITY_DISPATCHED" || event == "MEDICAL_DISPATCHED" ||
        event == "FACILITIES_DISPATCHED") {
        context->setState(new DispatchedState());
    }
}

void DispatchedState::handleUpdate(Broadcaster* context) {
    const std::string& event = context->getLastEvent();
    if (event == "AREA_LOCKED" || event == "AREA_RESTRICTED") {
        context->setState(new InProgressState());
    }
    // Additional dispatches while still Dispatched are legal and simply
    // stay in this state - handled naturally by not matching above.
}

void InProgressState::handleUpdate(Broadcaster* context) {
    const std::string& event = context->getLastEvent();
    if (event == "AREA_UNLOCKED") {
        context->setState(new ResolvedState());
    }
}

void ResolvedState::handleUpdate(Broadcaster* context) {
    const std::string& event = context->getLastEvent();
    std::cout << "  [IncidentState] incident already RESOLVED - ignoring '"<< event << "'\n";
}
