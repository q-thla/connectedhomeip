/*
 *
 *    Copyright (c) 2020-2021 Project CHIP Authors
 *    Copyright (c) 2019-2020 Google LLC.
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
 *          Provides an generic implementation of ConfigurationManager features
 *          for use on various platforms.
 */

#pragma once

#include <lib/support/BitFlags.h>
#include <platform/ConfigurationManager.h>

#if CHIP_ENABLE_ROTATING_DEVICE_ID
#include <lib/support/LifetimePersistedCounter.h>
#endif

namespace chip {
namespace DeviceLayer {

class ProvisioningDataSet;

namespace Internal {

/**
 * Provides a generic implementation of ConfigurationManager features that works on multiple platforms.
 *
 * This template contains implementations of select features from the ConfigurationManager abstract
 * interface that are suitable for use on all platforms.  It is intended to be inherited (directly
 * or indirectly) by the ConfigurationManagerImpl class, which also appears as the template's ImplClass
 * parameter.
 */
template <class ImplClass>
class GenericConfigurationManagerImpl : public ConfigurationManager
{
public:
    // ===== Methods that implement the ConfigurationManager abstract interface.

    CHIP_ERROR Init() override;
    CHIP_ERROR GetVendorName(char * buf, size_t bufSize) override;
    CHIP_ERROR GetVendorId(uint16_t & vendorId) override;
    CHIP_ERROR GetProductName(char * buf, size_t bufSize) override;
    CHIP_ERROR GetProductId(uint16_t & productId) override;
    CHIP_ERROR GetProductRevisionString(char * buf, size_t bufSize) override;
    CHIP_ERROR GetProductRevision(uint16_t & productRev) override;
    CHIP_ERROR StoreProductRevision(uint16_t productRev) override;
    CHIP_ERROR GetFirmwareRevisionString(char * buf, size_t bufSize) override;
    CHIP_ERROR GetFirmwareRevision(uint32_t & firmwareRev) override;
    CHIP_ERROR GetFirmwareBuildTime(uint16_t & year, uint8_t & month, uint8_t & dayOfMonth, uint8_t & hour, uint8_t & minute,
                                    uint8_t & second) override;
    CHIP_ERROR GetSerialNumber(char * buf, size_t bufSize, size_t & serialNumLen) override;
    CHIP_ERROR StoreSerialNumber(const char * serialNum, size_t serialNumLen) override;
    CHIP_ERROR GetPrimaryWiFiMACAddress(uint8_t * buf) override;
    CHIP_ERROR StorePrimaryWiFiMACAddress(const uint8_t * buf) override;
    CHIP_ERROR GetPrimary802154MACAddress(uint8_t * buf) override;
    CHIP_ERROR StorePrimary802154MACAddress(const uint8_t * buf) override;
    CHIP_ERROR GetManufacturingDate(uint16_t & year, uint8_t & month, uint8_t & dayOfMonth) override;
    CHIP_ERROR StoreManufacturingDate(const char * mfgDate, size_t mfgDateLen) override;
    CHIP_ERROR GetDeviceId(uint64_t & deviceId) override;
    CHIP_ERROR GetDeviceCertificate(uint8_t * buf, size_t bufSize, size_t & certLen) override;
    CHIP_ERROR GetDeviceIntermediateCACerts(uint8_t * buf, size_t bufSize, size_t & certsLen) override;
    CHIP_ERROR GetDevicePrivateKey(uint8_t * buf, size_t bufSize, size_t & keyLen) override;
    CHIP_ERROR GetManufacturerDeviceId(uint64_t & deviceId) override;
    CHIP_ERROR StoreManufacturerDeviceId(uint64_t deviceId) override;
    CHIP_ERROR GetManufacturerDeviceCertificate(uint8_t * buf, size_t bufSize, size_t & certLen) override;
    CHIP_ERROR StoreManufacturerDeviceCertificate(const uint8_t * cert, size_t certLen) override;
    CHIP_ERROR GetManufacturerDeviceIntermediateCACerts(uint8_t * buf, size_t bufSize, size_t & certsLen) override;
    CHIP_ERROR StoreManufacturerDeviceIntermediateCACerts(const uint8_t * certs, size_t certsLen) override;
    CHIP_ERROR GetManufacturerDevicePrivateKey(uint8_t * buf, size_t bufSize, size_t & keyLen) override;
    CHIP_ERROR StoreManufacturerDevicePrivateKey(const uint8_t * key, size_t keyLen) override;
    CHIP_ERROR GetSetupPinCode(uint32_t & setupPinCode) override;
    CHIP_ERROR StoreSetupPinCode(uint32_t setupPinCode) override;
    CHIP_ERROR GetSetupDiscriminator(uint16_t & setupDiscriminator) override;
    CHIP_ERROR StoreSetupDiscriminator(uint16_t setupDiscriminator) override;
    CHIP_ERROR GetFabricId(uint64_t & fabricId) override;
    CHIP_ERROR StoreFabricId(uint64_t fabricId) override;
#if CHIP_ENABLE_ROTATING_DEVICE_ID
    CHIP_ERROR GetLifetimeCounter(uint16_t & lifetimeCounter) override;
    CHIP_ERROR _IncrementLifetimeCounter();
#endif
    CHIP_ERROR GetServiceId(uint64_t & serviceId) override;
    CHIP_ERROR GetServiceConfig(uint8_t * buf, size_t bufSize, size_t & serviceConfigLen) override;
    CHIP_ERROR StoreServiceConfig(const uint8_t * serviceConfig, size_t serviceConfigLen) override;
    CHIP_ERROR GetPairedAccountId(char * buf, size_t bufSize, size_t & accountIdLen) override;
    CHIP_ERROR StorePairedAccountId(const char * accountId, size_t accountIdLen) override;
    CHIP_ERROR StoreServiceProvisioningData(uint64_t serviceId, const uint8_t * serviceConfig, size_t serviceConfigLen,
                                            const char * accountId, size_t accountIdLen) override;
    CHIP_ERROR ClearServiceProvisioningData() override;
    CHIP_ERROR GetFailSafeArmed(bool & val) override;
    CHIP_ERROR SetFailSafeArmed(bool val) override;
    CHIP_ERROR GetQRCodeString(char * buf, size_t bufSize) override;
    CHIP_ERROR GetWiFiAPSSID(char * buf, size_t bufSize) override;
    CHIP_ERROR GetBLEDeviceIdentificationInfo(Ble::ChipBLEDeviceIdentificationInfo & deviceIdInfo) override;
    bool IsCommissionableDeviceTypeEnabled() override;
    CHIP_ERROR GetDeviceType(uint16_t & deviceType) override;
    bool IsCommissionableDeviceNameEnabled() override;
    CHIP_ERROR GetDeviceName(char * buf, size_t bufSize) override;
    CHIP_ERROR GetInitialPairingHint(uint16_t & pairingHint) override;
    CHIP_ERROR GetInitialPairingInstruction(char * buf, size_t bufSize) override;
    CHIP_ERROR GetSecondaryPairingHint(uint16_t & pairingHint) override;
    CHIP_ERROR GetSecondaryPairingInstruction(char * buf, size_t bufSize) override;
    CHIP_ERROR GetRegulatoryLocation(uint32_t & location) override;
    CHIP_ERROR StoreRegulatoryLocation(uint32_t location) override;
    CHIP_ERROR GetCountryCode(char * buf, size_t bufSize, size_t & codeLen) override;
    CHIP_ERROR StoreCountryCode(const char * code, size_t codeLen) override;
    CHIP_ERROR GetBreadcrumb(uint64_t & breadcrumb) override;
    CHIP_ERROR StoreBreadcrumb(uint64_t breadcrumb) override;
    CHIP_ERROR ConfigureChipStack() override;
#if !defined(NDEBUG)
    CHIP_ERROR RunUnitTests(void) override;
#endif
    bool IsServiceProvisioned() override;
    bool IsMemberOfFabric() override;
    bool IsPairedToAccount() override;
    bool IsFullyProvisioned() override;
    CHIP_ERROR ComputeProvisioningHash(uint8_t * hashBuf, size_t hashBufSize) override;
    void InitiateFactoryReset() override;
    void LogDeviceConfig() override;

