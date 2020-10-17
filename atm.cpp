#include <iostream>
#include <string>
#include "slot.hpp"
#include "account.hpp"
#include "bank.hpp"
#include "cashbin.hpp"

using namespace std;
/*
class CashBin;
class Slot;
class Bank;
class ATM;

class CashBin {
 private:
  ATM* atm_;
  int balance_;

 public:
  CashBin(ATM& atm)
      : atm_(&atm), balance_(1000) {}
  void Deposit(unsigned int amount) {
    balance_ += amount;
  }
  int Withdraw(unsigned int amount) {
    if (amount <= balance_) {
      balance_ -= amount;
      return amount;
    } else {
      cout << "Not enough cash!!!" << endl;
      return 0;
    }
  }
  bool EnoughBalance(unsigned int amount){
    return balance_ > amount;
  }

  int getBalance() { return balance_; }
};

class Slot {
 private:
  ATM* atm_;
  static bool card_inserted_;

 public:
  Slot(ATM& atm) : atm_(&atm){}

  // hook to real cardreader device to update status;
  static void CardInsertedCallBack() {
    card_inserted_ = true;
  }
  static void CardRejectedCallBack() {
    card_inserted_ = false;
  }

  bool CardInserted() {
    // mimic hardware reader
    card_inserted_ = true;
    return card_inserted_;
  }
  void CardEject(){
    cout << "Please take your card" << endl;
    card_inserted_ = false;
    return;
  }
};

bool Slot::card_inserted_ = false;

class Account {
 private:
  int accout_id_;
  unsigned int balance_;
  int type_;

 public:
  Account(int id, unsigned int balance, int type)
      : accout_id_(id), balance_(balance), type_(type) {}
  void Deposit(unsigned int amount) { balance_ += amount; }
  int getBalance() { return balance_; }
  unsigned int Withdraw(unsigned int amount) {
    if (amount <= balance_) {
      balance_ -= amount;
      return amount;
    } else {
      // Todo: remind balance is low
      return 0;
    }
  }
  bool EnoughBalance(unsigned int amount) {
    return balance_ > amount;
  }
};

class Bank {
 private:
  Account* checking_;
  Account* saving_;

 public:
  //Bank();
  Account* selectAccount(int type) {
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
  void SendMessage(int card_num, int pin){
    // mimic serialize data and send 
    cout << "card_number = " << card_num << endl;
    cout << "PIN = "
         << "XXXXXX" << endl;
  }
  string ReadMessage(){
    string ret;
    ret = "checking_id: 123456, balance: 1000, checking_id: 654321, balance: 1000";
    return ret;
  }

  bool login(int card_num, int pin) {
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

  void logout() {
    // Todo: close session update remote bank
    delete checking_;
    delete saving_;
  }
};
*/
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
  ATM(int atm_id) : id(atm_id), state(IDLE) {
    card_reader = new Slot(*this);
    cash_bin = new CashBin(*this);
  }
  int getCardNumber() {
    int card_number;
    cout << "Input Card Number :";
    cin >> card_number;
    return card_number;
  }
  int getPIN() {
    int pin_number;
    cout << "Input PIN :";
    cin >> pin_number;
    return pin_number;
  }

  void run() {
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
                case WITHDRAW:{
                  unsigned int amount = 0;
                  cin >> amount;
                  if(!cash_bin || !cash_bin->EnoughBalance(amount)){
                    cout << "Cash Bin does not have enough cash!!" << endl;
                    break;
                  } else if (cur_accout && !cur_accout->EnoughBalance(amount)){
                    cout << "Balance is low!!" << endl;
                    break;
                  } else {
                    cur_accout->Withdraw(amount);
                    cash_bin->Withdraw(amount);
                  }
                } break;
                case DEPOSIT:{
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
};


int main(){
  ATM atm(1234);
  atm.run();
  return 0;
}