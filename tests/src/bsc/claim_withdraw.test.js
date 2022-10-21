import "core-js/stable";
import "regenerator-runtime";
import {
  waitForAppScreen,
  zemu,
  nano_models,
  serializeTx,
} from "../test.fixture";

const contractAddr = "0x7276241a669489e4bbb76f63d2a43bfe63080f2f";
const pluginName = "staderlabs";
const testNetwork = "bsc";
const chainID = 56;
const signedPlugin = false;
// Test from replayed transaction: https://bscscan.com/tx/0xc4ee2488f8a2f06c7cb300477df51a5bbec1195fc12e6e20ca9c3cb18ffd5995
const inputData =
  "0xb13acedd0000000000000000000000000000000000000000000000000000000000000000";

nano_models.forEach(function (model) {
  test(
    "[Nano " + model.letter + "] Claim Withdraw BNB",
    zemu(
      model,
      async (sim, eth) => {
        const serializedTx = serializeTx(contractAddr, inputData, chainID);

        const tx = eth.signTransaction("44'/60'/0'/0/0", serializedTx);

        const right_clicks = model.letter === "S" ? 5 : 5;

        // Wait for the application to actually load and parse the transaction
        await waitForAppScreen(sim);
        // Navigate the display by pressing the right button `right_clicks` times, then pressing both buttons to accept the transaction.
        await sim.navigateAndCompareSnapshots(
          ".",
          testNetwork + "_bnbx_" + model.name + "_claim_withdraw_",
          [right_clicks, 0]
        );

        await tx;
      },
      signedPlugin,
      testNetwork
    )
  );
});
