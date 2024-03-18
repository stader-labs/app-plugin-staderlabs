#include "plugin_utils.h"
#include "staderlabs_plugin.h"

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

    size_t index;
    if (!find_selector(U4BE(msg->selector, 0), SELECTORS, SELECTOR_COUNT, &index)) {
        PRINTF("Error: selector not found!\n");
        msg->result = ETH_PLUGIN_RESULT_UNAVAILABLE;
        return;
    }
    context->selectorIndex = index;
    // check for overflow
    if ((size_t) context->selectorIndex != index) {
        PRINTF("Error: overflow detected on selector index!\n");
        msg->result = ETH_PLUGIN_RESULT_ERROR;
        return;
    }

    // Set `next_param` to be the first field we expect to parse.
    // EDIT THIS: Adapt the `cases`, and set the `next_param` to be the first parameter you expect
    // to parse.
    switch (context->selectorIndex) {
        case ETHX_DEPOSIT_LEGACY:
        case ETHX_DEPOSIT:
            context->next_param = ACCOUNT_ADDR;
            break;

        case ETHX_REQUEST_WITHDRAW_LEGACY:
        case ETHX_REQUEST_WITHDRAW:
            context->next_param = UNSTAKE_AMOUNT;
            strlcpy(context->ticker, "ETHX", sizeof(context->ticker));
            break;

        case ETHX_CLAIM:
            context->next_param = UNEXPECTED_PARAMETER;
            strlcpy(context->ticker, "ETH", sizeof(context->ticker));
            break;

        case ETH_MATICX_SUBMIT:
            context->next_param = STAKE_AMOUNT;
            strlcpy(context->ticker, "MATIC", sizeof(context->ticker));
            break;

        case POLYGON_CHILDPOOL_SWAP_MATIC_FOR_MATICX_VIA_INSTANT_POOL:
            context->next_param = UNEXPECTED_PARAMETER;
            break;

        case BSC_STAKEMANAGER_DEPOSIT:
            // case FTM_DEPOSIT: // the selector matches with `BSC_STAKEMANAGER_DEPOSIT`
            context->next_param = UNEXPECTED_PARAMETER;
            break;

        case ETH_MATICX_REQUEST_WITHDRAW:
        // case BSC_STAKEMANAGER_REQUEST_WITHDRAW:
        // the selector matches with `ETH_MATICX_REQUEST_WITHDRAW`
        case POLYGON_CHILDPOOL_REQUEST_MATICX_SWAP:
            context->next_param = UNSTAKE_AMOUNT;
            strlcpy(context->ticker, "MATICX", sizeof(context->ticker));
            break;

        case FTM_UNDELEGATE:
            context->next_param = UNSTAKE_AMOUNT;
            strlcpy(context->ticker, "FTMX", sizeof(context->ticker));
            context->skip_next_param = true;
            break;

        case ETH_MATICX_CLAIM_WITHDRAWAL:
        case POLYGON_CHILDPOOL_CLAIM_MATICX_SWAP:
            context->next_param = UNEXPECTED_PARAMETER;
            strlcpy(context->ticker, "MATIC", sizeof(context->ticker));
            break;

        case BSC_STAKEMANAGER_CLAIM_WITHDRAW:
            context->next_param = UNEXPECTED_PARAMETER;
            strlcpy(context->ticker, "BNB", sizeof(context->ticker));
            break;

        case FTM_WITHDRAW:
            context->next_param = UNEXPECTED_PARAMETER;
            strlcpy(context->ticker, "FTM", sizeof(context->ticker));
            break;

        case KELP_LST_DEPOSIT:
            context->next_param = TOKEN_ADDR;
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
