/*
 *
 *    Copyright (c) 2020-2021 Project CHIP Authors
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

/**
 *    @file
 *          Provides an generic implementation of ConnectivityManager features
 *          for use on platforms that support WiFi.
 */

#pragma once

#include <lib/support/logging/CHIPLogging.h>
#include <platform/ConnectivityManager.h>
#include <platform/internal/DeviceNetworkInfo.h>

namespace chip {
namespace DeviceLayer {
namespace Internal {

/**
 * Provides a generic implementation of WiFi-specific ConnectivityManager features for
 * platforms that don't support WiFi.
 *
 * This class is intended to be inherited (directly or indirectly) by the ConnectivityManagerImpl
 * class, which also appears as the template's ImplClass parameter.
 *
 * The members of this class are all inlined methods that do nothing, and return static return
 * values.  This allows the compiler to optimize away dead code without the use of \#ifdef's.
 * For example:
 *
 * ```
 * if (ConnectivityMgr().GetWiFiStationMode() != ConnectivityManager::kWiFiStationMode_NotSupported)
 * {
 *     // ... do something on devices that support WiFi ...
 * }
 * ```
 */
template <class ImplClass>
class GenericConnectivityManagerImpl_WiFi
{
public:
    // ===== Methods that implement the ConnectivityManager abstract interface.

