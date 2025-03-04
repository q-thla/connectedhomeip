/*
 *
 *    Copyright (c) 2020 Project CHIP Authors
 *    Copyright (c) 2018 Nest Labs, Inc.
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
 *          Defines the public interface for the Device Layer ConnectivityManager object.
 */

#pragma once
#include <memory>

#include <app/AttributeAccessInterface.h>
#include <lib/support/CodeUtils.h>
#include <platform/CHIPDeviceBuildConfig.h>
#include <platform/CHIPDeviceEvent.h>

#include <app/util/basic-types.h>

namespace chip {

namespace Ble {
class BleLayer;
class BLEEndPoint;
} // namespace Ble

namespace DeviceLayer {

namespace Internal {
template <class>
class GenericPlatformManagerImpl;
template <class>
class GenericPlatformManagerImpl_FreeRTOS;
template <class>
class GenericPlatformManagerImpl_POSIX;
} // namespace Internal

class ConnectivityManagerImpl;

/**
 * Provides control of network connectivity for a chip device.
 */
class ConnectivityManager
{
    using ImplClass = ::chip::DeviceLayer::ConnectivityManagerImpl;

public:
    // ===== Members that define the public interface of the ConnectivityManager

    enum WiFiStationMode
    {
        kWiFiStationMode_NotSupported          = 0,
        kWiFiStationMode_ApplicationControlled = 1,
        kWiFiStationMode_Disabled              = 2,
        kWiFiStationMode_Enabled               = 3,
    };

    enum WiFiAPMode
    {
        kWiFiAPMode_NotSupported                = 0,
        kWiFiAPMode_ApplicationControlled       = 1,
        kWiFiAPMode_Disabled                    = 2,
        kWiFiAPMode_Enabled                     = 3,
        kWiFiAPMode_OnDemand                    = 4,
        kWiFiAPMode_OnDemand_NoStationProvision = 5,
    };

    enum ThreadMode
    {
        kThreadMode_NotSupported          = 0,
        kThreadMode_ApplicationControlled = 1,
        kThreadMode_Disabled              = 2,
        kThreadMode_Enabled               = 3,
    };

    enum WiFiStationState
    {
        kWiFiStationState_NotConnected,
        kWiFiStationState_Connecting,
        kWiFiStationState_Connecting_Succeeded,
        kWiFiStationState_Connecting_Failed,
        kWiFiStationState_Connected,
        kWiFiStationState_Disconnecting,
    };

    enum WiFiAPState
    {
        kWiFiAPState_NotActive,
        kWiFiAPState_Activating,
        kWiFiAPState_Active,
        kWiFiAPState_Deactivating,
    };

    enum CHIPoBLEServiceMode
    {
        kCHIPoBLEServiceMode_NotSupported = 0,
        kCHIPoBLEServiceMode_Enabled      = 1,
        kCHIPoBLEServiceMode_Disabled     = 2,
    };

    enum ThreadDeviceType
    {
        kThreadDeviceType_NotSupported     = 0,
        kThreadDeviceType_Router           = 1,
        kThreadDeviceType_FullEndDevice    = 2,
        kThreadDeviceType_MinimalEndDevice = 3,
        kThreadDeviceType_SleepyEndDevice  = 4,
    };

    enum BLEAdvertisingMode
    {
        kFastAdvertising = 0,
        kSlowAdvertising = 1,
    };

    struct ThreadPollingConfig;

    // WiFi station methods
    WiFiStationMode GetWiFiStationMode();
    CHIP_ERROR SetWiFiStationMode(WiFiStationMode val);
    bool IsWiFiStationEnabled();
    bool IsWiFiStationApplicationControlled();
    bool IsWiFiStationConnected();
    uint32_t GetWiFiStationReconnectIntervalMS();
    CHIP_ERROR SetWiFiStationReconnectIntervalMS(uint32_t val);
    bool IsWiFiStationProvisioned();
    void ClearWiFiStationProvision();
    CHIP_ERROR GetAndLogWifiStatsCounters();

    // WiFi AP methods
    WiFiAPMode GetWiFiAPMode();
    CHIP_ERROR SetWiFiAPMode(WiFiAPMode val);
    bool IsWiFiAPActive();
    bool IsWiFiAPApplicationControlled();
    void DemandStartWiFiAP();
    void StopOnDemandWiFiAP();
    void MaintainOnDemandWiFiAP();
    uint32_t GetWiFiAPIdleTimeoutMS();
    void SetWiFiAPIdleTimeoutMS(uint32_t val);

