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

 public:
  ATM(int atm_id);
  int getCardNumber();
  int getPIN();
  void run();
};
