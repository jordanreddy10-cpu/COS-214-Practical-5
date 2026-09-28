#include "Adapter.h"
#include <iostream>

Adapter::Adapter(LegacyRadio* radio) : oldRadio(radio) {}

void Adapter::sendMessage(const std::string& message) {
    std::cout << "sending message through adapter" << std::endl;
    const char* data = message.c_str();
    //give a standard value so that we can use an legacy system and meet its requirements
    int frequency = 155; 

    oldRadio->transmitAnalogSignal(frequency, data);
}