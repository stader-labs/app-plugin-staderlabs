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
// Test from replayed transaction: https://ftmscan.com/tx/0xe3a07a16873a19be351cacb1c48f7fe23c4b2975ba774e71b26c4992afca1ac0
// msg.value is hardcoded, hence it will be wrong in test
const inputData = "0xd0e30db0";

nano_models.forEach(function (model) {
  test(
    "[Nano " + model.letter + "] Deposit FTM",
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
          testNetwork + "_ftmx_" + model.name + "_deposit",
          [right_clicks, 0]
        );

        await tx;
      },
      signedPlugin,
      testNetwork
    ),
    20000
  );
});
