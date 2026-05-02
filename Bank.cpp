#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
using namespace std;

// Function to generate next Admin ID in format ADM001
string generateAdminID(const string &filename) {
    ifstream file(filename.c_str());
    int lastID = 0;
    string line;

    while (getline(file, line)) {
        if (line.empty()) continue;
        size_t pos = line.find(','); // first field is ID
        if (pos != string::npos) {
            string idStr = line.substr(0, pos);
            // Remove prefix "ADM" if present
            if (idStr.substr(0, 3) == "ADM") {
                idStr = idStr.substr(3);
            }
            int id;
            stringstream ss(idStr);
            ss >> id;
            if (id > lastID) lastID = id;
        }
    }
    file.close();

    lastID++; // next ID

    // Format as ADM + 3 digits
    stringstream ss;
    ss << "ADM";
    if (lastID < 10) ss << "00" << lastID;
    else if (lastID < 100) ss << "0" << lastID;
    else ss << lastID;

    return ss.str();
}

// Function to generate a simple password
string generatePassword() {
    int num = rand() % 9000 + 1000; // random 1000-9999
    stringstream ss;
    ss << "pass" << num;
    return ss.str();
}

int main() {
    srand(time(0)); // initialize random seed

    string name, phone, cnic;
    string adminID, password;
    int rolechoice, option;
    string filename = "admin_data.txt";

    cout << "Welcome to Bank Management System\n";

    while (true) {
        cout << "\nSelect Role:\n1. Admin\n2. User\n3. Exit\nEnter choice: ";
        cin >> rolechoice;

        if (rolechoice == 1) {
            cout << "1. Signup (New Admin)\n2. Login\nEnter option: ";
            cin >> option;

            if (option == 1) {
                cin.ignore(); // ignore leftover '\n'

                cout << "Enter your Name: ";
                getline(cin, name);

                cout << "Enter Your Phone No: ";
                getline(cin, phone);

                cout << "Enter your CNIC: ";
                getline(cin, cnic);

                // Generate Bank ID and Password
                adminID = generateAdminID(filename);
                password = generatePassword();

                cout << "\nSign Up Successful!\n";
                cout << "Your BANK ID: " << adminID << endl;
                cout << "Your Password: " << password << endl;

                // Save admin info to file
                ofstream outfile(filename.c_str(), ios::app);
                outfile << adminID << "," << password << "," << name << "," << phone << "," << cnic << endl;
                outfile.close();
            }
        }
        else if (rolechoice == 3) {
            cout << "Exiting program.\n";
            break;
        }
        else {
            cout << "Invalid choice! Please select again.\n";	
        }
    }

    return 0;
}

