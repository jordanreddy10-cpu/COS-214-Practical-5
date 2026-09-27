#include "LegacyRadio.h"
#include <iostream>

void LegacyRadio::transmitAnalogSignal(int frequency, const char* data) 
{
    std::cout << "[Legacy Radio] freq: " << frequency << "msg: " << data << std::endl;
}