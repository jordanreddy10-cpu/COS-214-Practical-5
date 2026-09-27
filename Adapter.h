#ifndef ADAPTER_H
#define ADAPTER_H

#include "Communicator.h"
#include "LegacyRadio.h"
#include <string>

class Adapter : public Communicator {
private:
    LegacyRadio* oldRadio;
public:
    Adapter(LegacyRadio* radio) : oldRadio(radio) {}
    void sendMessage(const std::string& message) override;
};

#endif