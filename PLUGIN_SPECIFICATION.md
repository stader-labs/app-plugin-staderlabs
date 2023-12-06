# Technical Specification

## About

This documentation describes the smart contracts and functions supported by the staderlabs plugin.

## MATICx

| Network  | Contract Name | Smart Contract                               |
| -------- | ------------- | -------------------------------------------- |
| Ethereum | MaticX        | `0xf03a7eb46d01d9ecaa104558c732cf82f6b6b645` |
| Polygon  | ChildPool     | `0xfd225c9e6601c9d38d8f98d8731bf59efcf8c0e3` |

#### Functions covered by above contract/s :
|Contract | Function | Selector | Displayed Parameters |
| --- | --- | --- | --- |
|MaticX | submit(uint256 \_amount) | `0xea99c2a6`| `_amount` |
|MaticX | requestWithdraw(uint256 \_amount) | `0x745400c9`| `_amount` |
|MaticX | claimWithdrawal(uint256 \_idx) | `0xf8444436`| |
|ChildPool | swapMaticForMaticXViaInstantPool() | `0xc78cf1a0`| native_token_amount (matic) |
|ChildPool | requestMaticXSwap(uint256 \_amount) | `0x48eaf6d6`| `_amount` |
|ChildPool | claimMaticXSwap(uint256 \_idx) | `0x77baf209`| |

## BNBx

| Network | Contract Name | Smart Contract                               |
| ------- | ------------- | -------------------------------------------- |
| BSC     | StakeManager  | `0x7276241a669489E4BBB76f63d2A43Bfe63080F2F` |

#### Functions covered by above contract/s :
|Contract | Function | Selector | Displayed Parameters |
| --- | --- | --- | --- |
|StakeManager | deposit() | `0xd0e30db0`| native_token_amount (bnb) |
|StakeManager | requestWithdraw(uint256 \_amountInBnbX) | `0x745400c9`| `_amountInBnbX` |
|StakeManager | claimWithdraw(uint256 \_idx) | `0xb13acedd`| |

## FTMx

| Network | Contract Name | Smart Contract                               |
| ------- | ------------- | -------------------------------------------- |
| Fantom  | FTMStaking    | `0xb458bfc855ab504a8a327720fcef98886065529b` |

#### Functions covered by above contract/s :
|Contract | Function | Selector | Displayed Parameters |
| --- | --- | --- | --- |
|FTMStaking | deposit() | `0xd0e30db0`| native_token_amount (ftm) |
|FTMStaking | undelegate(uint256 wrID, uint256 amountFTMx, uint256 minAmountFTM) | `0x4f864df4`| `amountFTMx` |
|FTMStaking | withdraw(uint256 wrID, uint256 bitmaskToSkip) | `0x441a3e70`| |

## ETHx

| Network  | Contract Name           | Smart Contract                               |
| -------- | ----------------------- | -------------------------------------------- |
| Ethereum | StaderStakePoolsManager | `0xcf5ea1b38380f6af39068375516daf40ed70d299` |
| Ethereum | UserWithdrawalManager   | `0x9f0491b32dbce587c50c4c43ab303b06478193a7` |
| Ethereum | MerkleDistributor   | `0xefE048ADed507b21CcA84d295135652Ef49CD04e` |

NOTE: MerkleDistributor address is a sample contract, there could be multiple instances of it.

#### Functions covered by above contract/s :
|Contract | Function | Selector | Displayed Parameters |
| --- | --- | --- | --- |
|StaderStakePoolsManager | deposit(address \_receiver, string calldata \_referralId) | `0xb7482509`| `_receiver`, native_token_amount (eth) |
|UserWithdrawalManager | requestWithdraw(uint256 \_ethXAmount, address \_owner, string calldata \_referralId) | `0x1f7ec122`| `_ethXAmount`, `_owner` |
|UserWithdrawalManager | claim(uint256 \_requestId) | `0x379607f5`| |
|StaderStakePoolsManager | deposit(address \_receiver) | `0xf340fa01`| `_receiver`, native_token_amount (eth) |
|UserWithdrawalManager | requestWithdraw(uint256 \_ethXAmount, address \_owner) | `0xccc143b8`| `_ethXAmount`, `_owner` |
|MerkleDistributor | claim(uint256 index, address account, uint256 amount, bytes32[] calldata merkleProof) | `0x2e7ba6ef`| `account`, `amount` |
