//
//  KeyImplementations.cpp
//  AMDRyzenCPUPowerManagement
//
//  Created by trulyspinach on 2/12/20.
//

#include "KeyImplementations.hpp"


SMC_RESULT TempPackage::readAccess() {
    uint16_t *ptr = reinterpret_cast<uint16_t *>(data);
    double temp = provider ? (double)provider->PACKAGE_TEMPERATURE_perPackage[0] : 45.0;
    if (temp <= 0.0 || temp > 125.0) temp = 45.0;
    *ptr = VirtualSMCAPI::encodeSp(type, temp);

    return SmcSuccess;
}

SMC_RESULT TempCore::readAccess() {
    uint16_t *ptr = reinterpret_cast<uint16_t *>(data);
    double temp = provider ? (double)provider->PACKAGE_TEMPERATURE_perPackage[0] : 45.0;
    if (temp <= 0.0 || temp > 125.0) temp = 45.0;
    *ptr = VirtualSMCAPI::encodeSp(type, temp);

    return SmcSuccess;
}

SMC_RESULT EnergyPackage::readAccess(){
    double energy = provider ? provider->uniPackageEnergy : 0.0;
    if (energy < 0.0 || energy > 500.0) energy = 0.0;
    if (type == SmcKeyTypeFloat)
        *reinterpret_cast<uint32_t *>(data) = VirtualSMCAPI::encodeFlt(energy);
    else
        *reinterpret_cast<uint16_t *>(data) = VirtualSMCAPI::encodeSp(type, energy);
    
    return SmcSuccess;
}
