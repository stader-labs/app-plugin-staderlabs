# Technical Specification

## About

Below Ledger Live Apps and their corresponding smart contract functionalities are supported by this plugin.

#### MATICx

| Network  | Contract Name | Smart Contract                               |
| -------- | ------------- | -------------------------------------------- |
| Ethereum | MaticX        | `0xf03a7eb46d01d9ecaa104558c732cf82f6b6b645` |
| Polygon  | ChildPool     | `0xfd225c9e6601c9d38d8f98d8731bf59efcf8c0e3` |

Functions covered by above contracts:
|Contract | Function | Selector | Displayed Parameters |
| --- | --- | --- | --- |
|MaticX | submit(uint256 \_amount) | `0xea99c2a6`| `_amount` |
|MaticX | submitPOL(uint256 \_amount) | `0x1564da79`| `_amount` |
|MaticX | requestWithdraw(uint256 \_amount) | `0x745400c9`| `_amount` |
|MaticX | claimWithdrawal(uint256 \_idx) | `0xf8444436`| |
|ChildPool | swapMaticForMaticXViaInstantPool() | `0xc78cf1a0`| native_token_amount (matic) |
|ChildPool | requestMaticXSwap(uint256 \_amount) | `0x48eaf6d6`| `_amount` |
|ChildPool | claimMaticXSwap(uint256 \_idx) | `0x77baf209`| |

#### BNBx

| Network | Contract Name | Smart Contract                               |
| ------- | ------------- | -------------------------------------------- |
| BSC     | StakeManager  | `0x3b961e83400d51e6e1af5c450d3c7d7b80588d28` |

Functions covered by above contracts:
|Contract | Function | Selector | Displayed Parameters |
| --- | --- | --- | --- |
|StakeManager | delegate(string calldata \_referralId) | `0x9ddb511a`| native_token_amount (bnb) |
|StakeManager | requestWithdraw(uint256 \_amount, string calldata \_referralId) | `0x0d57afa6`| `_amount` |
|StakeManager | claimWithdrawal(uint256 \_idx) | `0xf8444436`| |

#### ETHx

| Network  | Contract Name           | Smart Contract                               |
| -------- | ----------------------- | -------------------------------------------- |
| Ethereum | StaderStakePoolsManager | `0xcf5ea1b38380f6af39068375516daf40ed70d299` |
| Ethereum | UserWithdrawalManager   | `0x9f0491b32dbce587c50c4c43ab303b06478193a7` |

Functions covered by above contracts:
|Contract | Function | Selector | Displayed Parameters |
| --- | --- | --- | --- |
|StaderStakePoolsManager | deposit(address \_receiver, string calldata \_referralId) | `0xb7482509`| `_receiver`, native_token_amount (eth) |
|UserWithdrawalManager | requestWithdraw(uint256 \_ethXAmount, address \_owner, string calldata \_referralId) | `0x1f7ec122`| `_ethXAmount`, `_owner` |
|UserWithdrawalManager | claim(uint256 \_requestId) | `0x379607f5`| |

#### KELP (will be deprecated soon)

| Network | Contract Name | Smart Contract                               |
| ------- | ------------- | -------------------------------------------- |
| Ethereum  | LRTDepositPool    | `0x036676389e48133B63a802f8635AD39E752D375D` |
| Ethereum  | LRTWithdrawalManager    | `0x62de59c08eb5dae4b7e6f7a8cad3006d6965ec16` |

Functions covered by above contracts:
|Contract | Function | Selector | Displayed Parameters |
| --- | --- | --- | --- |
|LRTDepositPool | depositETH(uint256 minRSETHAmountExpected, string calldata referralId) | `0x72c51c0b`| native_token_amount (eth) |
|LRTDepositPool | depositAsset(address asset, uint256 depositAmount, uint256 minRSETHAmountExpected, string calldata referralId) | `0xc3ae1766`| `asset`, `depositAmount` |
|LRTWithdrawalManager | initiateWithdrawal(address asset, uint256 rsETHUnstaked) | `0xc8393ba9`| `asset`, `rsETHUnstaked` |
|LRTWithdrawalManager | completeWithdrawal(address asset) | `0x6dbaf9ee`| `asset` |
