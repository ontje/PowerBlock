/*
 * (c) Copyright 2015  Florian Müller (contact@petrockblock.com)
 * https://github.com/petrockblog/PowerBlock
 *
 * Permission to use, copy, modify and distribute the program in both binary and
 * source form, for non-commercial purposes, is hereby granted without fee,
 * providing that this license information and copyright notice appear with
 * all copies and any derived work.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event shall the authors be held liable for any damages
 * arising from the use of this software.
 *
 * This program is freeware for PERSONAL USE only. Commercial users must
 * seek permission of the copyright holders first. Commercial use includes
 * charging money for the program or software derived from the program.
 *
 * The copyright holders request that bug fixes and improvements to the code
 * should be forwarded to them so everyone can benefit from the modifications
 * in future versions.
 */

#include "PowerBlock.h"
#include <iostream>

PowerBlock::PowerBlock() :
        configuration(new PowerBlockConfiguration())
{
    std::map<PowerBlockConfiguration::ShutdownType_e, PowerSwitch::ShutdownActivated_e> switchMapping;
    switchMapping[PowerBlockConfiguration::SHUTDOWN_ACTIVATED] = PowerSwitch::SHUTDOWN_ACTIVATED;
    switchMapping[PowerBlockConfiguration::SHUTDOWN_DEACTIVATED] = PowerSwitch::SHUTDOWN_DEACTIVATED;

    configuration->initialize();

    powerSwitch = new PowerSwitch(switchMapping[configuration->getShutdownActivation()], configuration->getStatusPin(), configuration->getShutdownPin());
}

PowerBlock::~PowerBlock()
{
    delete powerSwitch;
    delete configuration;
}

void PowerBlock::update()
{
    try
    {
        powerSwitch->update();
    }
    catch (int errno)
    {
        std::cout << "Error while updating the power switch instance. Error number: " << errno << std::endl;
    }
}
