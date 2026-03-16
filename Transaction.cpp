#include "Transaction.h"
#include <iostream>
#include <stdexcept>

using namespace std;

Transaction::Transaction(int id, float amt, const string &d, const string &sender, const string &receiver)
    : transactionID(id), amount(amt), date(d), senderID(sender), receiverID(receiver) {
    if (amt <= 0) {
        throw invalid_argument("Transaction amount must be greater than zero.");
    }
}

void Transaction::displayTransaction() const {
    cout << "Transaction ID: " << transactionID
         << ", Amount: " << amount
         << ", Date: " << date
         << ", From: " << senderID
         << " to " << receiverID << endl;
}

int Transaction::getTransactionID() const { return transactionID; }
string Transaction::getSenderID() const { return senderID; }
string Transaction::getReceiverID() const { return receiverID; }

ostream& operator<<(ostream &os, const Transaction &transaction) {
    os << "Transaction ID: " << transaction.transactionID
       << ", Amount: " << transaction.amount
       << ", Date: " << transaction.date
       << ", From: " << transaction.senderID
       << " to " << transaction.receiverID;
    return os;
}
