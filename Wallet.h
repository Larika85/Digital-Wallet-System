#ifndef WALLET_H
#define WALLET_H

#include <vector>
#include <string>
#include "User.h" // Include User header file
#include "Transaction.h" // Include Transaction header file

using namespace std;

// Abstract base class for Wallet
class WalletBase {
public:
    virtual void registerUser(const string &username, const string &password, const string &name, float initialBalance) = 0;
    virtual ~WalletBase() = default;
};

// Wallet class inheriting from WalletBase
class Wallet : public WalletBase {
private:
    vector<User> users;  // Store users
    int transactionCount; // Track transaction count

    void loadUsers();
    void saveUsers();

public:
    Wallet();

    void registerUser(const string &username, const string &password, const string &name, float initialBalance) override;
    User* getUser(const string &username, const string &password);

    bool addFunds(const string &username, float amount);
    bool deductFunds(const string &username, float amount);
    bool transferFunds(const string &senderID, const string &receiverID, float amount, const string &date);
    bool removeUser(const string &username);
    bool isUsernameTaken(const string &username) const ;

    void mergeAccounts(const string &username1, const string &username2);
    bool isValidDate(const string &dateStr) const;
};

#endif // WALLET_H
