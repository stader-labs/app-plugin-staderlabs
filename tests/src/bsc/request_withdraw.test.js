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
// Test from replayed transaction: https://bscscan.com/tx/0x1babe8a1c9fd2cfffb71bee4eaf4c99e38a35d59d526a52d32c4f25780866257
const inputData =
  "0x745400c900000000000000000000000000000000000000000000000050232527c77e4000";

nano_models.forEach(function (model) {
  test(
    "[Nano " + model.letter + "] Request Withdraw BNBx",
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
          testNetwork + "_bnbx_" + model.name + "_request_withdraw_",
          [right_clicks, 0]
        );

        await tx;
      },
      signedPlugin,
      testNetwork
    )
  );
});
