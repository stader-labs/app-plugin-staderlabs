#pragma once

#include "eth_internals.h"
#include "eth_plugin_interface.h"
#include <string.h>

// Number of selectors defined in this plugin. Should match the enum `selector_t`.
#define NUM_SELECTORS 18

// Name of the plugin.
#define PLUGIN_NAME "Staderlabs"

// Enumeration of the different selectors possible.
// Should follow the exact same order as the array declared in main.c
typedef enum {
    ETH_MATICX_SUBMIT = 0,
    ETH_MATICX_REQUEST_WITHDRAW,
    ETH_MATICX_CLAIM_WITHDRAWAL,
    POLYGON_CHILDPOOL_SWAP_MATIC_FOR_MATICX_VIA_INSTANT_POOL,
    POLYGON_CHILDPOOL_REQUEST_MATICX_SWAP,
    POLYGON_CHILDPOOL_CLAIM_MATICX_SWAP,
    BSC_STAKEMANAGER_DEPOSIT,
    BSC_STAKEMANAGER_REQUEST_WITHDRAW,
    BSC_STAKEMANAGER_CLAIM_WITHDRAW,
    FTM_DEPOSIT,
    FTM_UNDELEGATE,
    FTM_WITHDRAW,
    ETHX_DEPOSIT,
    ETHX_REQUEST_WITHDRAW,
    ETHX_CLAIM,
    ETHX_DEPOSIT_LEGACY,
    ETHX_REQUEST_WITHDRAW_LEGACY,
    ETHX_BOOST_REWARDS_CLAIM,
} selector_t;

// Enumeration used to parse the smart contract data.
typedef enum {
    STAKE_AMOUNT = 0,
    UNSTAKE_AMOUNT,
    TOKEN_AMOUNT,
    ACCOUNT_ADDR,
    UNUSED_PARAM,
    UNEXPECTED_PARAMETER,
} parameter;

extern const uint32_t STADERLABS_SELECTORS[NUM_SELECTORS];

// Shared global memory with Ethereum app. Must be at most 5 * 32 bytes.
typedef struct context_t {
    // For display.
    uint8_t amount_received[INT256_LENGTH];  // 32 bytes
    const char *ticker;                      // 8 bytes
    uint8_t account_addr[ADDRESS_LENGTH];    // 20 bytes

    // For parsing data.
    uint8_t next_param;    // Set to be the next param we expect to parse. // 1 byte
    bool skip_next_param;  // flag to skip next param while parsing. // 1 byte

    // For both parsing and display.
    selector_t selectorIndex;  // 8 bytes
} context_t;

// Piece of code that will check that the above structure is not bigger than 5 * 32. Do not remove
// this check.
_Static_assert(sizeof(context_t) <= 5 * 32, "Structure of parameters too big.");