    // Thread Methods
    ThreadMode GetThreadMode();
    CHIP_ERROR SetThreadMode(ThreadMode val);
    bool IsThreadEnabled();
    bool IsThreadApplicationControlled();
    ThreadDeviceType GetThreadDeviceType();
    CHIP_ERROR SetThreadDeviceType(ThreadDeviceType deviceType);
    void GetThreadPollingConfig(ThreadPollingConfig & pollingConfig);
    CHIP_ERROR SetThreadPollingConfig(const ThreadPollingConfig & pollingConfig);
    bool IsThreadAttached();
    bool IsThreadProvisioned();
    void ErasePersistentInfo();
    void ResetThreadNetworkDiagnosticsCounts();
    CHIP_ERROR WriteThreadNetworkDiagnosticAttributeToTlv(AttributeId attributeId, const app::AttributeValueEncoder & encoder);

    // Ethernet network diagnostics methods
    CHIP_ERROR GetEthPacketRxCount(uint64_t & packetRxCount);
    CHIP_ERROR GetEthPacketTxCount(uint64_t & packetTxCount);
    CHIP_ERROR GetEthTxErrCount(uint64_t & txErrCount);
    CHIP_ERROR GetEthCollisionCount(uint64_t & collisionCount);
    CHIP_ERROR GetEthOverrunCount(uint64_t & overrunCount);
    CHIP_ERROR ResetEthNetworkDiagnosticsCounts();

    // WiFi network diagnostics methods
    CHIP_ERROR GetWiFiSecurityType(uint8_t & securityType);
    CHIP_ERROR GetWiFiVersion(uint8_t & wiFiVersion);
    CHIP_ERROR GetWiFiChannelNumber(uint16_t & channelNumber);
    CHIP_ERROR GetWiFiRssi(int8_t & rssi);
    CHIP_ERROR GetWiFiBeaconLostCount(uint32_t & beaconLostCount);
    CHIP_ERROR GetWiFiBeaconRxCount(uint32_t & beaconRxCount);
    CHIP_ERROR GetWiFiPacketMulticastRxCount(uint32_t & packetMulticastRxCount);
    CHIP_ERROR GetWiFiPacketMulticastTxCount(uint32_t & packetMulticastTxCount);
    CHIP_ERROR GetWiFiPacketUnicastRxCount(uint32_t & packetUnicastRxCount);
    CHIP_ERROR GetWiFiPacketUnicastTxCount(uint32_t & packetUnicastTxCount);
    CHIP_ERROR GetWiFiCurrentMaxRate(uint64_t & currentMaxRate);
    CHIP_ERROR GetWiFiOverrunCount(uint64_t & overrunCount);
    CHIP_ERROR ResetWiFiNetworkDiagnosticsCounts();

    // CHIPoBLE service methods
    Ble::BleLayer * GetBleLayer();
    CHIPoBLEServiceMode GetCHIPoBLEServiceMode();
    CHIP_ERROR SetCHIPoBLEServiceMode(CHIPoBLEServiceMode val);
    bool IsBLEAdvertisingEnabled();
    CHIP_ERROR SetBLEAdvertisingEnabled(bool val);
    bool IsBLEAdvertising();
    CHIP_ERROR SetBLEAdvertisingMode(BLEAdvertisingMode mode);
    CHIP_ERROR GetBLEDeviceName(char * buf, size_t bufSize);
    CHIP_ERROR SetBLEDeviceName(const char * deviceName);
    uint16_t NumBLEConnections();

    // User selected mode methods
    bool IsUserSelectedModeActive();
    void SetUserSelectedMode(bool val);
    uint16_t GetUserSelectedModeTimeout();
    void SetUserSelectedModeTimeout(uint16_t val);

    // Support methods
    static const char * WiFiStationModeToStr(WiFiStationMode mode);
    static const char * WiFiAPModeToStr(WiFiAPMode mode);
    static const char * WiFiStationStateToStr(WiFiStationState state);
    static const char * WiFiAPStateToStr(WiFiAPState state);
    static const char * CHIPoBLEServiceModeToStr(CHIPoBLEServiceMode mode);

private:
    // ===== Members for internal use by the following friends.

    friend class PlatformManagerImpl;
    template <class>
    friend class Internal::GenericPlatformManagerImpl;
    template <class>
    friend class Internal::GenericPlatformManagerImpl_FreeRTOS;
    template <class>
    friend class Internal::GenericPlatformManagerImpl_POSIX;

