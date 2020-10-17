
class ATM;

class Slot {
 private:
  ATM* atm_;
  static bool card_inserted_;

 public:
  Slot(ATM& atm);

  // hook to real cardreader device to update status;
  static void CardInsertedCallBack();
  static void CardRejectedCallBack();

  bool CardInserted();
  void CardEject();
};
