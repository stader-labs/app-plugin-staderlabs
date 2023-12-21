#include "staderlabs_plugin.h"

// Copy amount sent parameter to amount_received
static void handle_amount_received(const ethPluginProvideParameter_t *msg, context_t *context) {
    copy_parameter(context->amount_received, msg->parameter, sizeof(context->amount_received));
}

static void handle_unsupported_param(ethPluginProvideParameter_t *msg) {
#ifdef DEBUG
    context_t *context = (context_t *) msg->pluginContext;
    PRINTF("Param not supported: %d\n", context->next_param);
#endif

    msg->result = ETH_PLUGIN_RESULT_ERROR;
}

// EDIT THIS: Remove this function and write your own handlers!
static void handle_stake(ethPluginProvideParameter_t *msg, context_t *context) {
    switch (context->next_param) {
        case STAKE_AMOUNT:
            handle_amount_received(msg, context);
            context->next_param = UNEXPECTED_PARAMETER;
            break;
        // Keep this
        default:
            handle_unsupported_param(msg);
            break;
    }
}

static void handle_unstake(ethPluginProvideParameter_t *msg, context_t *context) {
    if (context->skip_next_param) {  // this is currently only useful in ftm_undelegate
        context->skip_next_param = false;
        return;
    }

    switch (context->next_param) {
        case UNSTAKE_AMOUNT:
            handle_amount_received(msg, context);
            context->skip_next_param = true;
            break;
        // Keep this
        default:
            handle_unsupported_param(msg);
            break;
    }
}

static void handle_ethx_deposit(ethPluginProvideParameter_t *msg, context_t *context) {
    if (context->skip_next_param) {
        return;
    }
    switch (context->next_param) {
        case ACCOUNT_ADDR:
            copy_address(context->account_addr, msg->parameter, sizeof(context->account_addr));
            context->next_param = UNEXPECTED_PARAMETER;
            context->skip_next_param = true;
            break;

        // Keep this
        default:
            handle_unsupported_param(msg);
            break;
    }
}

static void handle_ethx_request_withdraw(ethPluginProvideParameter_t *msg, context_t *context) {
    if (context->skip_next_param) {
        return;
    }
    switch (context->next_param) {
        case UNSTAKE_AMOUNT:
            handle_amount_received(msg, context);
            context->next_param = ACCOUNT_ADDR;
            break;

        case ACCOUNT_ADDR:
            copy_address(context->account_addr, msg->parameter, sizeof(context->account_addr));
            context->next_param = UNEXPECTED_PARAMETER;
            context->skip_next_param = true;
            break;

        // Keep this
        default:
            handle_unsupported_param(msg);
            break;
    }
}

static void handle_boost_rewards_claim(ethPluginProvideParameter_t *msg, context_t *context) {
    if (context->skip_next_param) {
        return;
    }
    switch (context->next_param) {
        case UNUSED_PARAM:
            context->next_param = ACCOUNT_ADDR;
            break;
        case ACCOUNT_ADDR:
            copy_address(context->account_addr, msg->parameter, sizeof(context->account_addr));
            context->next_param = TOKEN_AMOUNT;
            break;

        case TOKEN_AMOUNT:
            handle_amount_received(msg, context);
            context->next_param = UNEXPECTED_PARAMETER;
            context->skip_next_param = true;
            break;

        // Keep this
        default:
            handle_unsupported_param(msg);
            break;
    }
}

void handle_provide_parameter(ethPluginProvideParameter_t *msg) {
    context_t *context = (context_t *) msg->pluginContext;
    // We use `%.*H`: it's a utility function to print bytes. You first give
    // the number of bytes you wish to print (in this case, `PARAMETER_LENGTH`) and then
    // the address (here `msg->parameter`).
    PRINTF("plugin provide parameter: offset %d\nBytes: %.*H\n",
           msg->parameterOffset,
           PARAMETER_LENGTH,
           msg->parameter);

    msg->result = ETH_PLUGIN_RESULT_OK;

    // EDIT THIS: adapt the cases and the names of the functions.
    switch (context->selectorIndex) {
        case ETHX_DEPOSIT_LEGACY:
        case ETHX_DEPOSIT:
            handle_ethx_deposit(msg, context);
            break;

        case ETHX_REQUEST_WITHDRAW_LEGACY:
        case ETHX_REQUEST_WITHDRAW:
            handle_ethx_request_withdraw(msg, context);
            break;

        case ETH_MATICX_SUBMIT:
            handle_stake(msg, context);
            break;

        case ETH_MATICX_REQUEST_WITHDRAW:
        case POLYGON_CHILDPOOL_REQUEST_MATICX_SWAP:
        case BSC_STAKEMANAGER_REQUEST_WITHDRAW:
        case FTM_UNDELEGATE:
            handle_unstake(msg, context);
            break;

        case ETHX_CLAIM:
        case ETH_MATICX_CLAIM_WITHDRAWAL:
        case POLYGON_CHILDPOOL_SWAP_MATIC_FOR_MATICX_VIA_INSTANT_POOL:
        case POLYGON_CHILDPOOL_CLAIM_MATICX_SWAP:
        case BSC_STAKEMANAGER_DEPOSIT:
        case FTM_DEPOSIT:
        case BSC_STAKEMANAGER_CLAIM_WITHDRAW:
        case FTM_WITHDRAW:
            context->next_param = UNEXPECTED_PARAMETER;
            break;

        case ETHX_BOOST_REWARDS_CLAIM:
            handle_boost_rewards_claim(msg, context);
            break;

        default:
            PRINTF("Selector Index not supported: %d\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}
