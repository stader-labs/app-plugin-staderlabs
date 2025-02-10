from web3 import Web3
from tests.utils import run_test, load_contract

contract = load_contract(
    "0xD22dd194B8ec2abEeeFAC36a69cd8898FB6C43b3"
)

# Test from replayed transaction: https://etherscan.io/tx/0x92f606f3ab623de706e4a1a2bfdcfa95d07f071f2f3aacfc729aefa6b3c6d94c

def test_maticx_submit(backend, firmware, navigator, test_name, wallet_addr):
    data = "0xea99c2a60000000000000000000000000000000000000000000000481591030b2a830000"
    run_test(
        contract, 
        data, 
        backend, 
        firmware, 
        navigator, 
        test_name, 
        wallet_addr
    )

