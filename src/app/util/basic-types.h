/**
 *
 *    Copyright (c) 2020 Project CHIP Authors
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
 * @file
 * @brief The include file for all the types for the data model that are not
 *        dependent on an individual application configuration.
 */

#pragma once

#include <stdint.h>

#include <lib/core/GroupId.h>
#include <lib/core/NodeId.h>

// Pull in VendorId
#include <lib/core/CHIPVendorIdentifiers.hpp>

namespace chip {
typedef uint8_t ActionId;
typedef uint32_t AttributeId;
typedef uint32_t ClusterId;
typedef uint32_t CommandId;
typedef uint32_t DataVersion;
typedef uint32_t DeviceTypeId;
typedef uint16_t EndpointId;
typedef uint32_t EventId;
typedef uint64_t EventNumber;
typedef uint64_t FabricId;
typedef uint8_t FabricIndex;
typedef uint32_t FieldId;
typedef uint16_t ListIndex;
typedef uint32_t TransactionId;
typedef uint32_t StatusCode;
typedef uint8_t Percent;
typedef uint16_t Percent100ths;

static constexpr FabricIndex kUndefinedFabricIndex = 0;
} // namespace chip
