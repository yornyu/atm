#include <iostream>
#include <string>

#include "slot.hpp"
using namespace std;

bool Slot::card_inserted_ = false;

Slot::Slot(ATM& atm) : atm_(&atm) {}

  // hook to real cardreader device to update status;
void Slot::CardInsertedCallBack() {
  card_inserted_ = true;
}
void Slot::CardRejectedCallBack() {
  card_inserted_ = false;
}

bool Slot::CardInserted() {
  // mimic hardware reader
  card_inserted_ = true;
  return card_inserted_;
}
void Slot::CardEject() {
  cout << "Please take your card" << endl;
  card_inserted_ = false;
  return;
}

