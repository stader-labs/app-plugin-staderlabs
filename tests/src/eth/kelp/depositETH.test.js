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
// Test from replayed transaction: https://etherscan.io/tx/0x8a00de6dbc850f48e78b61a11c3061e3fc065507073921b8312bba9b4c713284
const inputData =
  "0x02f90138018083902d038509f5d5b7778307a4db94036676389e48133b63a802f8635ad39e752d375d880d0b8d0508de0000b8c472c51c0b000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000400000000000000000000000000000000000000000000000000000000000000042307836613137346533306162376238313262663631326462383932663038303634656364666161613638636166353034633330326630353236663066303930643836000000000000000000000000000000000000000000000000000000000000c080a0c451fdeb418249686444110516b6872489fdb57e5623e19e459a9f9dcb24487ba070a9fed5d2660b874f3b80bc14abb38d92863b1332c05dc9d11e6beb78d91034";

nano_models.forEach(function (model) {
  test(
    "[Nano " + model.letter + "] Deposit ETH",
    zemu(model, async (sim, eth) => {
      const serializedTx = txFromEtherscan(inputData);

      const tx = eth.signTransaction("44'/60'/0'/0", serializedTx);

      const right_clicks = model.letter === "S" ? 6 : 4;

      // Wait for the application to actually load and parse the transaction
      await waitForAppScreen(sim);
      // Navigate the display by pressing the right button `right_clicks` times, then pressing both buttons to accept the transaction.
      await sim.navigateAndCompareSnapshots(
        ".",
        testNetwork + "_kelp_" + model.name + "_deposit_eth",
        [right_clicks, 0]
      );

      await tx;
    }),
    50000
  );
});