    virtual ~GenericConfigurationManagerImpl() = default;

protected:
    enum class Flags : uint8_t
    {
        kIsServiceProvisioned                    = 0x01,
        kIsMemberOfFabric                        = 0x02,
        kIsPairedToAccount                       = 0x04,
        kUseManufacturerCredentialsAsOperational = 0x08,
    };

    BitFlags<Flags> mFlags;
#if CHIP_ENABLE_ROTATING_DEVICE_ID
    chip::LifetimePersistedCounter mLifetimePersistedCounter;
#endif
    CHIP_ERROR PersistProvisioningData(ProvisioningDataSet & provData);

private:
    ImplClass * Impl() { return static_cast<ImplClass *>(this); }
};

// Instruct the compiler to instantiate the template only when explicitly told to do so.
extern template class Internal::GenericConfigurationManagerImpl<ConfigurationManagerImpl>;

template <class ImplClass>
inline CHIP_ERROR GenericConfigurationManagerImpl<ImplClass>::GetVendorId(uint16_t & vendorId)
{
    vendorId = static_cast<uint16_t>(CHIP_DEVICE_CONFIG_DEVICE_VENDOR_ID);
    return CHIP_NO_ERROR;
}

template <class ImplClass>
inline CHIP_ERROR GenericConfigurationManagerImpl<ImplClass>::GetProductId(uint16_t & productId)
{
    productId = static_cast<uint16_t>(CHIP_DEVICE_CONFIG_DEVICE_PRODUCT_ID);
    return CHIP_NO_ERROR;
}

template <class ImplClass>
inline CHIP_ERROR GenericConfigurationManagerImpl<ImplClass>::GetFirmwareRevision(uint32_t & firmwareRev)
{
    firmwareRev = static_cast<uint32_t>(CHIP_DEVICE_CONFIG_DEVICE_FIRMWARE_REVISION);
    return CHIP_NO_ERROR;
}

template <class ImplClass>
inline CHIP_ERROR GenericConfigurationManagerImpl<ImplClass>::GetDeviceType(uint16_t & deviceType)
{
    deviceType = static_cast<uint16_t>(CHIP_DEVICE_CONFIG_DEVICE_TYPE);
    return CHIP_NO_ERROR;
}

template <class ImplClass>
inline CHIP_ERROR GenericConfigurationManagerImpl<ImplClass>::GetInitialPairingHint(uint16_t & pairingHint)
{
    pairingHint = static_cast<uint16_t>(CHIP_DEVICE_CONFIG_PAIRING_INITIAL_HINT);
    return CHIP_NO_ERROR;
}

template <class ImplClass>
inline CHIP_ERROR GenericConfigurationManagerImpl<ImplClass>::GetSecondaryPairingHint(uint16_t & pairingHint)
{
    pairingHint = static_cast<uint16_t>(CHIP_DEVICE_CONFIG_PAIRING_SECONDARY_HINT);
    return CHIP_NO_ERROR;
}

} // namespace Internal
} // namespace DeviceLayer
} // namespace chip
