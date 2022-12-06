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
// Test from replayed transaction: https://ftmscan.com/tx/0x60130f5baa43bfdad15b79f4ff573b081e9a2f69a64b6db839b7afc71df2903b
const inputData =
  "0x4f864df400000000000000000000000000000000000000000000000000011352faaba2bf00000000000000000000000000000000000000000000000ea00bf71b724f800000000000000000000000000000000000000000000000000f6eea29cfd81d7920";

nano_models.forEach(function (model) {
  test(
    "[Nano " + model.letter + "] Unstake FTM",
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
          testNetwork + "_ftmx_" + model.name + "_undelegate",
          [right_clicks, 0]
        );

        await tx;
      },
      signedPlugin,
      testNetwork
    )
  );
});
