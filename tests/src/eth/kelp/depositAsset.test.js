import "core-js/stable";
import "regenerator-runtime";
import {
  waitForAppScreen,
  zemu,
  nano_models,
  serializeTx,
  txFromEtherscan,
} from "../../test.fixture";

const testNetwork = "ethereum";
// Test from replayed transaction: https://etherscan.io/tx/0xfc310710142f1d1b6da83ae7a74ccdc6e110b83b193c546ac74423b61d03cfd9
const inputData =
  "0x02f9015401820221850746f00bd9850746f00bd98307066094036676389e48133b63a802f8635ad39e752d375d80b8e4c3ae1766000000000000000000000000a35b1b31ce002fbf2058d22f30f95d405200a15b0000000000000000000000000000000000000000000000001b340783b0b8800000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000080000000000000000000000000000000000000000000000000000000000000004065313663623065316333353133303164333338656661343334656531646166336631393335386363633363666161643163386264323733663736633133313561c001a0aec13856dbebd5a5dd1cca745781942327cb6a279f6276a8ec19c3c402294cd1a035b6f92a682f56ae9187eb84c3340c15f69649fdbbe396b5eaf7d16bb2826503";

nano_models.forEach(function (model) {
  test(
    "[Nano " + model.letter + "] Deposit LST",
    zemu(model, async (sim, eth) => {
      const serializedTx = txFromEtherscan(inputData);

      const tx = eth.signTransaction("44'/60'/0'/0", serializedTx);

      const right_clicks = model.letter === "S" ? 6 : 4;

      // Wait for the application to actually load and parse the transaction
      await waitForAppScreen(sim);
      // Navigate the display by pressing the right button `right_clicks` times, then pressing both buttons to accept the transaction.
      await sim.navigateAndCompareSnapshots(
        ".",
        testNetwork + "_kelp_" + model.name + "_deposit_lst",
        [right_clicks, 0]
      );

      await tx;
    }),
    50000
  );
});
