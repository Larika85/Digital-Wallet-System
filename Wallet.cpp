#include "Wallet.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include "Date.h"
#include "user.h"
using namespace std;

// Constructor
Wallet::Wallet() : transactionCount(0) {
    loadUsers();
}

// Load users from file
void Wallet::loadUsers() {
    ifstream file("users.txt");
    string username, password, name;
    float balance;

    while (file >> username >> password >> name >> balance) {
        users.emplace_back(username, password, name, balance);
    }
}

// Save users to file
void Wallet::saveUsers() {
    ofstream file("users.txt");
    for (const auto &user : users) {
        file << user.getUsername() << " "
             << user.getPassword() << " "
             << user.getName() << " "
             << user.getBalance() << endl;
    }
}

// Register a new user
void Wallet::registerUser(const string &username, const string &password, const string &name, float initialBalance) {
    for (const auto &user : users) {
        if (user.getUsername() == username) {
            throw runtime_error("User already exists!");
        }
    }
    users.emplace_back(username, password, name, initialBalance);
    saveUsers();
}

// Get user by username and password
User* Wallet::getUser(const string &username, const string &password) {
    for (auto &user : users) {
        if (user.matches(username, password)) {
            return &user;
        }
    }
   return nullptr;
}
bool Wallet::isUsernameTaken(const string &username) const {
    for (const auto &user : users) {
        if (user.getUsername() == username) {
            return true;
        }
    }
    return false;
}


// Add funds to a user's account
bool Wallet::addFunds(const string &username, float amount) {
    for (auto &user : users) {
        if (user.getUsername() == username) {
            user.addFunds(amount);
            saveUsers();
            return true;
        }
    }
    throw runtime_error("User not found!");
}

// Deduct funds from a user's account
bool Wallet::deductFunds(const string &username, float amount) {
    for (auto &user : users) {
        if (user.getUsername() == username) {
            if (!user.deductFunds(amount)) {
                throw runtime_error("Insufficient balance!");
            }
            saveUsers();
            return true;
        }
    }
    throw runtime_error("User not found!");
}

// Transfer funds between users
bool Wallet::transferFunds(const string &senderID, const string &receiverID, float amount, const string &date) {
    if (!isValidDate(date)) {
        throw runtime_error("Invalid date format!");
    }

    User *sender = nullptr;
    User *receiver = nullptr;

    for (auto &user : users) {
        if (user.getUsername() == senderID) {
            sender = &user;
        }
        if (user.getUsername() == receiverID) {
            receiver = &user;
        }
    }

    if (!sender || !receiver) {
        throw runtime_error("Invalid sender or receiver!");
    }

    if (!sender->deductFunds(amount)) {
        throw runtime_error("Insufficient funds for transfer!");
    }

    receiver->addFunds(amount);

    // Log the transaction
    Transaction transaction(transactionCount++, amount, date, senderID, receiverID);
    sender->addTransaction(transaction);
    receiver->addTransaction(transaction);

    saveUsers();
    return true;
}

// Remove a user from the wallet
bool Wallet::removeUser(const string &username) {
    auto it = remove_if(users.begin(), users.end(),
                        [&](const User &user) { return user.getUsername() == username; });

    if (it != users.end()) {
        users.erase(it, users.end());
        saveUsers();
        return true;
    }
    throw runtime_error("User not found!");
}

// Merge two user accounts
void Wallet::mergeAccounts(const string &username1, const string &username2) {
    User *user1 = nullptr;
    User *user2 = nullptr;

    for (auto &user : users) {
        if (user.getUsername() == username1) {
            user1 = &user;
        }
        if (user.getUsername() == username2) {
            user2 = &user;
        }
    }

    if (!user1 || !user2) {
        throw runtime_error("One or both users not found!");
    }

    // Use the overloaded `+` operator to merge accounts
    *user1 = *user1 + *user2;
    removeUser(username2);

    saveUsers();
}

// Validate date format
bool Wallet::isValidDate(const string &dateStr) const {
    Date date(dateStr);
    return date.isValid();
}
