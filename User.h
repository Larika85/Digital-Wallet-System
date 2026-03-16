#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "Transaction.h"

using namespace std;

class BaseUser {
public:
    virtual void showDetails() const = 0;
    virtual ~BaseUser() = default;
};

class User : public BaseUser {
private:
    string username;
    string password;
    string name;
    float balance;
    vector<Transaction> transactionHistory;

public:
    User(const string &username, const string &password, const string &name, float balance);

    const string& getUsername() const;
    const string& getPassword() const;
    const string& getName() const;
    float getBalance() const;

    bool matches(const string &username, const string &password) const;
    void addFunds(float amount);
    bool deductFunds(float amount);
    void addTransaction(const Transaction &transaction);

    void showTransactionHistory() const;
    void showBalance() const;       // Add this line
    void showDetails() const override;

    User operator+(const User &other);

    friend ostream& operator<<(ostream &os, const User &user);
    friend istream& operator>>(istream &is, User &user);
};

#endif
