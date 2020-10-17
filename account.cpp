#include <iostream>
#include <string>
#include "account.hpp"


Account::Account(int id, unsigned int balance, int type)
      : accout_id_(id), balance_(balance), type_(type) {

      }
      
void Account::Deposit(unsigned int amount) { balance_ += amount; }
int Account::getBalance() { return balance_; }
unsigned int Account::Withdraw(unsigned int amount) {
  if (amount <= balance_) {
    balance_ -= amount;
    return amount;
  } else {
    // Todo: remind balance is low
    return 0;
  }
}
bool Account::EnoughBalance(unsigned int amount) {
  return balance_ > amount;
}
