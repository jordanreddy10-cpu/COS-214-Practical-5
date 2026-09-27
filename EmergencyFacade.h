#ifndef EMERGENCYFACADE_H
#define EMERGENCYFACADE_H
#include <string>

class Broadcaster;
class CampusSecurity;
class Staff;
class Medical;

class EmergencyFacade {
public:
    EmergencyFacade(Broadcaster* mediator, CampusSecurity* security, Staff* facilities, Medical* medical);
    void declareLockdown(const std::string& location);
    void standDown(const std::string& location);

private:
    Broadcaster*    mediator;    // NOT owned
    CampusSecurity* security;    // NOT owned
    Staff*          facilities;  // NOT owned
    Medical*        medical;     // NOT owned
};
#endif
