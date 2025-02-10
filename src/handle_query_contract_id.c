#include "plugin.h"

// Sets the first screen to display.
void handle_query_contract_id(ethQueryContractID_t *msg) {
    const context_t *context = (const context_t *) msg->pluginContext;
    // msg->name will be the upper sentence displayed on the screen.
    // msg->version will be the lower sentence displayed on the screen.

    // For the first screen, display the plugin name.
    strlcpy(msg->name, APPNAME, msg->nameLength);
    const char *msgVersion;

    // EDIT THIS: Adapt the cases by modifying the strings you pass to `strlcpy`.
    switch (context->selectorIndex) {
        case ETHX_DEPOSIT:
        case ETH_MATICX_SUBMIT:
        case ETH_MATICX_SUBMIT_POL:
        case POLYGON_CHILDPOOL_SWAP_MATIC_FOR_MATICX_VIA_INSTANT_POOL:
        case BSC_STAKEMANAGER_DEPOSIT:
            msgVersion = "Stake";
            break;

        case BSC_STAKEMANAGER_REQUEST_WITHDRAW:
        case ETHX_REQUEST_WITHDRAW:
        case ETH_MATICX_REQUEST_WITHDRAW:
        case POLYGON_CHILDPOOL_REQUEST_MATICX_SWAP:
            msgVersion = "Unstake";
            break;

        case ETHX_CLAIM:
        case ETH_MATICX_CLAIM_WITHDRAWAL:
        // case BSC_STAKEMANAGER_CLAIM_WITHDRAW:
        // selector is same as ETH_MATICX_CLAIM_WITHDRAWAL
        case POLYGON_CHILDPOOL_CLAIM_MATICX_SWAP:
            msgVersion = "Claim";
            break;

        case KELP_LST_DEPOSIT:
            strlcpy(msg->name, "Kelp", msg->nameLength);
            msgVersion = "LST Restake";
            break;
        case KELP_ETH_DEPOSIT:
            strlcpy(msg->name, "Kelp", msg->nameLength);
            msgVersion = "Native Restake";
            break;

        case KELP_INITIATE_WITHDRAW:
            strlcpy(msg->name, "Kelp", msg->nameLength);
            msgVersion = "Unstake";
            break;

        case KELP_CLAIM_WITHDRAW:
            strlcpy(msg->name, "Kelp", msg->nameLength);
            msgVersion = "Claim";
            break;

        default:
            PRINTF("Selector index: %d not supported\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }

    strlcpy(msg->version, msgVersion, msg->versionLength);
    msg->result = ETH_PLUGIN_RESULT_OK;
}
