#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>
using namespace std;

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

bool isValidEmail(const string& email) {
    return email.find('@') != string::npos;
}

int checkPassword(const string& password) {
    if (password.length() < 8) return 1;
    for (char c : password) {
        if (!isalnum(c)) return 2;
    }
    return 0;
}

struct User {
    string email, username, password;
    double balance = 0;

};

vector<User> loadUsers() {
    vector<User> users;
    ifstream file("user.txt");
    if (!file.is_open()) return users;

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        User u;
        ss >> u.email >> u.username >> u.password >> u.balance;
        if (!u.email.empty())
            users.push_back(u);
    }
    return users;
}

void saveUsers(const vector<User>& users) {
    ofstream file("user.txt", ios::trunc);
    for (auto& u : users) {
        file << u.email << " " << u.username << " " << u.password << " " << u.balance << endl;
    }
}

int findUser(const vector<User>& users, const string& email, const string& password) {
    for (int i = 0; i < (int)users.size(); i++) {
        if (users[i].email == email && users[i].password == password) return i;
    }
    return -1;
}

void userMenu(vector<User>& users, int idx) {
    int choice;
    while (true) {
        system("cls");
        setColor(10);
        cout << "===== Welcome, " << users[idx].username << " =====" << endl;
        cout << "[1] View Balance" << endl;
        cout << "[2] Deposit Money" << endl;
        cout << "[3] Withdraw Money" << endl;
        cout << "[4] Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            setColor(10);
            cout << "\nYour Balance: " << users[idx].balance << " $" << endl;
            Sleep(2000);
        }
        else if (choice == 2) {
            double amount;
            cout << "Amount to deposit: ";
            cin >> amount;
            if (amount > 0) {
                users[idx].balance += amount;
                saveUsers(users);
                setColor(10);
                cout << amount << " $ deposited successfully!" << endl;
            }
            else {
                setColor(12);
                cout << "Invalid amount!" << endl;
            }
            Sleep(2000);
        }
        else if (choice == 3) {
            double amount;
            cout << "Amount to withdraw: ";
            cin >> amount;
            if (amount > 0 && amount <= users[idx].balance) {
                users[idx].balance -= amount;
                saveUsers(users);
                setColor(10);
                cout << amount << " $ withdrawn successfully!" << endl;
            }
            else {
                setColor(12);
                cout << "Insufficient balance or invalid amount!" << endl;
            }
            Sleep(2000);
        }
        else if (choice == 4) {
            return;
        }
        else {
            setColor(12);
            cout << "Invalid choice!" << endl;
            Sleep(1000);
        }
    }
}

int main() {
    for (int i = 0; i < 2; i++) {
        system("cls");
        setColor(3);
        cout << "login." << endl; Sleep(500);
        system("cls");
        cout << "login.." << endl; Sleep(500);
        system("cls");
        cout << "login..." << endl; Sleep(500);
    }

    int choice;

    while (true) {
        system("cls");
        setColor(10);
        cout << "==============================" << endl;
        cout << "     Welcome to Bank System   " << endl;
        cout << "==============================" << endl;
        cout << "[1] - Login" << endl;
        cout << "[2] - Create Account" << endl;
        cout << "[3] - Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string email, password;
            system("cls");
            setColor(10);
            cout << "===== Login =====" << endl;
            cout << "Email: ";
            cin >> email;
            cout << "Password: ";
            cin >> password;

            vector<User> users = loadUsers();
            int idx = findUser(users, email, password);

            if (idx != -1) {
                setColor(10);
                cout << "\nLogin successful!" << endl;
                Sleep(1000);
                userMenu(users, idx);
            }
            else {
                setColor(12);
                cout << "\nInvalid email or password!" << endl;
                Sleep(2000);
            }
        }
        else if (choice == 2) {
            string email, username, password;

            while (true) {
                system("cls");
                setColor(10);
                cout << "===== Create Account =====" << endl;
                cout << "Email: ";
                cin >> email;

                if (isValidEmail(email)) break;

                setColor(12);
                cout << "\nError: Email must contain '@'!" << endl;
                Sleep(1500);
            }

            cout << "Username: ";
            cin >> username;

            while (true) {
                cout << "Password (min 8 chars, only letters & numbers): ";
                cin >> password;

                int check = checkPassword(password);
                if (check == 0) break;

                setColor(12);
                if (check == 1) {
                    cout << "\nError: Password must be at least 8 characters!" << endl;
                }
                else {
                    cout << "\nError: Password can only contain letters and numbers!" << endl;
                }
                Sleep(1500);
            }

            ofstream file("user.txt", ios::app);
            if (file.is_open()) {
                file << email << " " << username << " " << password << " 0" << endl;
                file.close();
                setColor(10);
                cout << "\nAccount created successfully!" << endl;
            }
            else {
                setColor(12);
                cout << "Error: Could not open user.txt!" << endl;
            }

            Sleep(2000);
        }
        else if (choice == 3) {
            setColor(10);
            cout << "\nExiting program..." << endl;
            Sleep(1000);
            return 0;
        }
        else {
            setColor(12);
            cout << "\nInvalid choice! Try again." << endl;
            Sleep(1000);
        }
    }
}
