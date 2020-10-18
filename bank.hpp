#pragma once
#include <iostream>
#include <string>

#include "account.hpp"
using namespace std;
class Bank {
 private:
  Account* checking_;
  Account* saving_;

 public:
  //Bank();
  Account* selectAccount(int type);
  void SendMessage(int card_num, int pin);
   // remote connect to bank;
  string ReadMessage();

  bool login(int card_num, int pin);

  void logout();
};