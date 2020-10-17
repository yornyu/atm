
class ATM;

class CashBin {
 private:
  ATM* atm_;
  int balance_;

 public:
  CashBin(ATM& atm);
  void Deposit(unsigned int amount);
  int Withdraw(unsigned int amount);
  bool EnoughBalance(unsigned int amount);
  int getBalance() { return balance_; }
};