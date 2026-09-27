// abstract mediator.
#ifndef MEDIATOR_H
#define MEDIATOR_H
#include <string>

class Colleague;

class Mediator {
public:
    virtual ~Mediator() {}
    virtual void notify(Colleague* colleague, const std::string& event) = 0;
};
#endif
