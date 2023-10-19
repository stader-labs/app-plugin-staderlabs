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
  "0x02f9011101278405f5e100850202345eaa8306d1d9949f0491b32dbce587c50c4c43ab303b06478193a780b8a41f7ec12200000000000000000000000000000000000000000000000000005af3107a40000000000000000000000000007e9bb9673ac38071a7699e6a3c48b8fbde574cd00000000000000000000000000000000000000000000000000000000000000060000000000000000000000000000000000000000000000000000000000000000a74657374696e6731323300000000000000000000000000000000000000000000c080a0908adc7cdbe3110e6353592e11da106ec8ba4ca7172a1641058cb7bb26c5acefa07035284a6a0ef6f98708a30f498ac1ace86bafb8294683b4000cb638ad7beba1";

nano_models.forEach(function (model) {
  test(
    "[Nano " + model.letter + "] Request Withdraw ETH",
    zemu(model, async (sim, eth) => {
      const serializedTx = txFromEtherscan(inputData);

      const tx = eth.signTransaction("44'/60'/0'/0", serializedTx);

      const right_clicks = model.letter === "S" ? 9 : 5;

      // Wait for the application to actually load and parse the transaction
      await waitForAppScreen(sim);
      // Navigate the display by pressing the right button `right_clicks` times, then pressing both buttons to accept the transaction.
      await sim.navigateAndCompareSnapshots(
        ".",
        testNetwork + "_ethx_" + model.name + "_request_withdraw_eth",
        [right_clicks, 0]
      );

      await tx;
    }),
    50000
  );
});
