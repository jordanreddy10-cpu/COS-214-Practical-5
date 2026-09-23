// MEDIATOR colleague / COMMAND receiver (facilities + access control).
#ifndef STAFF_H
#define STAFF_H
#include <map>
#include "Colleague.h"

class Staff : public Colleague {
public:
    Staff(Mediator* m, const std::string& name);
    std::string getRole() const;
    void receive(const std::string& event, Colleague* from);
    void dispatchTo(const std::string& location);
    void lockArea(const std::string& area);
    void unlockArea(const std::string& area);
    void restrictArea(const std::string& area);
    std::string getAreaStatus(const std::string& area) const;
private:
    std::map<std::string, std::string> areas;   // area -> LOCKED / RESTRICTED (absent = OPEN)
};
#endif
