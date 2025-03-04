/*
 *
 *    Copyright (c) 2020 Project CHIP Authors
 *    Copyright (c) 2013-2017 Nest Labs, Inc.
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
 *      This file defines macros, constants, and interfaces for a
 *      platform-independent logging interface for the chip SDK.
 *
 *      chip SDK clients may choose, at compile time, among Android,
 *      C Standard I/O, or external (platform- and integrator-defined)
 *      logging style implementations that will be invoked when any of
 *      the following preprocessor symbols are asserted:
 *
 *         - #CHIP_ERROR_LOGGING
 *         - #CHIP_PROGRESS_LOGGING
 *         - #CHIP_DETAIL_LOGGING
 *
 */

#pragma once

#include <lib/core/CHIPConfig.h>

#include <platform/logging/LogV.h>

#include <lib/support/logging/Constants.h>

#include <inttypes.h>
#include <stdarg.h>
#include <stdint.h>

/**
 *   @namespace chip::Logging
 *
 *   @brief
 *     This namespace includes all interfaces within chip for shared
 *     logging support.
 *
 *     The interfaces include macros, constants, and functions for a
 *     platform-independent logging interface for the chip SDK.
 *
 *     chip SDK clients may choose, at compile time, among Android,
 *     C Standard I/O, or external (platform- and integrator-defined)
 *     logging style implementations that will be invoked when any of
 *     the following preprocessor symbols are asserted:
 *
 *        - #CHIP_ERROR_LOGGING
 *        - #CHIP_PROGRESS_LOGGING
 *        - #CHIP_DETAIL_LOGGING
 *
 */

