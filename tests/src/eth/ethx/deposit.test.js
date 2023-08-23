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
  "0x02f8980113850550de54dd850550de54dd8301c88a94cf5ea1b38380f6af39068375516daf40ed70d29987038d7ea4c68000a4f340fa01000000000000000000000000ad345b348bd84a4b42a5fde63feb7a29ef2af4e9c080a0a3adf22f4ce9fead664befb0ca33730f3bb8edb1a1d65a7f5275ac9a8622d29ea01a99e171740d723ee61049d7f0465f4e219fca86aaddf06bab02d3400f554242";

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
