#ifndef STRATEGY_H
#define STRATEGY_H

class Mediator;

class ResponseStrategy 
{
public:
    virtual ~ResponseStrategy() = default;
    virtual void determineResponse(Mediator* context) = 0;
};

class MedStrategy : public ResponseStrategy 
{
public:
    void determineResponse(Mediator* context) override;
};

class SecurityStrategy : public ResponseStrategy 
{
public:
    void determineResponse(Mediator* context) override;
};

#endif