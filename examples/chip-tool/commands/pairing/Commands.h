/*
 *   Copyright (c) 2020 Project CHIP Authors
 *   All rights reserved.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 */

#pragma once

#include "PairingCommand.h"

class Unpair : public PairingCommand
{
public:
    Unpair() : PairingCommand("unpair", PairingMode::None, PairingNetworkType::None) {}
};

class PairBypass : public PairingCommand
{
public:
    PairBypass() : PairingCommand("bypass", PairingMode::Bypass, PairingNetworkType::None) {}
};

class PairQRCode : public PairingCommand
{
public:
    PairQRCode() : PairingCommand("qrcode", PairingMode::QRCode, PairingNetworkType::None) {}
};

class PairManualCode : public PairingCommand
{
public:
    PairManualCode() : PairingCommand("manualcode", PairingMode::ManualCode, PairingNetworkType::None) {}
};

class PairOnNetwork : public PairingCommand
{
public:
    PairOnNetwork() : PairingCommand("onnetwork", PairingMode::OnNetwork, PairingNetworkType::None) {}
};

class PairOnNetworkShort : public PairingCommand
{
public:
    PairOnNetworkShort() :
        PairingCommand("onnetwork-short", PairingMode::OnNetwork, PairingNetworkType::None, chip::Mdns::DiscoveryFilterType::kShort)
    {}
};

class PairOnNetworkLong : public PairingCommand
{
public:
    PairOnNetworkLong() :
        PairingCommand("onnetwork-long", PairingMode::OnNetwork, PairingNetworkType::None, chip::Mdns::DiscoveryFilterType::kLong)
    {}
};

class PairOnNetworkVendor : public PairingCommand
{
public:
    PairOnNetworkVendor() :
        PairingCommand("onnetwork-vendor", PairingMode::OnNetwork, PairingNetworkType::None,
                       chip::Mdns::DiscoveryFilterType::kVendor)
    {}
};

class PairOnNetworkFabric : public PairingCommand
{
public:
    PairOnNetworkFabric() :
        PairingCommand("onnetwork-fabric", PairingMode::OnNetwork, PairingNetworkType::None,
                       chip::Mdns::DiscoveryFilterType::kCompressedFabricId)
    {}
};

class PairOnNetworkCommissioningMode : public PairingCommand
{
public:
    PairOnNetworkCommissioningMode() :
        PairingCommand("onnetwork-commissioning-mode", PairingMode::OnNetwork, PairingNetworkType::None,
                       chip::Mdns::DiscoveryFilterType::kCommissioningMode)
    {}
};

class PairOnNetworkCommissioner : public PairingCommand
{
public:
    PairOnNetworkCommissioner() :
        PairingCommand("onnetwork-commissioner", PairingMode::OnNetwork, PairingNetworkType::None,
                       chip::Mdns::DiscoveryFilterType::kCommissioner)
    {}
};

class PairOnNetworkDeviceType : public PairingCommand
{
public:
    PairOnNetworkDeviceType() :
        PairingCommand("onnetwork-device-type", PairingMode::OnNetwork, PairingNetworkType::None,
                       chip::Mdns::DiscoveryFilterType::kDeviceType)
    {}
};

class PairOnNetworkInstanceName : public PairingCommand
{
public:
    PairOnNetworkInstanceName() :
        PairingCommand("onnetwork-instance-name", PairingMode::OnNetwork, PairingNetworkType::None,
                       chip::Mdns::DiscoveryFilterType::kInstanceName)
    {}
};

class PairBleWiFi : public PairingCommand
{
public:
    PairBleWiFi() : PairingCommand("ble-wifi", PairingMode::Ble, PairingNetworkType::WiFi) {}
};

class PairBleThread : public PairingCommand
{
public:
    PairBleThread() : PairingCommand("ble-thread", PairingMode::Ble, PairingNetworkType::Thread) {}
};

class PairSoftAP : public PairingCommand
{
public:
    PairSoftAP() : PairingCommand("softap", PairingMode::SoftAP, PairingNetworkType::WiFi) {}
};

class Ethernet : public PairingCommand
{
public:
    Ethernet() : PairingCommand("ethernet", PairingMode::Ethernet, PairingNetworkType::Ethernet) {}
};

class OpenCommissioningWindow : public PairingCommand
{
public:
    OpenCommissioningWindow() :
        PairingCommand("open-commissioning-window", PairingMode::OpenCommissioningWindow, PairingNetworkType::None)
    {}
};

void registerCommandsPairing(Commands & commands)
{
    const char * clusterName = "Pairing";

    commands_list clusterCommands = {
        make_unique<Unpair>(),
        make_unique<PairBypass>(),
        make_unique<PairQRCode>(),
        make_unique<PairManualCode>(),
        make_unique<PairBleWiFi>(),
        make_unique<PairBleThread>(),
        make_unique<PairSoftAP>(),
        make_unique<Ethernet>(),
        make_unique<PairOnNetwork>(),
        make_unique<PairOnNetworkShort>(),
        make_unique<PairOnNetworkLong>(),
        make_unique<PairOnNetworkVendor>(),
        make_unique<PairOnNetworkCommissioningMode>(),
        make_unique<PairOnNetworkCommissioner>(),
        make_unique<PairOnNetworkDeviceType>(),
        make_unique<PairOnNetworkDeviceType>(),
        make_unique<PairOnNetworkInstanceName>(),
        make_unique<OpenCommissioningWindow>(),
    };

    commands.Register(clusterName, clusterCommands);
}
