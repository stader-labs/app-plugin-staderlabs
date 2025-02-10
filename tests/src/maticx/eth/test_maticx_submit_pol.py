from web3 import Web3
from tests.utils import run_test, load_contract

contract = load_contract(
    "0xD22dd194B8ec2abEeeFAC36a69cd8898FB6C43b3"
)

# Test from replayed transaction: https://etherscan.io/tx/0x0a75cc89e54f34610a3064c607205b7909a1f4cad80e11646732b2338fc4bf16

def test_maticx_submit_pol(backend, firmware, navigator, test_name, wallet_addr):
    data = "0x1564da7900000000000000000000000000000000000000000000001bc16d674ec80000"
    run_test(
        contract, 
        data, 
        backend, 
        firmware, 
        navigator, 
        test_name, 
        wallet_addr
    )

