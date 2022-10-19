import "core-js/stable";
import "regenerator-runtime";
import {
  waitForAppScreen,
  zemu,
  nano_models,
  txFromEtherscan,
} from "../../test.fixture";

const contractAddr = "0xf03a7eb46d01d9ecaa104558c732cf82f6b6b645";
const pluginName = "staderlabs";
const testNetwork = "ethereum";

// Test from replayed transaction: https://etherscan.io/tx/0xf3c639002557eafa1560159010093927560ebbb351720c279be67bd3c480d103
nano_models.forEach(function (model) {
  test(
    "[Nano " + model.letter + "] Claim Matic Tokens",
    zemu(model, async (sim, eth) => {
      // The rawTx of the tx up above is accessible through: https://etherscan.io/getRawTx?tx=0xf3c639002557eafa1560159010093927560ebbb351720c279be67bd3c480d103
      const serializedTx = txFromEtherscan(
        "0x02f89001078459682f008505a6d71662830307bc94f03a7eb46d01d9ecaa104558c732cf82f6b6b64580a4f84444360000000000000000000000000000000000000000000000000000000000000000c080a01dae94162970e34ff707029d274c8ab57841d80d0b374f3983b63e20d095e9f5a00ade1769548658f2a1065d6b963f49627b7cc701cb6bdcc98a7940f1b6ba5f96"
      );

      const tx = eth.signTransaction("44'/60'/0'/0", serializedTx);

      const right_clicks = model.letter === "S" ? 6 : 4;

      // Wait for the application to actually load and parse the transaction
      await waitForAppScreen(sim);
      // Navigate the display by pressing the right button `right_clicks` times, then pressing both buttons to accept the transaction.
      await sim.navigateAndCompareSnapshots(
        ".",
        testNetwork + "_maticx_" + model.name + "_claim_matic",
        [right_clicks, 0]
      );

      await tx;
    })
  );
});
