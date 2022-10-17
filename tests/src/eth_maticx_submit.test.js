import "core-js/stable";
import "regenerator-runtime";
import {
  waitForAppScreen,
  zemu,
  genericTx,
  nano_models,
  SPECULOS_ADDRESS,
  txFromEtherscan,
} from "./test.fixture";
import { ethers } from "ethers";
import { parseEther, parseUnits } from "ethers/lib/utils";

const contractAddr = "0xf03a7eb46d01d9ecaa104558c732cf82f6b6b645";
const pluginName = "staderlabs";
const testNetwork = "ethereum";
const abi_path =
  `../networks/${testNetwork}/${pluginName}/abis/` + contractAddr + ".json";
const abi = require(abi_path);

// Test from replayed transaction: https://etherscan.io/tx/0x0160b3aec12fd08e6be0040616c7c38248efb4413168a3372fc4d2db0e5961bb
nano_models.forEach(function (model) {
  test(
    "[Nano " + model.letter + "] Submit Matic Tokens",
    zemu(model, async (sim, eth) => {
      // The rawTx of the tx up above is accessible through: https://etherscan.io/getRawTx?tx=0xb27a69cd3190ad0712da39f6b809ecc019ecbc319d3c17169853270226d18a8a
      const serializedTx = txFromEtherscan(
        "0x02f890012b8459682f008501e45cb83d8307229094f03a7eb46d01d9ecaa104558c732cf82f6b6b64580a4ea99c2a60000000000000000000000000000000000000000000000481591030b2a830000c080a059adbe59fe76966e72c711b1487063246f5997278af9f2c7924aa49a23a50aaaa03a9c651f564666a26faa3f8ab9235bfc4d9d62a804075944d314a105e2519a30"
      );

      const tx = eth.signTransaction("44'/60'/0'/0", serializedTx);

      const right_clicks = model.letter === "S" ? 5 : 4;

      // Wait for the application to actually load and parse the transaction
      await waitForAppScreen(sim);
      // Navigate the display by pressing the right button `right_clicks` times, then pressing both buttons to accept the transaction.
      await sim.navigateAndCompareSnapshots(".", model.name + "_stake_matic", [
        right_clicks,
        0,
      ]);

      await tx;
    })
  );
});
