#ifndef INCIDENTSTATE_H
#define INCIDENTSTATE_H
#include <string>

class Broadcaster;

class IncidentState {
public:
    virtual ~IncidentState() {}
    virtual void handleUpdate(Broadcaster* context) = 0;
    virtual std::string getStatusName() const = 0;
};

class ReportedState : public IncidentState {
public:
    void handleUpdate(Broadcaster* context);
    std::string getStatusName() const { return "REPORTED"; }
};

class DispatchedState : public IncidentState {
public:
    void handleUpdate(Broadcaster* context);
    std::string getStatusName() const { return "DISPATCHED"; }
};

class InProgressState : public IncidentState {
public:
    void handleUpdate(Broadcaster* context);
    std::string getStatusName() const { return "IN_PROGRESS"; }
};

class ResolvedState : public IncidentState {
public:
    void handleUpdate(Broadcaster* context);
    std::string getStatusName() const { return "RESOLVED"; }
};

#endif
