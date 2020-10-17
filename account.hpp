#pragma once

class Account {
 private:
  int accout_id_;
  unsigned int balance_;
  int type_;

 public:
  Account(int id, unsigned int balance, int type);
  void Deposit(unsigned int amount);
  int getBalance();
  unsigned int Withdraw(unsigned int amount);
  bool EnoughBalance(unsigned int amount);
};