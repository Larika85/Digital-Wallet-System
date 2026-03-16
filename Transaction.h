#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <iostream>

using namespace std;

// Abstract base class for Transactions
class BaseTransaction {
public:
    virtual void displayTransaction() const = 0;
    virtual ~BaseTransaction() = default;
};

class Transaction : public BaseTransaction {
private:
    int transactionID;
    float amount;
    string date;
    string senderID;
    string receiverID;

public:
    Transaction(int id, float amt, const string &d, const string &sender, const string &receiver);

    void displayTransaction() const override;
    int getTransactionID() const;
    string getSenderID() const;
    string getReceiverID() const;

    friend ostream& operator<<(ostream &os, const Transaction &transaction);
};

#endif