    ConnectivityManager::WiFiStationMode _GetWiFiStationMode();
    CHIP_ERROR _SetWiFiStationMode(ConnectivityManager::WiFiStationMode val);
    bool _IsWiFiStationEnabled();
    bool _IsWiFiStationApplicationControlled();
    uint32_t _GetWiFiStationReconnectIntervalMS();
    CHIP_ERROR _SetWiFiStationReconnectIntervalMS(uint32_t val);
    bool _IsWiFiStationProvisioned();
    void _ClearWiFiStationProvision();
    ConnectivityManager::WiFiAPMode _GetWiFiAPMode();
    CHIP_ERROR _SetWiFiAPMode(ConnectivityManager::WiFiAPMode val);
    bool _IsWiFiAPActive();
    bool _IsWiFiAPApplicationControlled();
    void _DemandStartWiFiAP();
    void _StopOnDemandWiFiAP();
    void _MaintainOnDemandWiFiAP();
    uint32_t _GetWiFiAPIdleTimeoutMS();
    void _SetWiFiAPIdleTimeoutMS(uint32_t val);
    CHIP_ERROR _GetAndLogWifiStatsCounters();
    CHIP_ERROR _GetWiFiSecurityType(uint8_t & securityType);
    CHIP_ERROR _GetWiFiVersion(uint8_t & wiFiVersion);
    CHIP_ERROR _GetWiFiChannelNumber(uint16_t & channelNumber);
    CHIP_ERROR _GetWiFiRssi(int8_t & rssi);
    CHIP_ERROR _GetWiFiBeaconLostCount(uint32_t & beaconLostCount);
    CHIP_ERROR _GetWiFiBeaconRxCount(uint32_t & beaconRxCount);
    CHIP_ERROR _GetWiFiPacketMulticastRxCount(uint32_t & packetMulticastRxCount);
    CHIP_ERROR _GetWiFiPacketMulticastTxCount(uint32_t & packetMulticastTxCount);
    CHIP_ERROR _GetWiFiPacketUnicastRxCount(uint32_t & packetUnicastRxCount);
    CHIP_ERROR _GetWiFiPacketUnicastTxCount(uint32_t & packetUnicastTxCount);
    CHIP_ERROR _GetWiFiCurrentMaxRate(uint64_t & currentMaxRate);
    CHIP_ERROR _GetWiFiOverrunCount(uint64_t & overrunCount);
    CHIP_ERROR _ResetWiFiNetworkDiagnosticsCounts();
    bool _CanStartWiFiScan();
    void _OnWiFiScanDone();
    void _OnWiFiStationProvisionChange();
    static const char * _WiFiStationModeToStr(ConnectivityManager::WiFiStationMode mode);
    static const char * _WiFiAPModeToStr(ConnectivityManager::WiFiAPMode mode);
    static const char * _WiFiStationStateToStr(ConnectivityManager::WiFiStationState state);
    static const char * _WiFiAPStateToStr(ConnectivityManager::WiFiAPState state);

protected:
    enum class ConnectivityFlags : uint16_t
    {
        kHaveIPv4InternetConnectivity = 0x0001,
        kHaveIPv6InternetConnectivity = 0x0002,
        kAwaitingConnectivity         = 0x0010,
    };

private:
    ImplClass * Impl() { return static_cast<ImplClass *>(this); }
};

template <class ImplClass>
inline uint32_t GenericConnectivityManagerImpl_WiFi<ImplClass>::_GetWiFiStationReconnectIntervalMS()
{
    return 0;
}

template <class ImplClass>
inline CHIP_ERROR GenericConnectivityManagerImpl_WiFi<ImplClass>::_SetWiFiStationReconnectIntervalMS(uint32_t val)
{
    return CHIP_ERROR_UNSUPPORTED_CHIP_FEATURE;
}

template <class ImplClass>
inline bool GenericConnectivityManagerImpl_WiFi<ImplClass>::_IsWiFiStationProvisioned()
{
    return false;
}

template <class ImplClass>
inline void GenericConnectivityManagerImpl_WiFi<ImplClass>::_ClearWiFiStationProvision()
{}

template <class ImplClass>
inline ConnectivityManager::WiFiAPMode GenericConnectivityManagerImpl_WiFi<ImplClass>::_GetWiFiAPMode()
{
    return ConnectivityManager::kWiFiAPMode_NotSupported;
}

template <class ImplClass>
inline CHIP_ERROR GenericConnectivityManagerImpl_WiFi<ImplClass>::_SetWiFiAPMode(ConnectivityManager::WiFiAPMode val)
{
    return CHIP_ERROR_UNSUPPORTED_CHIP_FEATURE;
}

template <class ImplClass>
inline bool GenericConnectivityManagerImpl_WiFi<ImplClass>::_IsWiFiAPActive()
{
    return false;
}

template <class ImplClass>
inline bool GenericConnectivityManagerImpl_WiFi<ImplClass>::_IsWiFiAPApplicationControlled()
{
    return false;
}

template <class ImplClass>
inline void GenericConnectivityManagerImpl_WiFi<ImplClass>::_DemandStartWiFiAP()
{}

template <class ImplClass>
inline void GenericConnectivityManagerImpl_WiFi<ImplClass>::_StopOnDemandWiFiAP()
{}

template <class ImplClass>
inline void GenericConnectivityManagerImpl_WiFi<ImplClass>::_MaintainOnDemandWiFiAP()
{}

template <class ImplClass>
inline uint32_t GenericConnectivityManagerImpl_WiFi<ImplClass>::_GetWiFiAPIdleTimeoutMS()
{
    return 0;
}

template <class ImplClass>
inline void GenericConnectivityManagerImpl_WiFi<ImplClass>::_SetWiFiAPIdleTimeoutMS(uint32_t val)
{}

template <class ImplClass>
inline CHIP_ERROR GenericConnectivityManagerImpl_WiFi<ImplClass>::_GetAndLogWifiStatsCounters()
{
    return CHIP_ERROR_UNSUPPORTED_CHIP_FEATURE;
}

template <class ImplClass>
inline bool GenericConnectivityManagerImpl_WiFi<ImplClass>::_CanStartWiFiScan()
{
    return false;
}

template <class ImplClass>
inline void GenericConnectivityManagerImpl_WiFi<ImplClass>::_OnWiFiScanDone()
{}

template <class ImplClass>
inline void GenericConnectivityManagerImpl_WiFi<ImplClass>::_OnWiFiStationProvisionChange()
{}

template <class ImplClass>
inline CHIP_ERROR GenericConnectivityManagerImpl_WiFi<ImplClass>::_GetWiFiSecurityType(uint8_t & securityType)
{
    return CHIP_ERROR_UNSUPPORTED_CHIP_FEATURE;
}

template <class ImplClass>
inline CHIP_ERROR GenericConnectivityManagerImpl_WiFi<ImplClass>::_GetWiFiVersion(uint8_t & wiFiVersion)
{
    return CHIP_ERROR_UNSUPPORTED_CHIP_FEATURE;
}

template <class ImplClass>
inline CHIP_ERROR GenericConnectivityManagerImpl_WiFi<ImplClass>::_GetWiFiChannelNumber(uint16_t & channelNumber)
{
    return CHIP_ERROR_UNSUPPORTED_CHIP_FEATURE;
}

template <class ImplClass>
inline CHIP_ERROR GenericConnectivityManagerImpl_WiFi<ImplClass>::_GetWiFiRssi(int8_t & rssi)
{
    return CHIP_ERROR_UNSUPPORTED_CHIP_FEATURE;
}

template <class ImplClass>
inline CHIP_ERROR GenericConnectivityManagerImpl_WiFi<ImplClass>::_GetWiFiBeaconLostCount(uint32_t & beaconLostCount)
{
    return CHIP_ERROR_UNSUPPORTED_CHIP_FEATURE;
}

template <class ImplClass>
inline CHIP_ERROR GenericConnectivityManagerImpl_WiFi<ImplClass>::_GetWiFiBeaconRxCount(uint32_t & beaconRxCount)
{
    return CHIP_ERROR_UNSUPPORTED_CHIP_FEATURE;
}

template <class ImplClass>
inline CHIP_ERROR GenericConnectivityManagerImpl_WiFi<ImplClass>::_GetWiFiPacketMulticastRxCount(uint32_t & packetMulticastRxCount)
{
    return CHIP_ERROR_UNSUPPORTED_CHIP_FEATURE;
}

template <class ImplClass>
inline CHIP_ERROR GenericConnectivityManagerImpl_WiFi<ImplClass>::_GetWiFiPacketMulticastTxCount(uint32_t & packetMulticastTxCount)
{
    return CHIP_ERROR_UNSUPPORTED_CHIP_FEATURE;
}

template <class ImplClass>
inline CHIP_ERROR GenericConnectivityManagerImpl_WiFi<ImplClass>::_GetWiFiPacketUnicastRxCount(uint32_t & packetUnicastRxCount)
{
    return CHIP_ERROR_UNSUPPORTED_CHIP_FEATURE;
}

template <class ImplClass>
inline CHIP_ERROR GenericConnectivityManagerImpl_WiFi<ImplClass>::_GetWiFiPacketUnicastTxCount(uint32_t & packetUnicastTxCount)
{
    return CHIP_ERROR_UNSUPPORTED_CHIP_FEATURE;
}

template <class ImplClass>
inline CHIP_ERROR GenericConnectivityManagerImpl_WiFi<ImplClass>::_GetWiFiCurrentMaxRate(uint64_t & currentMaxRate)
{
    return CHIP_ERROR_UNSUPPORTED_CHIP_FEATURE;
}

template <class ImplClass>
inline CHIP_ERROR GenericConnectivityManagerImpl_WiFi<ImplClass>::_GetWiFiOverrunCount(uint64_t & overrunCount)
{
    return CHIP_ERROR_UNSUPPORTED_CHIP_FEATURE;
}

template <class ImplClass>
inline CHIP_ERROR GenericConnectivityManagerImpl_WiFi<ImplClass>::_ResetWiFiNetworkDiagnosticsCounts()
{
    return CHIP_ERROR_UNSUPPORTED_CHIP_FEATURE;
}

} // namespace Internal
} // namespace DeviceLayer
} // namespace chip
