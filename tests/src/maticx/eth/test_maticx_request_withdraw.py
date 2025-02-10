from web3 import Web3
from tests.utils import run_test, load_contract

contract = load_contract(
    "0xD22dd194B8ec2abEeeFAC36a69cd8898FB6C43b3"
)

# Test from replayed transaction: https://etherscan.io/tx/0x04727942385b723c4dc4881d696a3cb5ad576283231697d7786905712a0c1fa2

def test_maticx_request_withdraw(backend, firmware, navigator, test_name, wallet_addr):
    data = "0x745400c90000000000000000000000000000000000000000000000001bc16d674ec80000"
    run_test(
        contract, 
        data, 
        backend, 
        firmware, 
        navigator, 
        test_name, 
        wallet_addr
    )

