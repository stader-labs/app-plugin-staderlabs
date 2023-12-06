import "core-js/stable";
import "regenerator-runtime";
import {
  waitForAppScreen,
  zemu,
  nano_models,
  txFromEtherscan,
} from "../../test.fixture";

const testNetwork = "ethereum";
// Test from replayed transaction: https://etherscan.io/tx/0xaa727fb8dedae3be35067d07d0833729594e82598e9b877b6a6def31b96e4784
const inputData =
  "0x02f902f3010d85012a05f200850d09243416830249f094efe048aded507b21cca84d295135652ef49cd04e80b902842e7ba6ef00000000000000000000000000000000000000000000000000000000000027470000000000000000000000008e17a9ea59b3549bc145e14efc0685a23f59adae000000000000000000000000000000000000000000000001a0c01934d640c0000000000000000000000000000000000000000000000000000000000000000080000000000000000000000000000000000000000000000000000000000000000f6b234eb34034aeb2314bd91fe4eddc9988f1a025d6553475ca449def30948beac433a512bae7c2993f98731c1ade72409bbf5a7fa8e81c0ecf10a9b3f9bc2024cc865d270d2632fec22073c562006002488a06cb35679ec5a740657b72b517b786ee6a2a25d1285ac93cf38e7045cbf46db00ce212beb8e339c7194fdbf7eff3422ea6c649dcfe409fc331dcf04267dd714465c3d1dcbdde2c38a498f84ffacfe376a0cfff2e91eb914035a7f95fed0228a388ff1358561f4d5e0b2243cac178d855372c80f4eb6dbd24a759aa40f32258d36009dce85f169fc4ba1ad7b9811f82fe34cd5722047f170f590d58b7fe77f70b6825d28b2b128775cf0e84f11a1b6adfbc190ba5dfb7dc294826bdcaae3fff530355340c668ff3a53e3a111ef087e0c1cb03bde5f04a030e67dcb43735a715e6a1c9e9a9890dc51024c5816a98f5456c2422f29c64cf566a6e13cd19d03e59d765ae2e57280c2886fa66997e2c105349b68f2713d4dda86d5f78bf9b118d70a90c2af4792a632d17598e781aaba781d9e557759dd752e459ab79ac2b160d9012b89a0c5fb2ec9e59318815e6a6fcab26c7fadac3599431d3ec830e69e871615d0d89fa5ab0c8dd73fe1f7eee5b151287d7d441bd5c835ce745df41c22968ae0ccd4ba2c04ab6a3ea8d4cb17f2b6cc080a0bc035007ddbf28468dd6459e3d0a56fb11daf214fa7a7c39913c3faa2ce3b3d6a030a4619f76d171211c16df9942214afa392724bd06ec85c3d37d63c4b39ee811";

nano_models.forEach(function (model) {
  test(
    "[Nano " + model.letter + "] Claim Boost Rewards",
    zemu(model, async (sim, eth) => {
      const serializedTx = txFromEtherscan(inputData);

      const tx = eth.signTransaction("44'/60'/0'/0", serializedTx);

      const right_clicks = model.letter === "S" ? 8 : 5;

      // Wait for the application to actually load and parse the transaction
      await waitForAppScreen(sim);
      // Navigate the display by pressing the right button `right_clicks` times, then pressing both buttons to accept the transaction.
      await sim.navigateAndCompareSnapshots(
        ".",
        testNetwork + "_ethx_" + model.name + "_claim_boost_rewards",
        [right_clicks, 0]
      );

      await tx;
    }),
    20000
  );
});
