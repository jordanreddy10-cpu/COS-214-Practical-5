// concrete mediator.
//
// Ownership:
//   * Owns currentState and strategy (deleted in destructor).
//   * Does NOT own the colleagues (aggregation): the application creates and
//     destroys them. Colleagues never call the mediator from their destructor,
//     so destruction order is irrelevant.
#ifndef BROADCASTER_H
#define BROADCASTER_H
#include <string>
#include <vector>
#include "Mediator.h"

class Colleague;
class IncidentState;
class ResponseStrategy;

class Broadcaster : public Mediator {
public:
    Broadcaster();
    ~Broadcaster();
    Broadcaster(const Broadcaster&) = delete;
    Broadcaster& operator=(const Broadcaster&) = delete;

    // Mediator
    void notify(Colleague* colleague, const std::string& event);

    // Colleague registry
    void addColleague(Colleague* c);
    const std::vector<Colleague*>& getColleagues() const;

    // State / Strategy contexts
    void setState(IncidentState* state);
    void setStrategy(ResponseStrategy* strategy);
    void executeResponse();

    // Context data used by State and Strategy
    const std::string& getLastEvent() const;
    void setLocation(const std::string& location);
    const std::string& getLocation() const;
    std::string getStatusName() const;

private:
    bool isRegistered(Colleague* c) const;
    void flushRetiredStates();

    std::vector<Colleague*>     colleagues;
    IncidentState*              currentState;
    ResponseStrategy*           strategy;
    std::vector<IncidentState*> retiredStates;  // states replaced during handleUpdate()
    bool                        inUpdate;
    std::string                 lastEvent;
    std::string                 location;
};
#endif
