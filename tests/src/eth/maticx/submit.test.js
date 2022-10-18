import "core-js/stable";
import "regenerator-runtime";
import {
  waitForAppScreen,
  zemu,
  nano_models,
  serializeTx,
  txFromEtherscan,
} from "../../test.fixture";

const contractAddr = "0xf03a7eb46d01d9ecaa104558c732cf82f6b6b645";
const pluginName = "staderlabs";
const testNetwork = "ethereum";
const chainID = 1;
// Test from replayed transaction: https://etherscan.io/tx/0x92f606f3ab623de706e4a1a2bfdcfa95d07f071f2f3aacfc729aefa6b3c6d94c
const inputData =
  "0x02f890012b8459682f008501e45cb83d8307229094f03a7eb46d01d9ecaa104558c732cf82f6b6b64580a4ea99c2a60000000000000000000000000000000000000000000000481591030b2a830000c080a059adbe59fe76966e72c711b1487063246f5997278af9f2c7924aa49a23a50aaaa03a9c651f564666a26faa3f8ab9235bfc4d9d62a804075944d314a105e2519a30";

nano_models.forEach(function (model) {
  test(
    "[Nano " + model.letter + "] Submit Matic Tokens",
    zemu(model, async (sim, eth) => {
      const serializedTx = txFromEtherscan(inputData);

      const tx = eth.signTransaction("44'/60'/0'/0", serializedTx);

      const right_clicks = model.letter === "S" ? 5 : 4;

      // Wait for the application to actually load and parse the transaction
      await waitForAppScreen(sim);
      // Navigate the display by pressing the right button `right_clicks` times, then pressing both buttons to accept the transaction.
      await sim.navigateAndCompareSnapshots(
        ".",
        testNetwork + "_maticx_" + model.name + "_stake_matic",
        [right_clicks, 0]
      );

      await tx;
    })
  );
});
