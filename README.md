# Ledger Staderlabs Plugin

This is a plugin for the Ethereum application which helps parsing and displaying relevant information when signing a Staderlabs transaction.

## Setup

Clone the plugin to a new folder.

```shell
mkdir staderlabs_plugin_folder
cd staderlabs_plugin_folder

git clone --recurse-submodules https://github.com/LedgerHQ/app-plugin-staderlabs.git
```

Then in the same folder clone app-ethereum.

```shell
git clone --recurse-submodules https://github.com/LedgerHQ/app-ethereum.git     #app-ethereum
```

Launch the docker

```shell
brew install coreutils          #For mac users if below command errors out (realpath doesn't exist)
sudo docker run --rm -ti -v "$(realpath .):/app" --user $(id -u $USER):$(id -g $USER) ghcr.io/ledgerhq/ledger-app-builder/ledger-app-dev-tools:latest
```

From the Docker console

```shell
#build the staderlabs plugin
cd app-plugin-staderlabs
make

#go to tests folder inside staderlabs plugin and build the ".elf" files for testing
cd tests
./build_local_test_elfs.sh
```

## Tests

Open a new Terminal and go to staderlabs_plugin_folder

```shell
cd app-plugin-staderlabs/tests      #go to tests folder inside app-plugin-staderlabs
yarn install                        #install node packages
yarn test                           #run tests
```

## Documentation

Need more information about the interface, the architecture, or general stuff about ethereum plugins? You can find more about them in the [ethereum-app documentation](https://github.com/LedgerHQ/app-ethereum/blob/master/doc/ethapp_plugins.asc).

## Smart Contracts

Smart contracts covered by this plugin are:

#### MATICx

| Network  | Contract Name | Smart Contract                               |
| -------- | ------------- | -------------------------------------------- |
| Ethereum | MaticX        | `0xf03a7eb46d01d9ecaa104558c732cf82f6b6b645` |
| Polygon  | ChildPool     | `0xfd225c9e6601c9d38d8f98d8731bf59efcf8c0e3` |

#### BNBx

| Network | Contract Name | Smart Contract                               |
| ------- | ------------- | -------------------------------------------- |
| BSC     | StakeManager  | `0x7276241a669489E4BBB76f63d2A43Bfe63080F2F` |

#### FTMx

| Network | Contract Name | Smart Contract                               |
| ------- | ------------- | -------------------------------------------- |
| Fantom  | FTMStaking    | `0xb458bfc855ab504a8a327720fcef98886065529b` |

#### ETHx

| Network  | Contract Name           | Smart Contract                               |
| -------- | ----------------------- | -------------------------------------------- |
| Ethereum | StaderStakePoolsManager | `0xcf5ea1b38380f6af39068375516daf40ed70d299` |
| Ethereum | UserWithdrawalManager   | `0x9f0491b32dbce587c50c4c43ab303b06478193a7` |
