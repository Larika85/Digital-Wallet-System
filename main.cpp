#include <iostream>
#include <string>
#include "Wallet.h"
#include "Transaction.h"
#include "date.h"
using namespace std;

int main()
{
    Wallet wallet;
    string username, password, name, date;
    float amount;

    try {
        while (true)
        {
            cout << "1. Login\n2. Register a new user\n3.Exit\nChoose an option: ";
            int choice;
            cin >> choice;

            if (choice == 1)
            {
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;

                User *currentUser = wallet.getUser(username, password);
                if (currentUser)
                {
                    cout << "Login successful! Welcome, " << currentUser->getName() << "." << endl;
                    while (true)
                    {
                        cout << "1. Add funds\n2. Deduct funds\n3. Transfer funds\n4. Show balance\n5. Show transaction history\n6. Merge accounts\n7. Logout\n8. Delete account \nChoose an option: ";
                        cin >> choice;

                        if (choice == 1)
                        {
                            cout << "Enter amount to add: ";
                            cin >> amount;
                            wallet.addFunds(username, amount);
                        }
                        else if (choice == 2)
                        {
                            cout << "Enter amount to deduct: ";
                            cin >> amount;
                            if (wallet.deductFunds(username, amount))
                            {
                                cout << "Deduction successful!" << endl;
                            }
                            else
                            {
                                cout << "Insufficient funds!" << endl;
                            }
                        }
                        else if (choice == 3)
                        {
                            string receiver;
                            cout << "Enter receiver username: ";
                            cin >> receiver;
                            cout << "Enter amount to transfer: ";
                            cin >> amount;

                            if (amount < 0)
                            {
                                throw invalid_argument("Amount should be positive");
                            }

                            cin.ignore(); // This clears the leftover newline character
                            cout << "Enter date (YYYY-MM-DD): ";
                            getline(cin, date);

                            if (!wallet.isValidDate(date))
                            {
                                cout << "Invalid date! Please enter a valid date in YYYY-MM-DD format." << endl;
                                continue;
                            }

                            if (wallet.transferFunds(username, receiver, amount, date))
                            {
                                cout << "Transfer successful!" << endl;
                            }
                            else
                            {
                                cout << "Transfer failed!" << endl;
                            }
                        }
                        else if (choice == 4)
                        {
                            currentUser->showBalance();
                        }
                        else if (choice == 5)
                        {
                            currentUser->showTransactionHistory();
                        }
                        else if (choice == 6)
                        {
                            string username2, password2;
                            cout << "Enter the username of the account to merge: ";
                            cin >> username2;
                            cout << "Enter password of 2nd account: ";
                            cin >> password2;
                            User *currentUser2 = wallet.getUser(username2, password2);
                            if (currentUser2)
                                wallet.mergeAccounts(username, username2);
                            else
                                cout << "Enter valid account/password" << endl;
                        }
                        else if (choice == 7)
                        {
                            break;
                        }
                        else if (choice == 8)
                        {
                            if (wallet.removeUser(username))
                            {
                                cout << "User removed successfully!" << endl;
                                break;
                            }
                            else
                            {
                                cout << "User removal failed! User not found." << endl;
                            }
                        }
                    }
                }
                else
                {
                    cout << "Invalid username or password.\n";
                }
            }
             else if (choice == 2) {
    cout << "Enter new username: ";
    cin >> username;

    if (wallet.isUsernameTaken(username)) {
        cout << "Duplicate User detected (try with a different username)." << endl;
        continue; // Go back to the menu
    }

    cout << "Enter new password: ";
    cin >> password;
    cout << "Enter name: ";
    cin >> name;
    cout << "Enter initial balance: ";
    cin >> amount;

    wallet.registerUser(username, password, name, amount);
    cout << "User registered successfully!" << endl;
}

            else
            {
                break;
            }
        }
    }
    catch (const exception &e)
    {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
