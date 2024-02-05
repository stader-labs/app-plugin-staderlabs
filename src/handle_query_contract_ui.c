#include <stdbool.h>
#include "staderlabs_plugin.h"

static bool set_native_token_stake_ui(ethQueryContractUI_t *msg, context_t *context) {
    strlcpy(msg->title, "Stake", msg->titleLength);

    const uint8_t *native_token_amount = msg->pluginSharedRO->txContent->value.value;
    uint8_t native_token_amount_size = msg->pluginSharedRO->txContent->value.length;

    if (memcmp(msg->network_ticker, "FTM", 3) == 0) {
        context->ticker = "FTM";
    }

    // Converts the uint256 number located in `native_token_amount` to its string representation and
    // copies this to `msg->msg`.
    return amountToString(native_token_amount,
                          native_token_amount_size,
                          WEI_TO_ETHER,
                          context->ticker,
                          msg->msg,
                          msg->msgLength);
}

static bool set_stake_ui(ethQueryContractUI_t *msg, const context_t *context) {
    strlcpy(msg->title, "Stake", msg->titleLength);

    return amountToString(context->amount_received,
                          sizeof(context->amount_received),
                          WEI_TO_ETHER,
                          context->ticker,
                          msg->msg,
                          msg->msgLength);
}

static bool set_unstake_ui(ethQueryContractUI_t *msg, context_t *context) {
    strlcpy(msg->title, "Unstake", msg->titleLength);

    char bsc_ticker[MAX_TICKER_LEN] = "BNB";
    if (memcmp(msg->network_ticker, bsc_ticker, 3) == 0) {
        context->ticker = "BNBX";
    }

    return amountToString(context->amount_received,
                          sizeof(context->amount_received),
                          WEI_TO_ETHER,
                          context->ticker,
                          msg->msg,
                          msg->msgLength);
}

static bool set_claim_ui(ethQueryContractUI_t *msg, const context_t *context) {
    strlcpy(msg->title, "Claim", msg->titleLength);
    strlcpy(msg->msg, context->ticker, msg->msgLength);
    return true;
}

static bool set_account_addr_ui(ethQueryContractUI_t *msg, context_t *context) {
    // Prefix the address with `0x`.
    msg->msg[0] = '0';
    msg->msg[1] = 'x';

    // We need a random chainID for legacy reasons with `getEthAddressStringFromBinary`.
    // Setting it to `0` means it works with any chainID :)
    uint64_t chainid = 0;

    // Get the string format of the address stored in `context->beneficiary`. Store it in
    // `msg->msg`.
    return getEthAddressStringFromBinary(
        context->account_addr,
        (char *) msg->msg + 2,      // +2 because we've already prefixed with '0x'.
        msg->pluginSharedRW->sha3,  // Used by the function to calculate the hash
        chainid);
}

static bool handle_ethx_deposit(ethQueryContractUI_t *msg, context_t *context) {
    bool ret = false;

    memset(msg->title, 0, msg->titleLength);
    memset(msg->msg, 0, msg->msgLength);

    switch (msg->screenIndex) {
        case 0:
            ret = set_native_token_stake_ui(msg, context);
            break;
        case 1:
            strlcpy(msg->title, "Receiver", msg->titleLength);
            ret = set_account_addr_ui(msg, context);
            break;

        default:
            PRINTF("Received an invalid screenIndex\n");
    }
    return ret;
}

static bool handle_ethx_request_withdraw(ethQueryContractUI_t *msg, context_t *context) {
    bool ret = false;

    memset(msg->title, 0, msg->titleLength);
    memset(msg->msg, 0, msg->msgLength);
    switch (msg->screenIndex) {
        case 0:
            ret = set_unstake_ui(msg, context);
            break;
        case 1:
            strlcpy(msg->title, "Receiver", msg->titleLength);
            ret = set_account_addr_ui(msg, context);
            break;

        default:
            PRINTF("Received an invalid screenIndex\n");
    }
    return ret;
}

static bool handle_boost_rewards_claim(ethQueryContractUI_t *msg, context_t *context) {
    bool ret = false;

    memset(msg->title, 0, msg->titleLength);
    memset(msg->msg, 0, msg->msgLength);
    switch (msg->screenIndex) {
        case 0:
            ret = set_stake_ui(msg, context);  // sets title to "Stake" and msg to token amount
            strlcpy(msg->title, "Claim", msg->titleLength);  // update the title to "Claim"
            break;
        case 1:
            strlcpy(msg->title, "Receiver", msg->titleLength);
            ret = set_account_addr_ui(msg, context);
            break;

        default:
            PRINTF("Received an invalid screenIndex\n");
    }
    return ret;
}

void handle_query_contract_ui(ethQueryContractUI_t *msg) {
    context_t *context = (context_t *) msg->pluginContext;
    bool ret = false;

    // msg->title is the upper line displayed on the device.
    // msg->msg is the lower line displayed on the device.

    // Clean the display fields.
    memset(msg->title, 0, msg->titleLength);
    memset(msg->msg, 0, msg->msgLength);

    switch (context->selectorIndex) {
        case ETH_MATICX_SUBMIT:
            ret = set_stake_ui(msg, context);
            break;

        case ETH_MATICX_REQUEST_WITHDRAW:
        case POLYGON_CHILDPOOL_REQUEST_MATICX_SWAP:
        case BSC_STAKEMANAGER_REQUEST_WITHDRAW:
        case FTM_UNDELEGATE:
            ret = set_unstake_ui(msg, context);
            break;

        case ETHX_CLAIM:
        case ETH_MATICX_CLAIM_WITHDRAWAL:
        case POLYGON_CHILDPOOL_CLAIM_MATICX_SWAP:
        case BSC_STAKEMANAGER_CLAIM_WITHDRAW:
        case FTM_WITHDRAW:
            ret = set_claim_ui(msg, context);
            break;

        case POLYGON_CHILDPOOL_SWAP_MATIC_FOR_MATICX_VIA_INSTANT_POOL:
        case BSC_STAKEMANAGER_DEPOSIT:
        case FTM_DEPOSIT:
            ret = set_native_token_stake_ui(msg, context);
            break;

        case ETHX_DEPOSIT:
        case ETHX_DEPOSIT_LEGACY:
            ret = handle_ethx_deposit(msg, context);
            break;

        case ETHX_REQUEST_WITHDRAW:
        case ETHX_REQUEST_WITHDRAW_LEGACY:
            ret = handle_ethx_request_withdraw(msg, context);
            break;

        case ETHX_BOOST_REWARDS_CLAIM:
            ret = handle_boost_rewards_claim(msg, context);
            break;

        default:
            PRINTF("Selector index: %d not supported\n", context->selectorIndex);
    }
    msg->result = ret ? ETH_PLUGIN_RESULT_OK : ETH_PLUGIN_RESULT_ERROR;
}
