/**
 *
 *    Copyright (c) 2021 Project CHIP Authors
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
/****************************************************************************
 * @file
 * @brief Routines for the Content Launch plugin, the
 *server implementation of the Content Launch cluster.
 *******************************************************************************
 ******************************************************************************/

#include <app-common/zap-generated/cluster-objects.h>
#include <app/CommandHandler.h>
#include <app/ConcreteCommandPath.h>
#include <app/util/af.h>
#include <lib/support/Span.h>
#include <lib/support/logging/CHIPLogging.h>
#include <platform/internal/DeviceControlServer.h>

using namespace chip;
using namespace chip::app::Clusters::GeneralCommissioning;

bool emberAfGeneralCommissioningClusterArmFailSafeCallback(app::CommandHandler * commandObj,
                                                           const app::ConcreteCommandPath & commandPath, EndpointId endpoint,
                                                           uint16_t expiryLengthSeconds, uint64_t breadcrumb, uint32_t timeoutMs,
                                                           Commands::ArmFailSafe::DecodableType & commandData)
{
    CHIP_ERROR err = DeviceLayer::Internal::DeviceControlServer::DeviceControlSvr().ArmFailSafe(expiryLengthSeconds);
    emberAfSendImmediateDefaultResponse(err == CHIP_NO_ERROR ? EMBER_ZCL_STATUS_SUCCESS : EMBER_ZCL_STATUS_FAILURE);

    return true;
}

bool emberAfGeneralCommissioningClusterCommissioningCompleteCallback(app::CommandHandler * commandObj,
                                                                     const app::ConcreteCommandPath & commandPath,
                                                                     EndpointId endpoint,
                                                                     Commands::CommissioningComplete::DecodableType & commandData)
{
    CHIP_ERROR err = DeviceLayer::Internal::DeviceControlServer::DeviceControlSvr().CommissioningComplete();
    emberAfSendImmediateDefaultResponse(err == CHIP_NO_ERROR ? EMBER_ZCL_STATUS_SUCCESS : EMBER_ZCL_STATUS_FAILURE);

    return true;
}

bool emberAfGeneralCommissioningClusterSetRegulatoryConfigCallback(app::CommandHandler * commandObj,
                                                                   const app::ConcreteCommandPath & commandPath,
                                                                   EndpointId endpoint, uint8_t location, uint8_t * countryCode,
                                                                   uint64_t breadcrumb, uint32_t timeoutMs,
                                                                   Commands::SetRegulatoryConfig::DecodableType & commandData)
{
    CHIP_ERROR err = DeviceLayer::Internal::DeviceControlServer::DeviceControlSvr().SetRegulatoryConfig(
        location, reinterpret_cast<const char *>(countryCode), breadcrumb);

    emberAfSendImmediateDefaultResponse(err == CHIP_NO_ERROR ? EMBER_ZCL_STATUS_SUCCESS : EMBER_ZCL_STATUS_FAILURE);

    return true;
}
