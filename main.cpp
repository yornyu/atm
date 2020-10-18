#include <iostream>
#include <string>

#include "account.hpp"
#include "bank.hpp"
#include "cashbin.hpp"
#include "slot.hpp"
#include "atm.hpp"

int main() {
  ATM* atm = ATM::getInstance(1234);
  if(atm){
    atm->run();
  }
  return 0;
}