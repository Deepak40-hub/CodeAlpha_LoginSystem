#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_USERS = 100;

// Structure to store user info
struct User {
    string username;
    string password;
};

// Global array of users
User users[MAX_USERS];
int userCount = 0;

// Load users from file to array
void loadUsersFromFile() {
    ifstream file("users.txt");
    if (!file.is_open()) return;

    while (file >> users[userCount].username >> users[userCount].password) {
        userCount++;
    }

    file.close();
}

// Save all users to file
void saveUsersToFile() {
    ofstream file("users.txt");
    for (int i = 0; i < userCount; i++) {
        file << users[i].username << " " << users[i].password << "\n";
    }
    file.close();
}

// Check if username already exists
bool isUsernameTaken(const string& username) {
    for (int i = 0; i < userCount; i++) {
        if (users[i].username == username) return true;
    }
    return false;
}

// Register a new user
void registerUser() {
    string username, password;
    cout << "\n--- Register ---\n";
    cout << "Enter username: ";
    cin >> username;

    if (isUsernameTaken(username)) {
        cout << "Error: Username already taken.\n";
        return;
    }

    cout << "Enter password: ";
    cin >> password;

    users[userCount].username = username;
    users[userCount].password = password;
    userCount++;

    saveUsersToFile();  // Save to file
    cout << "Registration successful!\n";
}

// Login user
void loginUser() {
    string username, password;
    cout << "\n--- Login ---\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    for (int i = 0; i < userCount; i++) {
        if (users[i].username == username && users[i].password == password) {
            cout << "Login successful. Welcome, " << username << "!\n";
            return;
        }
    }

    cout << "Error: Invalid username or password.\n";
}

// Main menu
int main() {
    loadUsersFromFile(); // Load existing users
    int choice;

    do {
        cout << "\n--- Login & Registration System ---\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
