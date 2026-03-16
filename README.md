# Digital Wallet Management System

A command-line Digital Wallet Management System written in C++ that simulates core wallet operations — account registration, secure login, fund transfers, balance management, and transaction tracking. Built with C++11 using OOP principles including inheritance, operator overloading, and file-based persistence.

## Features

- **User Registration**: Register with a unique username, password, display name, and initial balance. Duplicate usernames are detected and rejected before registration.
- **Secure Login**: Authenticate with a username and password to access wallet operations.
- **Add Funds**: Deposit an amount into your wallet; balance is updated and saved immediately.
- **Deduct Funds**: Withdraw from your wallet; rejected if balance is insufficient.
- **Fund Transfers**: Transfer money to another registered user. Date is validated in `YYYY-MM-DD` format (including leap year checks). Both sender and receiver get the transaction logged.
- **Transaction History**: View all transactions associated with your account.
- **Balance Display**: Check your current wallet balance.
- **Account Merging**: Merge a second verified account into your own — balances are combined and the second account is removed.
- **Account Deletion**: Permanently delete your account from the system.
- **Data Persistence**: User records are loaded from and saved to `users.txt` after every operation.

## Project Structure

| File | Description |
|---|---|
| `Transaction.h / Transaction.cpp` | `Transaction` class — stores ID, amount, date, sender, and receiver; inherits from abstract `BaseTransaction` |
| `User.h / User.cpp` | `User` class — stores username, password, name, balance, and transaction history; inherits from abstract `BaseUser` |
| `Wallet.h / Wallet.cpp` | `Wallet` class — manages all users and operations; handles file I/O, transfers, merging; inherits from abstract `WalletBase` |
| `date.h / date.cpp` | `Date` class — parses and validates `YYYY-MM-DD` strings including leap year logic |
| `main.cpp` | Entry point — interactive menu-driven CLI |
| `users.txt` | Flat-file store for persistent user data |
| `Makefile` | Build configuration |

## Design

The project uses **abstract base classes** for its three core types:

| Abstract Class | Pure Virtual Method |
|---|---|
| `BaseTransaction` | `displayTransaction()` |
| `BaseUser` | `showDetails()` |
| `WalletBase` | `registerUser(...)` |

**Operator overloading** is used throughout:

- `User::operator+(const User&)` — merges two users; adds the second user's balance into the first
- `User::operator<<` / `operator>>` — file serialization (username, password, name, balance)
- `Transaction::operator<<` — formatted output of transaction details
- `Date::operator<<` / `operator>>` — date string I/O

## Getting Started

### Prerequisites

A C++ compiler with C++11 support or later (e.g., `g++` on Linux or macOS).

### Build

```bash
make
```

Compiles all `.cpp` files, places object files in the `obj/` directory, and produces the `DigitalWalletSystem` executable.

### Run

```bash
./DigitalWalletSystem
```

### Clean

```bash
make clean
```

Removes the `obj/` directory contents and the compiled executable.

## Usage

On launch:

```
1. Login
2. Register a new user
3. Exit
```

After a successful login:

```
1. Add funds
2. Deduct funds
3. Transfer funds
4. Show balance
5. Show transaction history
6. Merge accounts
7. Logout
8. Delete account
```

When transferring funds, you will be prompted for the receiver's username, an amount (must be positive), and a date in `YYYY-MM-DD` format. The date is validated before the transfer proceeds.

When merging accounts, you must provide the username **and password** of the second account to authenticate it before the merge is performed.

## Class Reference

### `Transaction`

```cpp
Transaction(int id, float amt, const string &date, const string &senderID, const string &receiverID);
```

| Member | Description |
|---|---|
| `transactionID` | Auto-incremented unique ID |
| `amount` | Transfer amount — throws `invalid_argument` if ≤ 0 |
| `date` | Date string passed from caller |
| `senderID` | Username of sender |
| `receiverID` | Username of receiver |
| `displayTransaction()` | Prints full transaction details to stdout |
| `getTransactionID()` | Returns the transaction ID |
| `getSenderID()` / `getReceiverID()` | Returns sender / receiver username |

### `User`

```cpp
User(const string &username, const string &password, const string &name, float balance);
```

| Member | Description |
|---|---|
| `username` | Unique login identifier |
| `password` | Account password |
| `name` | Display name |
| `balance` | Current wallet balance |
| `transactionHistory` | `vector<Transaction>` of all associated transactions |
| `addFunds(amount)` | Increments balance |
| `deductFunds(amount)` | Decrements balance; returns `false` if insufficient |
| `matches(username, password)` | Returns `true` if credentials match |
| `addTransaction(t)` | Appends a transaction to history |
| `showBalance()` | Prints current balance |
| `showTransactionHistory()` | Prints all transactions |
| `showDetails()` | Prints username, name, and balance |
| `operator+(other)` | Returns a new user with combined balance |

### `Wallet`

```cpp
Wallet(); // Loads users from users.txt on construction
```

| Method | Description |
|---|---|
| `registerUser(username, password, name, balance)` | Adds new user; throws `runtime_error` if username taken |
| `getUser(username, password)` | Returns pointer to matching user, or `nullptr` |
| `isUsernameTaken(username)` | Returns `true` if username already exists |
| `addFunds(username, amount)` | Adds funds; throws if user not found |
| `deductFunds(username, amount)` | Deducts funds; throws on insufficient balance or user not found |
| `transferFunds(sender, receiver, amount, date)` | Validates date, checks balance, logs transaction on both users, saves |
| `removeUser(username)` | Deletes user; throws if not found |
| `mergeAccounts(username1, username2)` | Merges `username2` into `username1` using `operator+`, removes `username2` |
| `isValidDate(dateStr)` | Delegates to `Date::isValid()` |

### `Date`

```cpp
Date(int year, int month, int day);
Date(const string &dateStr); // Parses "YYYY-MM-DD"; throws invalid_argument on bad format
```

| Method | Description |
|---|---|
| `isValid()` | Validates year ≥ 1, month 1–12, day within month range |
| `isLeapYear(year)` | Returns `true` for leap years |
| `toString()` | Returns zero-padded `YYYY-MM-DD` string |

## Data Format

`users.txt` stores one user per line, space-separated:

```
username password name balance
```

Example:
```
alice pass123 Alice 1500.5
bob securepass Bob 800.0
```

> **Note:** Transaction history is not persisted to file. Only balances are saved between sessions — transaction history is lost on exit.

## CI

This project uses GitHub Actions. The workflow runs on every push and pull request to `main` on `ubuntu-latest`, executing:

```bash
make
make check
make distcheck
```

## Contributing

Fork the repository, make your changes, and open a pull request. Bug reports and feature requests can be submitted via issues.

## License

This project is open-source.
