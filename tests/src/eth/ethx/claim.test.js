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
// Test from replayed transaction: https://etherscan.io/tx/0x6a9c6ec076057ece2cd2201376e889fd58aed440ced33b769e78f86d0043a9a5
const inputData =
  "0x02f8910156850680edd7ec850680edd7ec83015d09949f0491b32dbce587c50c4c43ab303b06478193a780a4379607f50000000000000000000000000000000000000000000000000000000000000042c080a0ef4bce4226c5f12be27b95257456c6f51268d46a4d34c5eee583dbe41266fb51a02ca1ee59d5ddfd731edeccc0599e6f76a9012420412c98008cd05bdc3bf52668";

nano_models.forEach(function (model) {
  test(
    "[Nano " + model.letter + "] Claim ETH",
    zemu(model, async (sim, eth) => {
      const serializedTx = txFromEtherscan(inputData);

      const tx = eth.signTransaction("44'/60'/0'/0", serializedTx);

      const right_clicks = model.letter === "S" ? 6 : 4;

      // Wait for the application to actually load and parse the transaction
      await waitForAppScreen(sim);
      // Navigate the display by pressing the right button `right_clicks` times, then pressing both buttons to accept the transaction.
      await sim.navigateAndCompareSnapshots(
        ".",
        testNetwork + "_ethx_" + model.name + "_claim_eth",
        [right_clicks, 0]
      );

      await tx;
    })
  );
});
