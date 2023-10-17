#include "staderlabs_plugin.h"

void handle_finalize(ethPluginFinalize_t *msg) {
    context_t *context = (context_t *) msg->pluginContext;

    switch (context->selectorIndex) {
        case ETHX_DEPOSIT:
        case ETHX_REQUEST_WITHDRAW:
            msg->numScreens = 2;
            break;

        default:
            msg->numScreens = 1;
            break;
    }
    msg->uiType = ETH_UI_TYPE_GENERIC;

    msg->result = ETH_PLUGIN_RESULT_OK;
}