    CHIP_ERROR Init();
    void OnPlatformEvent(const ChipDeviceEvent * event);
    bool CanStartWiFiScan();
    void OnWiFiScanDone();
    void OnWiFiStationProvisionChange();

protected:
    // Construction/destruction limited to subclasses.
    ConnectivityManager()  = default;
    ~ConnectivityManager() = default;

    // No copy, move or assignment.
    ConnectivityManager(const ConnectivityManager &)  = delete;
    ConnectivityManager(const ConnectivityManager &&) = delete;
    ConnectivityManager & operator=(const ConnectivityManager &) = delete;
};

/**
 * Information describing the desired Thread polling behavior of a device.
 */
struct ConnectivityManager::ThreadPollingConfig
{
    uint32_t ActivePollingIntervalMS; /**< Interval at which the device polls its parent Thread router when
                                           when there are active chip exchanges in progress. Only meaningful
                                           when the device is acting as a sleepy end node. */

    uint32_t InactivePollingIntervalMS; /**< Interval at which the device polls its parent Thread router when
                                             when there are NO active chip exchanges in progress. Only meaningful
                                             when the device is acting as a sleepy end node. */

    void Clear() { memset(this, 0, sizeof(*this)); }
};

/**
 * Returns a reference to the public interface of the ConnectivityManager singleton object.
 *
 * chip applications should use this to access features of the ConnectivityManager object
 * that are common to all platforms.
 */
extern ConnectivityManager & ConnectivityMgr();

/**
 * Returns the platform-specific implementation of the ConnectivityManager singleton object.
 *
 * chip applications can use this to gain access to features of the ConnectivityManager
 * that are specific to the selected platform.
 */
extern ConnectivityManagerImpl & ConnectivityMgrImpl();

} // namespace DeviceLayer
} // namespace chip

/* Include a header file containing the implementation of the ConfigurationManager
 * object for the selected platform.
 */
#ifdef EXTERNAL_CONNECTIVITYMANAGERIMPL_HEADER
#include EXTERNAL_CONNECTIVITYMANAGERIMPL_HEADER
#elif defined(CHIP_DEVICE_LAYER_TARGET)
#define CONNECTIVITYMANAGERIMPL_HEADER <platform/CHIP_DEVICE_LAYER_TARGET/ConnectivityManagerImpl.h>
#include CONNECTIVITYMANAGERIMPL_HEADER
#endif // defined(CHIP_DEVICE_LAYER_TARGET)

