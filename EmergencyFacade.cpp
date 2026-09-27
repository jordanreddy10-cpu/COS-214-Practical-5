// [Lwandiso] FACADE - implementation.
#include "EmergencyFacade.h"
#include "Broadcaster.h"
#include "CampusSecurity.h"
#include "Staff.h"
#include "Medical.h"
#include "OperationalCommands.h"
#include "AccessCommands.h"
#include <iostream>
#include <stdexcept>

EmergencyFacade::EmergencyFacade(Broadcaster* mediator, CampusSecurity* security,Staff* facilities, Medical* medical)
    :mediator(mediator), security(security), facilities(facilities), medical(medical){
    if (!mediator || !security || !facilities || !medical){
        throw std::invalid_argument("EmergencyFacade needs a mediator and all three colleagues");
    }
}

void EmergencyFacade::declareLockdown(const std::string& location) {
    
    std::cout << "\n=== [Facade] declareLockdown(" << location << ") ===\n";
    mediator->setLocation(location);

    // Subsystem op 1: dispatch security.
    security->setCommand(new Dispatch(security, location));
    security->triggerCommand();

    // Subsystem op 2: lock the area.
    facilities->setCommand(new Lock(facilities, location));
    facilities->triggerCommand();

    // Subsystem op 3: notify medical to stand by.
    medical->setCommand(new Notify(medical, "Lockdown in effect at " + location + " - stand by."));
    medical->triggerCommand();

    // Hook for the Strategy pattern (owned separately) - safe to call
    // even if nothing has been configured on the mediator yet.
    mediator->executeResponse();

    std::cout << "=== [Facade] Lockdown workflow complete. Incident status: "<< mediator->getStatusName() << " ===\n\n";
}
void EmergencyFacade::standDown(const std::string& location) {
    std::cout << "\n=== [Facade] standDown(" << location << ") ===\n";

    facilities->setCommand(new Unlock(facilities, location));
    facilities->triggerCommand();

    security->setCommand(new Notify(security, "Stand down - " + location + " has been reopened."));
    security->triggerCommand();

    medical->setCommand(new Notify(medical, "Stand down - " + location + " has been reopened."));
    medical->triggerCommand();

    std::cout << "=== [Facade] Stand-down workflow complete. Incident status: "<< mediator->getStatusName() << " ===\n\n";
}
