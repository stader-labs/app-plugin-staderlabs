#include "staderlabs_plugin.h"

static void set_stake_ui(ethQueryContractUI_t *msg, const context_t *context) {
    strlcpy(msg->title, "Stake", msg->titleLength);

    amountToString(context->amount_received,
                   sizeof(context->amount_received),
                   WEI_TO_ETHER,
                   context->ticker,
                   msg->msg,
                   msg->msgLength);
}

static void set_unstake_ui(ethQueryContractUI_t *msg, const context_t *context) {
    strlcpy(msg->title, "Unstake", msg->titleLength);

    amountToString(context->amount_received,
                   sizeof(context->amount_received),
                   WEI_TO_ETHER,
                   context->ticker,
                   msg->msg,
                   msg->msgLength);
}

void handle_query_contract_ui(void *parameters) {
    ethQueryContractUI_t *msg = (ethQueryContractUI_t *) parameters;
    context_t *context = (context_t *) msg->pluginContext;

    // msg->title is the upper line displayed on the device.
    // msg->msg is the lower line displayed on the device.

    // Clean the display fields.
    memset(msg->title, 0, msg->titleLength);
    memset(msg->msg, 0, msg->msgLength);

    // if value of screenIndex is not 0, then it is invalid as we require only one screen in all
    // methods
    if (msg->screenIndex) {
        PRINTF("Received an invalid screenIndex\n");
        msg->result = ETH_PLUGIN_RESULT_ERROR;
        return;
    }

    switch (context->selectorIndex) {
        case ETH_MATICX_SUBMIT:
            set_stake_ui(msg, context);
            break;

        case ETH_MATICX_REQUEST_WITHDRAW:
            set_unstake_ui(msg, context);
            break;

            // case ETH_MATICX_CLAIM_WITHDRAWAL:
            //     break;

        default:
            PRINTF("Selector index: %d not supported\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }
    msg->result = ETH_PLUGIN_RESULT_OK;
}
