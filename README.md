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

## Ethereum-App

Need more information about the interface, the architecture, or general stuff about ethereum plugins? You can find more about them in the [ethereum-app documentation](https://github.com/LedgerHQ/app-ethereum/blob/master/doc/ethapp_plugins.asc).

## Smart Contracts

Smart contracts covered by this plugin are documented in [PLUGIN_SPECIFICATON.md](https://github.com/LedgerHQ/app-plugin-staderlabs/blob/develop/PLUGIN_SPECIFICATION.md)
