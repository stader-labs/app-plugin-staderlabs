import "core-js/stable";
import "regenerator-runtime";
import {
  waitForAppScreen,
  zemu,
  nano_models,
  serializeTx,
} from "../test.fixture";

const contractAddr = "0xb458bfc855ab504a8a327720fcef98886065529b";
const pluginName = "staderlabs";
const testNetwork = "fantom";
const chainID = 250;
const signedPlugin = false;
// Test from replayed transaction: https://ftmscan.com/tx/0x8b5cc5810f4cf8048413ff3f66c32d3c0175e6f159a5c8dce0ce1a2207effc25
const inputData =
  "0x441a3e70000000000000000000000000000000000000000000000000000325c5ddb1a21c0000000000000000000000000000000000000000000000000000000000000000";

nano_models.forEach(function (model) {
  test(
    "[Nano " + model.letter + "] Withdraw FTM",
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
          testNetwork + "_ftmx_" + model.name + "_withdraw",
          [right_clicks, 0]
        );

        await tx;
      },
      signedPlugin,
      testNetwork
    )
  );
});
