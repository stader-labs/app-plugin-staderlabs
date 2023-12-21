/*******************************************************************************
 *   Ethereum 2 Deposit Application
 *   (c) 2020 Ledger
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 ********************************************************************************/

#include <stdint.h>
#include "staderlabs_plugin.h"

// List of selectors supported by this plugin.

// Network: Ethereum
// Contract: MaticX
// Method: function submit(uint256 _amount)
// Selector: 0xea99c2a6
static const uint32_t ETH_MATICX_SUBMIT_SELECTOR = 0xea99c2a6;

// Network: Ethereum
// Contract: MaticX
// Method: function requestWithdraw(uint256 _amount)
// Selector: 0x745400c9
static const uint32_t ETH_MATICX_REQUEST_WITHDRAW_SELECTOR = 0x745400c9;

// Network: Ethereum
// Contract: MaticX
// Method: function claimWithdrawal(uint256 _idx)
// Selector: 0xf8444436
static const uint32_t ETH_MATICX_CLAIM_WITHDRAWAL_SELECTOR = 0xf8444436;

// Network: Polygon
// Contract: ChildPool
// Method: function swapMaticForMaticXViaInstantPool()
// Selector: 0xc78cf1a0
static const uint32_t POLYGON_CHILDPOOL_SWAP_MATIC_FOR_MATICX_VIA_INSTANT_POOL_SELECTOR =
    0xc78cf1a0;

// Network: Polygon
// Contract: ChildPool
// Method: function requestMaticXSwap(uint256 _amount)
// Selector: 0x48eaf6d6
static const uint32_t POLYGON_CHILDPOOL_REQUEST_MATICX_SWAP_SELECTOR = 0x48eaf6d6;

// Network: Polygon
// Contract: ChildPool
// Method: function claimMaticXSwap(uint256 _idx)
// Selector: 0x77baf209
static const uint32_t POLYGON_CHILDPOOL_CLAIM_MATICX_SWAP_SELECTOR = 0x77baf209;

// Network: BSC
// Contract: StakeManager
// Method: function deposit()
// Selector: 0xd0e30db0
static const uint32_t BSC_STAKEMANAGER_DEPOSIT_SELECTOR = 0xd0e30db0;

// Network: BSC
// Contract: StakeManager
// Method: function requestWithdraw(uint256 _amountInBnbX)
// Selector: 0x745400c9
static const uint32_t BSC_STAKEMANAGER_REQUEST_WITHDRAW_SELECTOR = 0x745400c9;

// Network: BSC
// Contract: StakeManager
// Method: function claimWithdraw(uint256 _idx)
// Selector: 0xb13acedd
static const uint32_t BSC_STAKEMANAGER_CLAIM_WITHDRAW_SELECTOR = 0xb13acedd;

// Network: Fantom
// Contract: FTMStaking
// Method: function deposit()
// Selector: 0xd0e30db0
static const uint32_t FTM_DEPOSIT_SELECTOR = 0xd0e30db0;

// Network: Fantom
// Contract: FTMStaking
// Method: function undelegate(uint256 wrID, uint256 amountFTMx, uint256 minAmountFTM)
// Selector: 0x4f864df4
static const uint32_t FTM_UNDELEGATE_SELECTOR = 0x4f864df4;

// Network: Fantom
// Contract: FTMStaking
// Method: function withdraw(uint256 wrID, uint256 bitmaskToSkip)
// Selector: 0x441a3e70
static const uint32_t FTM_WITHDRAW_SELECTOR = 0x441a3e70;

// Network: Ethereum
// Contract: StaderStakePoolsManager
// Method: function deposit(address _receiver, string calldata _referralId)
// Selector: 0xb7482509
static const uint32_t ETHX_DEPOSIT_SELECTOR = 0xb7482509;

// Network: Ethereum
// Contract: UserWithdrawalManager
// Method:
// function requestWithdraw(uint256 _ethXAmount, address _owner, string calldata _referralId)
// Selector: 0x1f7ec122
static const uint32_t ETHX_REQUEST_WITHDRAW_SELECTOR = 0x1f7ec122;

// Network: Ethereum
// Contract: UserWithdrawalManager
// Method: function claim(uint256 _requestId)
// Selector: 0x379607f5
static const uint32_t ETHX_CLAIM_SELECTOR = 0x379607f5;

// Network: Ethereum
// Contract: StaderStakePoolsManager
// Method: function deposit(address _receiver)
// Selector: 0xf340fa01
static const uint32_t ETHX_DEPOSIT_LEGACY_SELECTOR = 0xf340fa01;

// Network: Ethereum
// Contract: UserWithdrawalManager
// Method: function requestWithdraw(uint256 _ethXAmount, address _owner)
// Selector: 0xccc143b8
static const uint32_t ETHX_REQUEST_WITHDRAW_LEGACY_SELECTOR = 0xccc143b8;

// Network: Ethereum
// Contract: MerkleDistributor
// Method: function claim(uint256 index, address account, uint256 amount, bytes32[] calldata
// merkleProof)
// Selector: 0x2e7ba6ef
static const uint32_t ETHX_BOOST_REWARDS_CLAIM_SELECTOR = 0x2e7ba6ef;

// Array of all the different staderlabs selectors. Make sure this follows the same order as the
// enum defined in `staderlabs_plugin.h`
const uint32_t STADERLABS_SELECTORS[NUM_SELECTORS] = {
    ETH_MATICX_SUBMIT_SELECTOR,
    ETH_MATICX_REQUEST_WITHDRAW_SELECTOR,
    ETH_MATICX_CLAIM_WITHDRAWAL_SELECTOR,
    POLYGON_CHILDPOOL_SWAP_MATIC_FOR_MATICX_VIA_INSTANT_POOL_SELECTOR,
    POLYGON_CHILDPOOL_REQUEST_MATICX_SWAP_SELECTOR,
    POLYGON_CHILDPOOL_CLAIM_MATICX_SWAP_SELECTOR,
    BSC_STAKEMANAGER_DEPOSIT_SELECTOR,
    BSC_STAKEMANAGER_REQUEST_WITHDRAW_SELECTOR,
    BSC_STAKEMANAGER_CLAIM_WITHDRAW_SELECTOR,
    FTM_DEPOSIT_SELECTOR,
    FTM_UNDELEGATE_SELECTOR,
    FTM_WITHDRAW_SELECTOR,
    ETHX_DEPOSIT_SELECTOR,
    ETHX_REQUEST_WITHDRAW_SELECTOR,
    ETHX_CLAIM_SELECTOR,
    ETHX_DEPOSIT_LEGACY_SELECTOR,
    ETHX_REQUEST_WITHDRAW_LEGACY_SELECTOR,
    ETHX_BOOST_REWARDS_CLAIM_SELECTOR,
};
