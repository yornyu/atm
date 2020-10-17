#include <iostream>
#include <string>
#include "cashbin.hpp"
using namespace std;

class ATM;


CashBin::CashBin(ATM& atm)
      : atm_(&atm), balance_(1000) {}

void CashBin::Deposit(unsigned int amount) {
  balance_ += amount;
}
int CashBin::Withdraw(unsigned int amount) {
  if (amount <= balance_) {
    balance_ -= amount;
    return amount;
  } else {
    cout << "Not enough cash!!!" << endl;
    return 0;
  }
}
bool CashBin::EnoughBalance(unsigned int amount) {
  return balance_ > amount;
}
