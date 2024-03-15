/*******************************************************************************
 *   Plugin Staderlabs
 *   (c) 2023 Ledger
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 ********************************************************************************/

#pragma once

#include <string.h>
#include "eth_plugin_interface.h"

// All possible selectors of your plugin.
// EDIT THIS: Enter your selectors here, in the format X(NAME, value)
// A Xmacro below will create for you:
//     - an enum named selector_t with every NAME
//     - a map named SELECTORS associating each NAME with it's value
#define SELECTORS_LIST(X)                                                   \
    X(ETH_MATICX_SUBMIT, 0xea99c2a6)                                        \
    X(ETH_MATICX_REQUEST_WITHDRAW, 0x745400c9)                              \
    X(ETH_MATICX_CLAIM_WITHDRAWAL, 0xf8444436)                              \
    X(POLYGON_CHILDPOOL_SWAP_MATIC_FOR_MATICX_VIA_INSTANT_POOL, 0xc78cf1a0) \
    X(POLYGON_CHILDPOOL_REQUEST_MATICX_SWAP, 0x48eaf6d6)                    \
    X(POLYGON_CHILDPOOL_CLAIM_MATICX_SWAP, 0x77baf209)                      \
    X(BSC_STAKEMANAGER_DEPOSIT, 0xd0e30db0)                                 \
    X(BSC_STAKEMANAGER_REQUEST_WITHDRAW, 0x745400c9)                        \
    X(BSC_STAKEMANAGER_CLAIM_WITHDRAW, 0xb13acedd)                          \
    X(FTM_DEPOSIT, 0xd0e30db0)                                              \
    X(FTM_UNDELEGATE, 0x4f864df4)                                           \
    X(FTM_WITHDRAW, 0x441a3e70)                                             \
    X(ETHX_DEPOSIT, 0xb7482509)                                             \
    X(ETHX_REQUEST_WITHDRAW, 0x1f7ec122)                                    \
    X(ETHX_CLAIM, 0x379607f5)                                               \
    X(ETHX_DEPOSIT_LEGACY, 0xf340fa01)                                      \
    X(ETHX_REQUEST_WITHDRAW_LEGACY, 0xccc143b8)

// Xmacro helpers to define the enum and map
// Do not modify !
#define TO_ENUM(selector_name, selector_id)  selector_name,
#define TO_VALUE(selector_name, selector_id) selector_id,

// This enum will be automatically expanded to hold all selector names.
// The value SELECTOR_COUNT can be used to get the number of defined selectors
// Do not modify !
typedef enum selector_e {
    SELECTORS_LIST(TO_ENUM) SELECTOR_COUNT,
} selector_t;

// This array will be automatically expanded to map all selector_t names with the correct value.
// Do not modify !
extern const uint32_t SELECTORS[SELECTOR_COUNT];

// Enumeration used to parse the smart contract data.
// EDIT THIS: Adapt the parameter names here.
typedef enum {
    STAKE_AMOUNT = 0,
    UNSTAKE_AMOUNT,
    ACCOUNT_ADDR,
    UNEXPECTED_PARAMETER,
} parameter;

// Shared global memory with Ethereum app. Must be at most 5 * 32 bytes.
// EDIT THIS: This struct is used by your plugin to save the parameters you parse. You
// will need to adapt this struct to your plugin.
typedef struct context_s {
    // For display.
    uint8_t amount_received[INT256_LENGTH];
    const char *ticker;
    uint8_t account_addr[ADDRESS_LENGTH];

    // For parsing data.
    uint8_t next_param;    // Set to be the next param we expect to parse.
    bool skip_next_param;  // flag to skip next param while parsing.

    // For both parsing and display.
    selector_t selectorIndex;
} context_t;

// Check if the context structure will fit in the RAM section ETH will prepare for us
// Do not remove!
ASSERT_SIZEOF_PLUGIN_CONTEXT(context_t);