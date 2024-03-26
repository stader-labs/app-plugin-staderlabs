#include "staderlabs_plugin.h"

void handle_finalize(ethPluginFinalize_t *msg) {
    context_t *context = (context_t *) msg->pluginContext;

    switch (context->selectorIndex) {
        case ETHX_DEPOSIT:
        case ETHX_DEPOSIT_LEGACY:
        case ETHX_REQUEST_WITHDRAW:
        case ETHX_REQUEST_WITHDRAW_LEGACY:
            msg->numScreens = 2;
            break;

        case KELP_LST_DEPOSIT:
            msg->numScreens = 1;
            msg->tokenLookup1 = context->token_addr;
            break;

        default:
            msg->numScreens = 1;
            break;
    }
    msg->uiType = ETH_UI_TYPE_GENERIC;

    msg->result = ETH_PLUGIN_RESULT_OK;
}
