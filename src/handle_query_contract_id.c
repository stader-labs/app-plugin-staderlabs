#include "staderlabs_plugin.h"

// Sets the first screen to display.
void handle_query_contract_id(ethQueryContractID_t *msg) {
    const context_t *context = (const context_t *) msg->pluginContext;
    // msg->name will be the upper sentence displayed on the screen.
    // msg->version will be the lower sentence displayed on the screen.

    // For the first screen, display the plugin name.
    strlcpy(msg->name, PLUGIN_NAME, msg->nameLength);
    const char *msgVersion;

    // EDIT THIS: Adapt the cases by modifying the strings you pass to `strlcpy`.
    switch (context->selectorIndex) {
        case ETHX_DEPOSIT:
        case ETHX_DEPOSIT_LEGACY:
        case ETH_MATICX_SUBMIT:
        case POLYGON_CHILDPOOL_SWAP_MATIC_FOR_MATICX_VIA_INSTANT_POOL:
        case BSC_STAKEMANAGER_DEPOSIT:
        case FTM_DEPOSIT:
            msgVersion = "Stake";
            break;

        case ETHX_REQUEST_WITHDRAW:
        case ETHX_REQUEST_WITHDRAW_LEGACY:
        case ETH_MATICX_REQUEST_WITHDRAW:
        case POLYGON_CHILDPOOL_REQUEST_MATICX_SWAP:
        case BSC_STAKEMANAGER_REQUEST_WITHDRAW:
        case FTM_UNDELEGATE:
            msgVersion = "Unstake";
            break;

        case ETHX_CLAIM:
        case ETH_MATICX_CLAIM_WITHDRAWAL:
        case POLYGON_CHILDPOOL_CLAIM_MATICX_SWAP:
        case BSC_STAKEMANAGER_CLAIM_WITHDRAW:
        case FTM_WITHDRAW:
            msgVersion = "Claim";
            break;

        case ETHX_BOOST_REWARDS_CLAIM:
            msgVersion = "Claim SD Rewards";
            break;

        default:
            PRINTF("Selector index: %d not supported\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }

    strlcpy(msg->version, msgVersion, msg->versionLength);
    msg->result = ETH_PLUGIN_RESULT_OK;
}
