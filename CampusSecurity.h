//  MEDIATOR colleague / COMMAND receiver.
#ifndef CAMPUSSECURITY_H
#define CAMPUSSECURITY_H
#include "Colleague.h"

class CampusSecurity : public Colleague {
public:
    CampusSecurity(Mediator* m, const std::string& name);
    std::string getRole() const;
    void receive(const std::string& event, Colleague* from);
    void dispatchTo(const std::string& location);
};
#endif
