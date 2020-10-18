#pragma once
#include "account.hpp"
#include "bank.hpp"
#include "cashbin.hpp"
#include "slot.hpp"

class ATM {
 private:
  enum State {
    IDLE,
    LOGIN,
    OPERATION,
    LOGOUT
  };
  enum Operation {
    QUIT,
    INQUERY_BALANCE,
    WITHDRAW,
    DEPOSIT
  };

  int id;
  Slot* card_reader;
  CashBin* cash_bin;
  Bank* bank;
  Account* cur_accout;
  int state;
  static ATM* instance;
  ATM(int atm_id);

 public:
  static ATM* getInstance(int atm_id) {
    if (instance == nullptr) {
      instance = new ATM(atm_id);
    }
    return instance;
  }
  int getCardNumber();
  int getPIN();
  void run();
};
