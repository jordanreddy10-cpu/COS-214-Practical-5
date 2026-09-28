#include "LegacyRadio.h"
#include <iostream>

void LegacyRadio::transmitAnalogSignal(int frequency, const char* data) 
{
    std::cout << "older radio has freq: " << frequency << "msg: " << data << std::endl;
}