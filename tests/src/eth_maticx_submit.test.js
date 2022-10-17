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
// EDIT THIS: build your own test
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
      await sim.navigateAndCompareSnapshots(
        ".",
        model.name + "_submit_matic_tokens",
        [right_clicks, 0]
      );

      await tx;
    })
  );
});

// Test from constructed transaction
// EDIT THIS: build your own test
// nano_models.forEach(function(model) {
//   test('[Nano ' + model.letter + '] Swap Exact Eth For Tokens', zemu(model, async (sim, eth) => {
//   const contract = new ethers.Contract(contractAddr, abi);

//   // Constants used to create the transaction
//   // EDIT THIS: Remove what you don't need
//   const amountOutMin = parseUnits("28471151959593036279", 'wei');
//   const WETH = "0xc02aaa39b223fe8d0a0e5c4f27ead9083c756cc2";
//   const SUSHI = "0x6b3595068778dd592e39a122f4f5a5cf09c90fe2";
//   const path = [WETH, SUSHI];
//   const deadline = Number(1632843280);
//   // We set beneficiary to the default address of the emulator, so it maches sender address
//   const beneficiary = SPECULOS_ADDRESS;

//   // EDIT THIS: adapt the signature to your method
//   // signature: swapExactETHForTokens(uint amountOutMin, address[] calldata path, address to, uint deadline)
//   // EDIT THIS: don't call `swapExactETHForTokens` but your own method and adapt the arguments.
//   const {data} = await contract.populateTransaction.swapExactETHForTokens(amountOutMin, path, beneficiary ,deadline);

//   // Get the generic transaction template
//   let unsignedTx = genericTx;
//   // Modify `to` to make it interact with the contract
//   unsignedTx.to = contractAddr;
//   // Modify the attached data
//   unsignedTx.data = data;
//   // EDIT THIS: get rid of this if you don't wish to modify the `value` field.
//   // Modify the number of ETH sent
//   unsignedTx.value = parseEther("0.1");

//   // Create serializedTx and remove the "0x" prefix
//   const serializedTx = ethers.utils.serializeTransaction(unsignedTx).slice(2);

//   const tx = eth.signTransaction(
//     "44'/60'/0'/0",
//     serializedTx
//   );

//   const right_clicks = model.letter === 'S' ? 7 : 5;

//   // Wait for the application to actually load and parse the transaction
//   await waitForAppScreen(sim);
//   // Navigate the display by pressing the right button 10 times, then pressing both buttons to accept the transaction.
//   // EDIT THIS: modify `10` to fix the number of screens you are expecting to navigate through.
//   await sim.navigateAndCompareSnapshots('.', model.name + '_swap_exact_eth_for_tokens', [right_clicks, 0]);

//   await tx;
//   }));
// });
