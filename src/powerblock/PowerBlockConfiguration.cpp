/*
 * (c) Copyright 2015  Florian Müller (contact@petrockblock.com)
 * https://github.com/petrockblog/PowerBlockService
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

#include <iostream>
#include <fstream>

#include "PowerBlockConfiguration.h"

#include <stdint.h>

PowerBlockConfiguration::PowerBlockConfiguration() :
        doShutdown(SHUTDOWN_ACTIVATED),
        statusPin(17),
        shutdownPin(18)
{ }

PowerBlockConfiguration::~PowerBlockConfiguration()
{ }

void PowerBlockConfiguration::initialize()
{
    try
    {
        Json::Value root;
        Json::Reader reader;

        std::ifstream t("/etc/powerblockconfig.cfg");
        std::string config_doc((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

        bool parsingSuccessful = reader.parse(config_doc, root);
        if (!parsingSuccessful)
        {
            std::cout << "[PowerBlock] Failed to parse configuration\n" << reader.getFormattedErrorMessages();
            return;
        }

        bool configboolean = root["powerswitch"]["activated"].asBool();
        if (configboolean)
        {
            doShutdown = SHUTDOWN_ACTIVATED;
            std::cout << "[PowerBlock] Shutdown is ACTIVATED" << std::endl;
        }
        else
        {
            doShutdown = SHUTDOWN_DEACTIVATED;
            std::cout << "[PowerBlock] Shutdown is DEACTIVATED" << std::endl;
        }

        if (root["statuspin"].isNull()) {
            statusPin = 17;
        } else {
            statusPin = (uint16_t) root["statuspin"].asInt();
        }

        if (root["shutdownpin"].isNull()) {
            shutdownPin = 18;
        } else {
            shutdownPin = (uint16_t) root["shutdownpin"].asInt();
        }

        std::cout << "[PowerBlock] Shutdown Pin is " << shutdownPin << std::endl;
        std::cout << "[PowerBlock] Status Pin is " << statusPin << std::endl;
    }
    catch (int errno)
    {
        std::cout << "[PowerBlock] Error while initializing "
                "PowerBlockConfiguration instance. Error number: " << errno << std::endl;
    }
}

PowerBlockConfiguration::ShutdownType_e PowerBlockConfiguration::getShutdownActivation() const
{
    return doShutdown;
}

uint16_t PowerBlockConfiguration::getShutdownPin() const
{
    return shutdownPin;
}

uint16_t PowerBlockConfiguration::getStatusPin() const
{
    return statusPin;
}
