#include "Strategy.h"
#include "Broadcaster.h" 
#include "Colleague.h"
#include "AccessCommands.h"
#include "OperationalCommands.h"
#include <iostream>


void MedStrategy::determineResponse(Mediator* context) {
    Broadcaster* hub = dynamic_cast<Broadcaster*>(context);
    
    if (hub != nullptr) {

        std::string location = hub->getLocation();
        std::string trigger = hub->getLastEvent();
        
        std::cout << "[MedStrategy] Medical response triggered by " << trigger 
                  << " at " << location << std::endl;


        Colleague* medTeam = hub->getMedicalTeam();
        

        Command* cmd = new Dispatch(medTeam, location); 

        medTeam->setCommand(cmd);
        medTeam->triggerCommand();
        
        delete cmd;
    }
}

void SecurityStrategy::determineResponse(Mediator* context) {
    Broadcaster* hub = dynamic_cast<Broadcaster*>(context);
    
    if (hub != nullptr) {
        std::string location = hub->getLocation();
        std::string trigger = hub->getLastEvent();
        
        std::cout << "[SecurityStrategy] Analyzing " << trigger << " at " << location << std::endl;

        Colleague* secTeam = hub->getSecurityTeam();
        Colleague* staffTeam = hub->getStaffTeam();

        Command* l_cmd = new Lock(secTeam, location); 
        Command* r_cmd = new Restrict(staffTeam, location);
        
        secTeam->setCommand(l_cmd);
        secTeam->triggerCommand();
        
        staffTeam->setCommand(r_cmd);
        staffTeam->triggerCommand();
        
        delete l_cmd;
        delete r_cmd;
    }
}