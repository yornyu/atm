# Build
```shell
mkdir build
cd build
cmake ..
make 
```
# Run
```shell
./atm_demo

input integer as card number 
input integer as PIN
select account type: 0 checking, 1 saving
ctrl + c quit

```
# Note
```
class slot handles card reading
class cashbin handles cash bin deposoit/withdraw and balance check
class account handles the account info
class bank handles udpateing account info from remote
class atm is the entry point
```