namespace chip {
namespace Logging {

using LogRedirectCallback_t = void (*)(const char * module, uint8_t category, const char * msg, va_list args);

void SetLogRedirectCallback(LogRedirectCallback_t callback);

/**
 * gcc and clang provide a way to warn for a custom formatter when formats don't
 * match arguments.  Use that for Log() so we catch mistakes.  The "format"
 * attribute takes the type of format, which arg is the format string, and which
 * arg is the first variadic arg, with both arg numbers 1-based.
 */

#if defined(__GNUC__)
#define ENFORCE_FORMAT(n, m) __attribute__((format(printf, n, m)))
#else                        // __GNUC__
#define ENFORCE_FORMAT(n, m) /* How to do with MSVC? */
#endif                       // __GNUC__

void LogV(uint8_t module, uint8_t category, const char * msg, va_list args);
void Log(uint8_t module, uint8_t category, const char * msg, ...) ENFORCE_FORMAT(3, 4);

uint8_t GetLogFilter();
void SetLogFilter(uint8_t category);

#ifndef CHIP_ERROR_LOGGING
#define CHIP_ERROR_LOGGING 1
#endif

#ifndef CHIP_LOG_FILTERING
#define CHIP_LOG_FILTERING 1
#endif

#if CHIP_ERROR_LOGGING
/**
 * @def ChipLogError(MOD, MSG, ...)
 *
 * @brief
 *   Log a chip message for the specified module in the 'Error'
 *   category.
 *
 */
#ifndef ChipLogError
#define ChipLogError(MOD, MSG, ...)                                                                                                \
    chip::Logging::Log(chip::Logging::kLogModule_##MOD, chip::Logging::kLogCategory_Error, MSG, ##__VA_ARGS__)
#endif
#else
#define ChipLogError(MOD, MSG, ...) ((void) 0)
#endif

#ifndef CHIP_PROGRESS_LOGGING
#define CHIP_PROGRESS_LOGGING 1
#endif

#if CHIP_PROGRESS_LOGGING
/**
 * @def ChipLogProgress(MOD, MSG, ...)
 *
 * @brief
 *   Log a chip message for the specified module in the 'Progress'
 *   category.
 *
 */
#ifndef ChipLogProgress
#define ChipLogProgress(MOD, MSG, ...)                                                                                             \
    chip::Logging::Log(chip::Logging::kLogModule_##MOD, chip::Logging::kLogCategory_Progress, MSG, ##__VA_ARGS__)
#endif
#else
#define ChipLogProgress(MOD, MSG, ...) ((void) 0)
#endif

#ifndef CHIP_DETAIL_LOGGING
#define CHIP_DETAIL_LOGGING 1
#endif

#if CHIP_DETAIL_LOGGING
/**
 * @def ChipLogDetail(MOD, MSG, ...)
 *
 * @brief
 *   Log a chip message for the specified module in the 'Detail'
 *   category.
 *
 */
#ifndef ChipLogDetail
#define ChipLogDetail(MOD, MSG, ...)                                                                                               \
    chip::Logging::Log(chip::Logging::kLogModule_##MOD, chip::Logging::kLogCategory_Detail, MSG, ##__VA_ARGS__)
#endif
#else
#define ChipLogDetail(MOD, MSG, ...) ((void) 0)
#endif

#if CHIP_ERROR_LOGGING || CHIP_PROGRESS_LOGGING || CHIP_DETAIL_LOGGING
#define _CHIP_USE_LOGGING 1
#else
#define _CHIP_USE_LOGGING 0
#endif /* CHIP_ERROR_LOGGING || CHIP_PROGRESS_LOGGING || CHIP_DETAIL_LOGGING */

#if _CHIP_USE_LOGGING

/**
 * CHIP logging length constants
 */
static constexpr uint16_t kMaxModuleNameLen  = 3;
static constexpr uint16_t kMaxPrefixLen      = 3;
static constexpr uint16_t kMaxSeparatorLen   = 2;
static constexpr uint16_t kMaxTrailerLen     = 2;
static constexpr uint16_t kMaxMessagePadding = (chip::Logging::kMaxPrefixLen + chip::Logging::kMaxModuleNameLen +
                                                chip::Logging::kMaxSeparatorLen + chip::Logging::kMaxTrailerLen);

void GetMessageWithPrefix(char * buf, uint8_t bufSize, uint8_t module, const char * msg);
void GetModuleName(char * buf, uint8_t bufSize, uint8_t module);

#else

static inline void GetMessageWithPrefix(char * buf, uint8_t bufSize, uint8_t module, const char * msg)
{
    return;
}

static inline void GetModuleName(char * buf, uint8_t bufSize, uint8_t module)
{
    return;
}

#endif // _CHIP_USE_LOGGING

bool IsCategoryEnabled(uint8_t category);

/**
 *  @def ChipLogIfFalse(aCondition)
 *
 *  @brief
 *    This checks for the specified condition, which is expected to
 *    commonly be true and emits some log, based on configuration, if
 *    the condition is false.
 *
 *  @note
 *    Evaluation of @a aCondition is always done, but logging is only enabled when
 *    #CHIP_CONFIG_ENABLE_CONDITION_LOGGING is enabled. This can be turned on or
 *    off for each compilation unit by enabling or disabling, as desired,
 *    #CHIP_CONFIG_ENABLE_CONDITION_LOGGING before ChipLogging.h is included by
 *    the preprocessor.
 *
 *  Example Usage:
 *
 *  @code
 *  #define CHIP_CONFIG_ENABLE_CONDITION_LOGGING 1
 *
 *  #include <chip/Support/Logging/ChipLogging.h>
 *
 *  ...
 *
 *  void foo(void)
 *  {
 *      CHIP_ERROR err = CHIP_NO_ERROR;
 *
 *      ...
 *
 *  exit:
 *      ChipLogIfFalse(CHIP_END_OF_TLV == err);
 *  }
 *  @endcode
 *
 *  @param[in]  aCondition     A Boolean expression to be evaluated.
 *
 *  @sa CHIP_CONFIG_ENABLE_TRACE_ON_CHECK_FAILURE
 *
 */

#if CHIP_CONFIG_ENABLE_CONDITION_LOGGING && !defined(ChipLogIfFalse)

#define ChipLogIfFalse(aCondition)                                                                                                 \
    do                                                                                                                             \
    {                                                                                                                              \
        if (!(aCondition))                                                                                                         \
        {                                                                                                                          \
            ChipLogError(NotSpecified, "Condition Failed (%s) at %s:%d", #aCondition, __FILE__, __LINE__);                         \
        }                                                                                                                          \
    } while (0)

#else // CHIP_CONFIG_ENABLE_CONDITION_LOGGING

#define ChipLogIfFalse(aCondition) IgnoreUnusedVariable(aCondition)

#endif // CHIP_CONFIG_ENABLE_CONDITION_LOGGING

/*
 *  @brief
 *      Macro for use in a string formatter for a 64-bit hex print.
 *      Will split into 2x 32-bit prints to support small printf libraries
 *
 *  Example Usage:
 *
 *  @code
 *  void foo() {
 *      uint64_t value = 0x1122334455667788;
 *      ChipLogProgress(Foo, "A 64-bit value: 0x" ChipLogFormatX64, ChipLogValueX64(value));
 *  }
 *  @endcode
 *
 */
#define ChipLogFormatX64 "%08" PRIX32 "%08" PRIX32

/*
 *  @brief
 *      Macro for use in a printf parameter list for a 64-bit value.
 *      Will split into MSB/LSB 32-bit values to use only 32-bit formatting.
 *
 *  Example Usage:
 *
 *  @code
 *  void foo() {
 *      uint64_t value = 0x1122334455667788;
 *      ChipLogProgress(Foo, "A 64-bit value: 0x" ChipLogFormatX64, ChipLogValueX64(value));
 *  }
 *  @endcode
 *
 *  @param[in]  aValue    64-bit value that will be split in 32-bit MSB/LSB part
 */
#define ChipLogValueX64(aValue) static_cast<uint32_t>(aValue >> 32), static_cast<uint32_t>(aValue)

/*
 *  @brief
 *      Macro for use in a string formatter for a MEI hex print.
 *      Will split into 2x 16-bit prints to display both the MEI prefix/suffix
 *
 *  Example Usage:
 *
 *  @code
 *  void foo() {
 *      chip::CommandId value = 0x12340001;
 *      ChipLogProgress(Foo, "A MEI value: " ChipLogFormatMEI, ChipLogValueMEI(value));
 *  }
 *  @endcode
 *
 */
#define ChipLogFormatMEI "0x%04" PRIX16 "_%04" PRIX16

/*
 *  @brief
 *      Macro for use in a printf parameter list for MEI value.
 *      Will split into MSB/LSB 16-bit values to separate prefix/suffix.
 *
 *  Example Usage:
 *
 *  @code
 *  void foo() {
 *      chip::CommandId value = 0x12340001;
 *      ChipLogProgress(Foo, "A MEI value: " ChipLogFormatMEI, ChipLogValueMEI(value));
 *  }
 *  @endcode
 *
 *  @param[in]  aValue    "32-bit value that will be split in 16-bit MSB/LSB part
 */
#define ChipLogValueMEI(aValue) static_cast<uint16_t>(aValue >> 16), static_cast<uint16_t>(aValue)

/**
 * Logging helpers for exchanges.  For now just log the exchange id and whether
 * it's an initiator or responder, but eventually we may want to log the peer
 * node id as well (especially for the responder case).  Some callsites only
 * have the exchange id and initiator/responder boolean, not an actual exchange,
 * so we want to have a helper for that case too.
 */
#define ChipLogFormatExchangeId "%" PRIu16 "%c"
#define ChipLogValueExchangeId(id, isInitiator) id, ((isInitiator) ? 'i' : 'r')
#define ChipLogFormatExchange ChipLogFormatExchangeId
#define ChipLogValueExchange(ec) ChipLogValueExchangeId((ec)->GetExchangeId(), (ec)->IsInitiator())
#define ChipLogValueExchangeIdFromSentHeader(payloadHeader)                                                                        \
    ChipLogValueExchangeId((payloadHeader).GetExchangeID(), (payloadHeader).IsInitiator())
// A received header's initiator boolean is the inverse of the exchange's.
#define ChipLogValueExchangeIdFromReceivedHeader(payloadHeader)                                                                    \
    ChipLogValueExchangeId((payloadHeader).GetExchangeID(), !(payloadHeader).IsInitiator())

/**
 * Logging helpers for protocol ids.  A protocol id is a (vendor-id,
 * protocol-id) pair.
 */
#define ChipLogFormatProtocolId "(%" PRIu16 ", %" PRIu16 ")"
#define ChipLogValueProtocolId(id) (id).GetVendorId(), (id).GetProtocolId()

/**
 * Logging helpers for message counters, so we format them consistently.
 */
#define ChipLogFormatMessageCounter "%" PRIu32

/**
 * Logging helpers for message types, so we format them consistently.
 */
#define ChipLogFormatMessageType "0x%" PRIx8

} // namespace Logging
} // namespace chip
