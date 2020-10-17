#include "bank.hpp"

#include <iostream>
#include <string>

using namespace std;

Account* Bank::selectAccount(int type) {
  switch (type) {
    case 0:
      return checking_;
      break;
    case 1:
      return saving_;
      break;
    default:
      cout << "ERROR" << endl;
      break;
  }
  return nullptr;
}
// remote connect to bank
void Bank::SendMessage(int card_num, int pin) {
  // mimic serialize data and send
  cout << "card_number = " << card_num << endl;
  cout << "PIN = "
       << "XXXXXX" << endl;
}
string Bank::ReadMessage() {
  string ret;
  ret = "checking_id: 123456, balance: 1000, checking_id: 654321, balance: 1000";
  return ret;
}

bool Bank::login(int card_num, int pin) {
  SendMessage(card_num, pin);

  int checking_id = 123456;
  unsigned int checking_balance = 1000;
  int saving_id = 654321;
  unsigned int saving_balance = 1000;

  //Get account info remotely
  string responce = ReadMessage();
  // Todo: update account info id, blance, type ...

  // type : 0 for checking
  checking_ = new Account(checking_id, checking_balance, 0);
  // type : 1 for saving
  saving_ = new Account(saving_id, saving_balance, 1);
  return true;
}

void Bank::logout() {
  // Todo: close session update remote bank
  delete checking_;
  delete saving_;
}
