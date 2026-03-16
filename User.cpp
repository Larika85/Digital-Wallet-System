#include "User.h"
#include <iostream>
using namespace std;

User::User(const string &username, const string &password, const string &name, float balance)
    : username(username), password(password), name(name), balance(balance) {}

const string& User::getUsername() const { return username; }
const string& User::getPassword() const { return password; }
const string& User::getName() const { return name; }
float User::getBalance() const { return balance; }

bool User::matches(const string &username, const string &password) const {
    return this->username == username && this->password == password;
}

void User::addFunds(float amount) { balance += amount; }
bool User::deductFunds(float amount) {
    if (balance >= amount) {
        balance -= amount;
        return true;
    }
    return false;
}

void User::addTransaction(const Transaction &transaction) {
    transactionHistory.push_back(transaction);
}

void User::showTransactionHistory() const {
    cout << "Transaction History for " << username << ":\n";
    for (const auto &transaction : transactionHistory) {
        transaction.displayTransaction();
    }
}

void User::showBalance() const { // Add this implementation
    cout << "Balance for " << username << ": " << balance << endl;
}

void User::showDetails() const { // Ensure only one definition exists
    cout << "Username: " << username << ", Name: " << name << ", Balance: " << balance << endl;
}

User User::operator+(const User &other) {
    User mergedUser = *this;
    mergedUser.addFunds(other.balance);
    return mergedUser;
}

ostream& operator<<(ostream &os, const User &user) {
    os << "Username: " << user.username << ", Name: " << user.name << ", Balance: " << user.balance;
    return os;
}

istream& operator>>(istream &is, User &user) {
    is >> user.username >> user.password >> user.name >> user.balance;
    return is;
}
