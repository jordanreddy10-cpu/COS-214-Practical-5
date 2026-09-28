#include <iostream>
#include "Broadcaster.h"
#include "CampusSecurity.h"
#include "Staff.h"
#include "Medical.h"
#include "LegacyRadio.h"
#include "Adapter.h"
#include "EmergencyFacade.h"
#include "IncidentState.h"
#include "Strategy.h"

int main() {

    Broadcaster* mediator = new Broadcaster();
    LegacyRadio* radio = new LegacyRadio();
    Adapter* adapter = new Adapter(radio);

    CampusSecurity* security = new CampusSecurity(mediator, "Security1");
    Staff* staff = new Staff(mediator, "staff1");
    Medical* medical = new Medical(mediator, "Med1");
    
    //connect adapter to medical colleague
    medical->setCommunicator(adapter);
    mediator->addColleague(security);
    mediator->addColleague(staff);
    mediator->addColleague(medical);

    //setup facade
    EmergencyFacade facade(mediator, security, staff, medical);

    std::cout << "\nScenario 1\n";
    std::cout << "Using: Facade, Mediator, Command, Strategy, Adapter \n";
    facade.declareLockdown("Science Building");
    facade.standDown("Science Building");

    std::cout << "\nScenario 2\n";
    std::cout << "Using: Mediator, Command, Strategy, State \n";
    mediator->setLocation("Library 2nd Floor");
    mediator->setState(new ReportedState());
    mediator->setStrategy(new MedStrategy());
    mediator->executeResponse();
    mediator->setState(new DispatchedState());
    mediator->setState(new ResolvedState());

    delete medical;
    delete staff;
    delete security;
    delete adapter;
    delete radio;
    delete mediator; 

    return 0;
}