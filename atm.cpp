#include <iostream>
#include <string>
#include "slot.hpp"
#include "account.hpp"
#include "bank.hpp"
#include "cashbin.hpp"
#include "atm.hpp"

using namespace std;

ATM* ATM::instance = nullptr;

ATM::ATM(int atm_id) : id(atm_id), state(IDLE) {
  card_reader = new Slot(*this);
  cash_bin = new CashBin(*this);
}

int ATM::getCardNumber() {
  int card_number;
  cout << "Input Card Number :";
  cin >> card_number;
  return card_number;
}
int ATM::getPIN() {
  int pin_number;
  cout << "Input PIN :";
  cin >> pin_number;
  return pin_number;
}

void ATM::run() {
  int operation;
  while (1) {
    switch (state) {
      case IDLE:
        if (card_reader && card_reader->CardInserted()) {
          state = LOGIN;
        }
        break;
      case LOGIN: {
        int card_number = getCardNumber();
        int pin_number = getPIN();
        bank = new Bank();
        if (bank && bank->login(card_number, pin_number)) {
          cout << "Select Account" << endl;
          int account_type;
          cin >> account_type;
          cur_accout = bank->selectAccount(account_type);
          state = OPERATION;
        } else {
          cout << "Wrong Account or PIN" << endl;
          state = IDLE;
        }
      } break;
      case OPERATION: {
        while (1) {
          if (cur_accout) {
            cout << "menu:" << endl;
            cout << "0.Quit" << endl;
            cout << "1.Inquery balance" << endl;
            cout << "2.Withdraw" << endl;
            cout << "3.Deposit" << endl;
          }
          cin >> operation;
          if (operation != QUIT) {
            switch (operation) {
              case INQUERY_BALANCE:
                cout << "Balance = " << cur_accout->getBalance() << endl;
                cout << endl;
                cout << "cash bin has balance " << cash_bin->getBalance() << endl;
                break;
              case WITHDRAW: {
                unsigned int amount = 0;
                cin >> amount;
                if (!cash_bin || !cash_bin->EnoughBalance(amount)) {
                  cout << "Cash Bin does not have enough cash!!" << endl;
                  break;
                } else if (cur_accout && !cur_accout->EnoughBalance(amount)) {
                  cout << "Balance is low!!" << endl;
                  break;
                } else {
                  cur_accout->Withdraw(amount);
                  cash_bin->Withdraw(amount);
                }
              } break;
              case DEPOSIT: {
                unsigned int amount = 0;
                cin >> amount;
                if (cash_bin) {
                  cash_bin->Deposit(amount);
                  cur_accout->Deposit(amount);
                }
              } break;
              default:
                cout << "ERROR" << endl;
                break;
            }
          } else {
            state = LOGOUT;
            break;
          }
        }
      } break;
      case LOGOUT:
        if (bank) {
          bank->logout();
          card_reader->CardEject();
          state = IDLE;
        }
        break;
      default:
        break;
    }
  }
}