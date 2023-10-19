import "core-js/stable";
import "regenerator-runtime";
import {
  waitForAppScreen,
  zemu,
  nano_models,
  serializeTx,
  txFromEtherscan,
} from "../../test.fixture";

const contractAddr = "0xcf5ea1b38380f6af39068375516daf40ed70d299";
const pluginName = "staderlabs";
const testNetwork = "ethereum";
const chainID = 1;
// Test from replayed transaction: https://etherscan.io/tx/0x4e771017864ff34176c8c9fa62fe1950852933345f921dc5316c63554c9bc453
const inputData =
  "0x02f8f701248405f5e1008501fa14a6d7830329eb94cf5ea1b38380f6af39068375516daf40ed70d299865af3107a4000b884b74825090000000000000000000000007e9bb9673ac38071a7699e6a3c48b8fbde574cd00000000000000000000000000000000000000000000000000000000000000040000000000000000000000000000000000000000000000000000000000000000a74657374696e6731323300000000000000000000000000000000000000000000c001a0e50fe06c37fda195c02ee64e359020fa135b7b2e9f9e4ffc12aa1b6430eda835a0732c210ac338e9ff2431c7f5076ce6cde517a6fa4d37a6339928e58e24d1a86f";

nano_models.forEach(function (model) {
  test(
    "[Nano " + model.letter + "] Deposit ETH",
    zemu(model, async (sim, eth) => {
      const serializedTx = txFromEtherscan(inputData);

      const tx = eth.signTransaction("44'/60'/0'/0", serializedTx);

      const right_clicks = model.letter === "S" ? 9 : 5;

      // Wait for the application to actually load and parse the transaction
      await waitForAppScreen(sim);
      // Navigate the display by pressing the right button `right_clicks` times, then pressing both buttons to accept the transaction.
      await sim.navigateAndCompareSnapshots(
        ".",
        testNetwork + "_ethx_" + model.name + "_stake_eth",
        [right_clicks, 0]
      );

      await tx;
    }),
    50000
  );
});
