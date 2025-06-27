#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <filesystem>

using namespace std;

int main(){
    string filename;
    string login;
    string site;
    int passwd_length;
    bool use_special_chars;
    bool use_numbers;
    string passwd;
    string user_name;

    // Ask for username and check if directory exists
    namespace fs = std::filesystem;
    string downloads_path;
    while (true) {
        cout << "Please enter your Username so we can save the file to Downloads -> ";
        cin >> user_name;
        downloads_path = "C:\\Users\\" + user_name + "\\Downloads";
        if (fs::exists(downloads_path)) {
            break;
        } else {
            cout << "That user does not exist or Downloads folder not found. Try again." << endl;
        }
    }

    cout << "Enter the site URL (optional, can be left blank): ";
    cin.ignore();
    getline(cin, site); 

    cout << "Enter the filename to save the login" << endl;
    cin >> filename;

    cout << "Enter the login (e-mail or username)" << endl;
    cin >> login;

    cout << "how long should the password be?" << endl;
    cin >> passwd_length;

    cout << "Do you want to use special characters? (1 for yes, 0 for no)" << endl;
    cin >> use_special_chars;

    cout << "Do you want to use numbers? (1 for yes, 0 for no)" << endl;
    cin >> use_numbers;

    // Define character sets
    const string lower = "abcdefghijklmnopqrstuvwxyz"; 
    const string upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const string digits = "0123456789";
    const string special_chars = "!@#$%^&*()-_=+[]{}|;:,.<>?";

    // Initialize random number generator
    random_device rd;
    mt19937 gen(rd());

    // Build charset based on user choices
    string charset = lower + upper;
    if (use_numbers) charset += digits;
    if (use_special_chars) charset += special_chars;

    uniform_int_distribution<> dis(0, charset.size() - 1);
    passwd = "";
    for (int i = 0; i < passwd_length; ++i) {
        passwd += charset[dis(gen)];
    }
    string full_path = downloads_path + "\\" + filename + ".txt"; // Combine the path and filename;

    ofstream file(full_path);
    if (file.is_open()) {
        file << "Site URL: " << site << endl << endl;
        file << "Login: " << login << endl << endl;
        file << "Password: " << passwd << endl << endl;
        file.close();
        cout << "Saved to file." << endl;
    } else {
        cout << "Failed to open file." << endl;
    }

    cout << "file saved to path: " << full_path << endl;
    cout << "Your password is: " << passwd << endl;
    cout << "Press Enter to exit...";
    cin.ignore(); 
    cin.get();
    exit(0);
    return 0;
}