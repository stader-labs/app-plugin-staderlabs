#include "staderlabs_plugin.h"

static int find_selector(uint32_t selector, const uint32_t *selectors, size_t n, selector_t *out) {
    for (selector_t i = 0; i < n; i++) {
        if (selector == selectors[i]) {
            *out = i;
            return 0;
        }
    }
    return -1;
}

// Called once to init.
void handle_init_contract(ethPluginInitContract_t *msg) {
    // Make sure we are running a compatible version.
    if (msg->interfaceVersion != ETH_PLUGIN_INTERFACE_VERSION_LATEST) {
        // If not the case, return the `UNAVAILABLE` status.
        msg->result = ETH_PLUGIN_RESULT_UNAVAILABLE;
        return;
    }

    // Double check that the `context_t` struct is not bigger than the maximum size (defined by
    // `msg->pluginContextLength`).
    if (msg->pluginContextLength < sizeof(context_t)) {
        PRINTF("Plugin parameters structure is bigger than allowed size\n");
        msg->result = ETH_PLUGIN_RESULT_ERROR;
        return;
    }

    context_t *context = (context_t *) msg->pluginContext;

    // Initialize the context (to 0).
    memset(context, 0, sizeof(*context));

    uint32_t selector = U4BE(msg->selector, 0);
    if (find_selector(selector, STADERLABS_SELECTORS, NUM_SELECTORS, &context->selectorIndex)) {
        msg->result = ETH_PLUGIN_RESULT_UNAVAILABLE;
        return;
    }

    // Set `next_param` to be the first field we expect to parse.
    // EDIT THIS: Adapt the `cases`, and set the `next_param` to be the first parameter you expect
    // to parse.
    switch (context->selectorIndex) {
        case ETHX_DEPOSIT_LEGACY:
        case ETHX_DEPOSIT:
            context->next_param = ACCOUNT_ADDR;
            context->ticker = "ETH";
            break;

        case ETHX_REQUEST_WITHDRAW_LEGACY:
        case ETHX_REQUEST_WITHDRAW:
            context->next_param = UNSTAKE_AMOUNT;
            context->ticker = "ETHX";
            break;

        case ETHX_CLAIM:
            context->next_param = UNEXPECTED_PARAMETER;
            context->ticker = "ETH";
            break;

        case ETH_MATICX_SUBMIT:
            context->next_param = STAKE_AMOUNT;
            context->ticker = "MATIC";
            break;

        case POLYGON_CHILDPOOL_SWAP_MATIC_FOR_MATICX_VIA_INSTANT_POOL:
            context->next_param = UNEXPECTED_PARAMETER;
            context->ticker = "MATIC";
            break;

        case BSC_STAKEMANAGER_DEPOSIT:
        // the below case is of no use, as the selector matches with `BSC_STAKEMANAGER_DEPOSIT`
        case FTM_DEPOSIT:
            context->next_param = UNEXPECTED_PARAMETER;
            context->ticker = "BNB";
            break;

        case ETH_MATICX_REQUEST_WITHDRAW:
        // the below case is of no use, as the selector matches with `ETH_MATICX_REQUEST_WITHDRAW`
        case BSC_STAKEMANAGER_REQUEST_WITHDRAW:
        case POLYGON_CHILDPOOL_REQUEST_MATICX_SWAP:
            context->next_param = UNSTAKE_AMOUNT;
            context->ticker = "MATICX";
            break;

        case FTM_UNDELEGATE:
            context->next_param = UNSTAKE_AMOUNT;
            context->ticker = "FTMX";
            context->skip_next_param = true;
            break;

        case ETH_MATICX_CLAIM_WITHDRAWAL:
        case POLYGON_CHILDPOOL_CLAIM_MATICX_SWAP:
            context->next_param = UNEXPECTED_PARAMETER;
            context->ticker = "MATIC";
            break;

        case BSC_STAKEMANAGER_CLAIM_WITHDRAW:
            context->next_param = UNEXPECTED_PARAMETER;
            context->ticker = "BNB";
            break;

        case FTM_WITHDRAW:
            context->next_param = UNEXPECTED_PARAMETER;
            context->ticker = "FTM";
            break;

        case ETHX_BOOST_REWARDS_CLAIM:
            context->next_param = UNUSED_PARAM;
            context->ticker = "SD";
            break;

        // Keep this
        default:
            PRINTF("Missing selectorIndex: %d\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }

    // Return valid status.
    msg->result = ETH_PLUGIN_RESULT_OK;
}