namespace chip {
namespace DeviceLayer {

inline ConnectivityManager::WiFiStationMode ConnectivityManager::GetWiFiStationMode()
{
    return static_cast<ImplClass *>(this)->_GetWiFiStationMode();
}

inline CHIP_ERROR ConnectivityManager::SetWiFiStationMode(WiFiStationMode val)
{
    return static_cast<ImplClass *>(this)->_SetWiFiStationMode(val);
}

inline bool ConnectivityManager::IsWiFiStationEnabled()
{
    return static_cast<ImplClass *>(this)->_IsWiFiStationEnabled();
}

inline bool ConnectivityManager::IsWiFiStationApplicationControlled()
{
    return static_cast<ImplClass *>(this)->_IsWiFiStationApplicationControlled();
}

inline bool ConnectivityManager::IsWiFiStationConnected()
{
    return static_cast<ImplClass *>(this)->_IsWiFiStationConnected();
}

inline uint32_t ConnectivityManager::GetWiFiStationReconnectIntervalMS()
{
    return static_cast<ImplClass *>(this)->_GetWiFiStationReconnectIntervalMS();
}

inline CHIP_ERROR ConnectivityManager::SetWiFiStationReconnectIntervalMS(uint32_t val)
{
    return static_cast<ImplClass *>(this)->_SetWiFiStationReconnectIntervalMS(val);
}

inline bool ConnectivityManager::IsWiFiStationProvisioned()
{
    return static_cast<ImplClass *>(this)->_IsWiFiStationProvisioned();
}

inline void ConnectivityManager::ClearWiFiStationProvision()
{
    static_cast<ImplClass *>(this)->_ClearWiFiStationProvision();
}

inline ConnectivityManager::WiFiAPMode ConnectivityManager::GetWiFiAPMode()
{
    return static_cast<ImplClass *>(this)->_GetWiFiAPMode();
}

inline CHIP_ERROR ConnectivityManager::SetWiFiAPMode(WiFiAPMode val)
{
    return static_cast<ImplClass *>(this)->_SetWiFiAPMode(val);
}

inline bool ConnectivityManager::IsWiFiAPActive()
{
    return static_cast<ImplClass *>(this)->_IsWiFiAPActive();
}

inline bool ConnectivityManager::IsWiFiAPApplicationControlled()
{
    return static_cast<ImplClass *>(this)->_IsWiFiAPApplicationControlled();
}

inline void ConnectivityManager::DemandStartWiFiAP()
{
    static_cast<ImplClass *>(this)->_DemandStartWiFiAP();
}

inline void ConnectivityManager::StopOnDemandWiFiAP()
{
    static_cast<ImplClass *>(this)->_StopOnDemandWiFiAP();
}

inline void ConnectivityManager::MaintainOnDemandWiFiAP()
{
    static_cast<ImplClass *>(this)->_MaintainOnDemandWiFiAP();
}

inline uint32_t ConnectivityManager::GetWiFiAPIdleTimeoutMS()
{
    return static_cast<ImplClass *>(this)->_GetWiFiAPIdleTimeoutMS();
}

inline void ConnectivityManager::SetWiFiAPIdleTimeoutMS(uint32_t val)
{
    static_cast<ImplClass *>(this)->_SetWiFiAPIdleTimeoutMS(val);
}

inline CHIP_ERROR ConnectivityManager::GetAndLogWifiStatsCounters()
{
    return static_cast<ImplClass *>(this)->_GetAndLogWifiStatsCounters();
}

inline CHIP_ERROR ConnectivityManager::GetEthPacketRxCount(uint64_t & packetRxCount)
{
    return static_cast<ImplClass *>(this)->_GetEthPacketRxCount(packetRxCount);
}

inline CHIP_ERROR ConnectivityManager::GetEthPacketTxCount(uint64_t & packetTxCount)
{
    return static_cast<ImplClass *>(this)->_GetEthPacketTxCount(packetTxCount);
}

inline CHIP_ERROR ConnectivityManager::GetEthTxErrCount(uint64_t & txErrCount)
{
    return static_cast<ImplClass *>(this)->_GetEthTxErrCount(txErrCount);
}

inline CHIP_ERROR ConnectivityManager::GetEthCollisionCount(uint64_t & collisionCount)
{
    return static_cast<ImplClass *>(this)->_GetEthCollisionCount(collisionCount);
}

inline CHIP_ERROR ConnectivityManager::GetEthOverrunCount(uint64_t & overrunCount)
{
    return static_cast<ImplClass *>(this)->_GetEthOverrunCount(overrunCount);
}

inline CHIP_ERROR ConnectivityManager::ResetEthNetworkDiagnosticsCounts()
{
    return static_cast<ImplClass *>(this)->_ResetEthNetworkDiagnosticsCounts();
}

inline CHIP_ERROR ConnectivityManager::GetWiFiSecurityType(uint8_t & securityType)
{
    return static_cast<ImplClass *>(this)->_GetWiFiSecurityType(securityType);
}

inline CHIP_ERROR ConnectivityManager::GetWiFiVersion(uint8_t & wiFiVersion)
{
    return static_cast<ImplClass *>(this)->_GetWiFiVersion(wiFiVersion);
}

inline CHIP_ERROR ConnectivityManager::GetWiFiChannelNumber(uint16_t & channelNumber)
{
    return static_cast<ImplClass *>(this)->_GetWiFiChannelNumber(channelNumber);
}

inline CHIP_ERROR ConnectivityManager::GetWiFiRssi(int8_t & rssi)
{
    return static_cast<ImplClass *>(this)->_GetWiFiRssi(rssi);
}

inline CHIP_ERROR ConnectivityManager::GetWiFiBeaconLostCount(uint32_t & beaconLostCount)
{
    return static_cast<ImplClass *>(this)->_GetWiFiBeaconLostCount(beaconLostCount);
}

inline CHIP_ERROR ConnectivityManager::GetWiFiBeaconRxCount(uint32_t & beaconRxCount)
{
    return static_cast<ImplClass *>(this)->_GetWiFiBeaconRxCount(beaconRxCount);
}

inline CHIP_ERROR ConnectivityManager::GetWiFiPacketMulticastRxCount(uint32_t & packetMulticastRxCount)
{
    return static_cast<ImplClass *>(this)->_GetWiFiPacketMulticastRxCount(packetMulticastRxCount);
}

inline CHIP_ERROR ConnectivityManager::GetWiFiPacketMulticastTxCount(uint32_t & packetMulticastTxCount)
{
    return static_cast<ImplClass *>(this)->_GetWiFiPacketMulticastTxCount(packetMulticastTxCount);
}

inline CHIP_ERROR ConnectivityManager::GetWiFiPacketUnicastRxCount(uint32_t & packetUnicastRxCount)
{
    return static_cast<ImplClass *>(this)->_GetWiFiPacketUnicastRxCount(packetUnicastRxCount);
}

inline CHIP_ERROR ConnectivityManager::GetWiFiPacketUnicastTxCount(uint32_t & packetUnicastTxCount)
{
    return static_cast<ImplClass *>(this)->_GetWiFiPacketUnicastTxCount(packetUnicastTxCount);
}

inline CHIP_ERROR ConnectivityManager::GetWiFiCurrentMaxRate(uint64_t & currentMaxRate)
{
    return static_cast<ImplClass *>(this)->_GetWiFiCurrentMaxRate(currentMaxRate);
}

inline CHIP_ERROR ConnectivityManager::GetWiFiOverrunCount(uint64_t & overrunCount)
{
    return static_cast<ImplClass *>(this)->_GetWiFiOverrunCount(overrunCount);
}

inline CHIP_ERROR ConnectivityManager::ResetWiFiNetworkDiagnosticsCounts()
{
    return static_cast<ImplClass *>(this)->_ResetWiFiNetworkDiagnosticsCounts();
}

inline ConnectivityManager::ThreadMode ConnectivityManager::GetThreadMode()
{
    return static_cast<ImplClass *>(this)->_GetThreadMode();
}

inline CHIP_ERROR ConnectivityManager::SetThreadMode(ThreadMode val)
{
    return static_cast<ImplClass *>(this)->_SetThreadMode(val);
}

inline bool ConnectivityManager::IsThreadEnabled()
{
    return static_cast<ImplClass *>(this)->_IsThreadEnabled();
}

inline bool ConnectivityManager::IsThreadApplicationControlled()
{
    return static_cast<ImplClass *>(this)->_IsThreadApplicationControlled();
}

inline ConnectivityManager::ThreadDeviceType ConnectivityManager::GetThreadDeviceType()
{
    return static_cast<ImplClass *>(this)->_GetThreadDeviceType();
}

inline CHIP_ERROR ConnectivityManager::SetThreadDeviceType(ThreadDeviceType deviceType)
{
    return static_cast<ImplClass *>(this)->_SetThreadDeviceType(deviceType);
}

inline void ConnectivityManager::GetThreadPollingConfig(ThreadPollingConfig & pollingConfig)
{
    return static_cast<ImplClass *>(this)->_GetThreadPollingConfig(pollingConfig);
}

inline CHIP_ERROR ConnectivityManager::SetThreadPollingConfig(const ThreadPollingConfig & pollingConfig)
{
    return static_cast<ImplClass *>(this)->_SetThreadPollingConfig(pollingConfig);
}

inline bool ConnectivityManager::IsThreadAttached()
{
    return static_cast<ImplClass *>(this)->_IsThreadAttached();
}

inline bool ConnectivityManager::IsThreadProvisioned()
{
    return static_cast<ImplClass *>(this)->_IsThreadProvisioned();
}

inline void ConnectivityManager::ErasePersistentInfo()
{
    static_cast<ImplClass *>(this)->_ErasePersistentInfo();
}

inline void ConnectivityManager::ResetThreadNetworkDiagnosticsCounts()
{
    static_cast<ImplClass *>(this)->_ResetThreadNetworkDiagnosticsCounts();
}

/*
 * @brief Get runtime value from the thread network based on the given attribute ID.
 *        The info is encoded via the AttributeValueEncoder.
 *
 * @param attributeId Id of the attribute for the requested info.
 * @param aEncoder Encoder to encode the attribute value.
 *
 * @return CHIP_NO_ERROR = Succes.
 *         CHIP_ERROR_NOT_IMPLEMENTED = Runtime value for this attribute to yet available to send as reply
 *                                      Use standard read.
 *         CHIP_ERROR_UNSUPPORTED_CHIP_FEATURE = Is not a Runtime readable attribute. Use standard read
 *         All other errors should be treated as a read error and reported as such.
 */
inline CHIP_ERROR ConnectivityManager::WriteThreadNetworkDiagnosticAttributeToTlv(AttributeId attributeId,
                                                                                  const app::AttributeValueEncoder & encoder)
{
    return static_cast<ImplClass *>(this)->_WriteThreadNetworkDiagnosticAttributeToTlv(attributeId, encoder);
}

inline Ble::BleLayer * ConnectivityManager::GetBleLayer()
{
    return static_cast<ImplClass *>(this)->_GetBleLayer();
}

inline ConnectivityManager::CHIPoBLEServiceMode ConnectivityManager::GetCHIPoBLEServiceMode()
{
    return static_cast<ImplClass *>(this)->_GetCHIPoBLEServiceMode();
}

inline CHIP_ERROR ConnectivityManager::SetCHIPoBLEServiceMode(CHIPoBLEServiceMode val)
{
    return static_cast<ImplClass *>(this)->_SetCHIPoBLEServiceMode(val);
}

inline bool ConnectivityManager::IsBLEAdvertisingEnabled()
{
    return static_cast<ImplClass *>(this)->_IsBLEAdvertisingEnabled();
}

inline CHIP_ERROR ConnectivityManager::SetBLEAdvertisingEnabled(bool val)
{
    return static_cast<ImplClass *>(this)->_SetBLEAdvertisingEnabled(val);
}

inline bool ConnectivityManager::IsBLEAdvertising()
{
    return static_cast<ImplClass *>(this)->_IsBLEAdvertising();
}

inline CHIP_ERROR ConnectivityManager::SetBLEAdvertisingMode(BLEAdvertisingMode mode)
{
    return static_cast<ImplClass *>(this)->_SetBLEAdvertisingMode(mode);
}

inline CHIP_ERROR ConnectivityManager::GetBLEDeviceName(char * buf, size_t bufSize)
{
    return static_cast<ImplClass *>(this)->_GetBLEDeviceName(buf, bufSize);
}

inline CHIP_ERROR ConnectivityManager::SetBLEDeviceName(const char * deviceName)
{
    return static_cast<ImplClass *>(this)->_SetBLEDeviceName(deviceName);
}

inline uint16_t ConnectivityManager::NumBLEConnections()
{
    return static_cast<ImplClass *>(this)->_NumBLEConnections();
}

inline bool ConnectivityManager::IsUserSelectedModeActive()
{
    return static_cast<ImplClass *>(this)->_IsUserSelectedModeActive();
}

inline void ConnectivityManager::SetUserSelectedMode(bool val)
{
    static_cast<ImplClass *>(this)->_SetUserSelectedMode(val);
}

inline uint16_t ConnectivityManager::GetUserSelectedModeTimeout()
{
    return static_cast<ImplClass *>(this)->_GetUserSelectedModeTimeout();
}

inline void ConnectivityManager::SetUserSelectedModeTimeout(uint16_t val)
{
    static_cast<ImplClass *>(this)->_SetUserSelectedModeTimeout(val);
}

inline const char * ConnectivityManager::WiFiStationModeToStr(WiFiStationMode mode)
{
    return ImplClass::_WiFiStationModeToStr(mode);
}

inline const char * ConnectivityManager::WiFiAPModeToStr(WiFiAPMode mode)
{
    return ImplClass::_WiFiAPModeToStr(mode);
}

inline const char * ConnectivityManager::WiFiStationStateToStr(WiFiStationState state)
{
    return ImplClass::_WiFiStationStateToStr(state);
}

inline const char * ConnectivityManager::WiFiAPStateToStr(WiFiAPState state)
{
    return ImplClass::_WiFiAPStateToStr(state);
}

inline const char * ConnectivityManager::CHIPoBLEServiceModeToStr(CHIPoBLEServiceMode mode)
{
    return ImplClass::_CHIPoBLEServiceModeToStr(mode);
}

inline CHIP_ERROR ConnectivityManager::Init()
{
    return static_cast<ImplClass *>(this)->_Init();
}

inline void ConnectivityManager::OnPlatformEvent(const ChipDeviceEvent * event)
{
    static_cast<ImplClass *>(this)->_OnPlatformEvent(event);
}

inline bool ConnectivityManager::CanStartWiFiScan()
{
    return static_cast<ImplClass *>(this)->_CanStartWiFiScan();
}

inline void ConnectivityManager::OnWiFiScanDone()
{
    static_cast<ImplClass *>(this)->_OnWiFiScanDone();
}

inline void ConnectivityManager::OnWiFiStationProvisionChange()
{
    static_cast<ImplClass *>(this)->_OnWiFiStationProvisionChange();
}

} // namespace DeviceLayer
} // namespace chip
