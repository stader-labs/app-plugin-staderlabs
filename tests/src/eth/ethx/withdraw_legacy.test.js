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
// Test from replayed transaction: https://etherscan.io/tx/0xa7b2f78c84bc5528629d37b56856d47601c42f4d7f1505fa6767bcd090fb5044
const inputData =
  "0x02f8b30182059585053f837bd185053f837bd18304d7be949f0491b32dbce587c50c4c43ab303b06478193a780b844ccc143b80000000000000000000000000000000000000000000000056a30e2758fb0a40000000000000000000000000087bc2f2ba8c83f412fed5c3151de0ffbdc959984c080a01bf62d962c7e2d888df40f0a61dd9eb6c60ed01e1291ce15b9acbad154e0cf619fc470d4477df1e52cb4030e2f976dc13856d09010d164dd97a5532d59b9d413";

nano_models.forEach(function (model) {
  test(
    "[Nano " + model.letter + "] Legacy Request Withdraw ETH",
    zemu(model, async (sim, eth) => {
      const serializedTx = txFromEtherscan(inputData);

      const tx = eth.signTransaction("44'/60'/0'/0", serializedTx);

      const right_clicks = model.letter === "S" ? 9 : 5;

      // Wait for the application to actually load and parse the transaction
      await waitForAppScreen(sim);
      // Navigate the display by pressing the right button `right_clicks` times, then pressing both buttons to accept the transaction.
      await sim.navigateAndCompareSnapshots(
        ".",
        testNetwork + "_ethx_" + model.name + "_legacy_request_withdraw_eth",
        [right_clicks, 0]
      );

      await tx;
    }),
    50000
  );
});
