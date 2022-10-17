import "core-js/stable";
import "regenerator-runtime";
import {
  waitForAppScreen,
  zemu,
  nano_models,
  txFromEtherscan,
} from "./test.fixture";

const contractAddr = "0xf03a7eb46d01d9ecaa104558c732cf82f6b6b645";
const pluginName = "staderlabs";
const testNetwork = "ethereum";
const abi_path =
  `../networks/${testNetwork}/${pluginName}/abis/` + contractAddr + ".json";
const abi = require(abi_path);

// Test from replayed transaction: https://etherscan.io/tx/0x718110ca67a3f440195c388c16a1749e0d89877817d2d3e944365855f642145d
nano_models.forEach(function (model) {
  test(
    "[Nano " + model.letter + "] Unstake MaticX Tokens",
    zemu(model, async (sim, eth) => {
      // The rawTx of the tx up above is accessible through: https://etherscan.io/getRawTx?tx=0x718110ca67a3f440195c388c16a1749e0d89877817d2d3e944365855f642145d
      const serializedTx = txFromEtherscan(
        "0x02f890012c8459682f008501deb8635e8309c5c794f03a7eb46d01d9ecaa104558c732cf82f6b6b64580a4745400c9000000000000000000000000000000000000000000000045c41fde9b3d420000c001a020d9ed1733bdea2b2fc59f7b0e4037ede9f45b7992f25c5c996f1d7ede25313aa043b6a72566c01b2d2f8abbdd3824ea5fc0410ac728cc15f5bb5d01070df4d3ca"
      );

      const tx = eth.signTransaction("44'/60'/0'/0", serializedTx);

      const right_clicks = model.letter === "S" ? 6 : 4;

      // Wait for the application to actually load and parse the transaction
      await waitForAppScreen(sim);
      // Navigate the display by pressing the right button `right_clicks` times, then pressing both buttons to accept the transaction.
      await sim.navigateAndCompareSnapshots(
        ".",
        model.name + "_unstake_maticx",
        [right_clicks, 0]
      );

      await tx;
    })
  );
});
