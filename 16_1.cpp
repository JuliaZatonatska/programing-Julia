#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

const int MAX_ACQUAINTANCES = 100;
const string PHONEBOOK_FILENAME = "phonebook.txt";

class Person {
private:
    string name;
    unsigned birthYear;

public:
    Person(string n = "", unsigned y = 0) : name(n), birthYear(y) {}
    virtual ~Person() {}

    string getName() const { return name; }
    unsigned getBirthYear() const { return birthYear; }

    virtual int input();
    virtual void show() const;

    friend istream& operator>>(istream& is, Person& p);
    friend ostream& operator<<(ostream& os, const Person& p);
};

int Person::input() {
    cout << "    Enter Last Name/First Name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (!getline(cin, name)) return 0;

    cout << "    Enter Birth Year (XXXX): ";
    if (!(cin >> birthYear)) return 0;

    return 1;
}

void Person::show() const {
    cout << "Last Name/First Name: " << name << ", Birth Year: " << birthYear;
}

istream& operator>>(istream& is, Person& p) {
    if (&is == &cin) {
        p.input();
    } else {
        is >> p.name >> p.birthYear;
    }
    return is;
}

ostream& operator<<(ostream& os, const Person& p) {
    if (&os == &cout) {
        p.show();
    } else {
        os << p.name << " " << p.birthYear;
    }
    return os;
}

class Acquaintance : public Person {
private:
    string phoneNumber;

public:
    Acquaintance(string n = "", unsigned y = 0, string phone = "N/A")
        : Person(n, y), phoneNumber(phone) {}

    string getPhoneNumber() const { return phoneNumber; }
    void setPhoneNumber(const string& newPhone) { phoneNumber = newPhone; }

    int input() override;
    void show() const override;

    friend istream& operator>>(istream& is, Acquaintance& a);
    friend ostream& operator<<(ostream& os, const Acquaintance& a);
};

int Acquaintance::input() {
    cout << "Entering Acquaintance data:\n";
    if (!Person::input()) return 0;

    cout << "    Enter Phone Number: ";
    if (!(cin >> phoneNumber)) return 0;

    return 1;
}

void Acquaintance::show() const {
    Person::show();
    cout << ", Phone: " << phoneNumber << endl;
}

istream& operator>>(istream& is, Acquaintance& a) {
    is >> static_cast<Person&>(a);

    is >> a.phoneNumber;

    return is;
}

ostream& operator<<(ostream& os, const Acquaintance& a) {
    if (&os == &cout) {
        a.show();
    } else {
        os << a.getName() << " " << a.getBirthYear() << " " << a.phoneNumber << endl;
    }
    return os;
}

class PhoneBook {
private:
    vector<Acquaintance> contacts;

    void saveToFile() const {
        ofstream ofs(PHONEBOOK_FILENAME);
        if (ofs.is_open()) {
            for (const auto& a : contacts) {
                ofs << a;
            }
            ofs.close();
        } else {
            cerr << "Error: Could not open file for writing: " << PHONEBOOK_FILENAME << endl;
        }
    }

    void loadFromFile() {
        ifstream ifs(PHONEBOOK_FILENAME);
        if (ifs.is_open()) {
            contacts.clear();
            Acquaintance a;
            while (ifs >> a && contacts.size() < MAX_ACQUAINTANCES) {
                contacts.push_back(a);
            }
            ifs.close();
            cout << "\n>>> Phonebook loaded. Contacts: " << contacts.size() << endl;
        } else {
            cout << "\n>>> Phonebook file not found or empty. Creating a new one." << endl;
        }
    }

public:
    PhoneBook() {
        loadFromFile();
    }

    ~PhoneBook() {
        saveToFile();
        cout << "\n>>> Phonebook saved to file " << PHONEBOOK_FILENAME << endl;
    }

    void addAcquaintance() {
        if (contacts.size() >= MAX_ACQUAINTANCES) {
            cout << "!!! Phonebook is full (Max. " << MAX_ACQUAINTANCES << " entries)." << endl;
            return;
        }

        Acquaintance newContact;
        cout << "\n--- Adding new acquaintance ---\n";
        cin >> newContact;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "!!! Input error. Addition canceled." << endl;
            return;
        }

        contacts.push_back(newContact);
        cout << "\n>>> Acquaintance " << newContact.getName() << " successfully added." << endl;
    }

    void findPhoneNumber() const {
        string searchName;
        cout << "\n--- Find Phone Number ---\n";
        cout << "Enter Last Name/First Name to search: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, searchName);

        auto it = find_if(contacts.begin(), contacts.end(),
            [&searchName](const Acquaintance& a) {
                return a.getName() == searchName;
            });

        if (it != contacts.end()) {
            cout << "\nFound: ";
            cout << *it;
        } else {
            cout << "\n!!! Acquaintance named '" << searchName << "' not found." << endl;
        }
    }

    void replacePhoneNumber() {
        string searchName;
        cout << "\n--- Replace Phone Number ---\n";
        cout << "Enter Last Name/First Name whose number needs to be changed: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, searchName);

        auto it = find_if(contacts.begin(), contacts.end(),
            [&searchName](const Acquaintance& a) {
                return a.getName() == searchName;
            });

        if (it != contacts.end()) {
            string newPhone;
            cout << "Current number: " << it->getPhoneNumber() << endl;
            cout << "Enter new phone number: ";
            cin >> newPhone;

            it->setPhoneNumber(newPhone);
            cout << "\n>>> Phone number for " << it->getName() << " successfully changed." << endl;
        } else {
            cout << "\n!!! Acquaintance named '" << searchName << "' not found." << endl;
        }
    }

    void showAll() const {
        cout << "\n==========================================";
        cout << "\n          Phone Book                      ";
        cout << "\n==========================================";
        if (contacts.empty()) {
            cout << "\nPhonebook is empty." << endl;
            return;
        }
        for (size_t i = 0; i < contacts.size(); ++i) {
            cout << "[" << i + 1 << "] ";
            cout << contacts[i];
        }
        cout << "==========================================\n";
    }

    void menu() {
        int choice;
        do {
            cout << "\n--- Phone Book Menu ---\n";
            cout << "1. Show all entries\n";
            cout << "2. Add entry\n";
            cout << "3. Find number by Last Name\n";
            cout << "4. Replace phone number\n";
            cout << "0. Exit (Data will be saved)\n";
            cout << "Your choice: ";

            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                choice = -1;
            }

            switch (choice) {
                case 1: showAll(); break;
                case 2: addAcquaintance(); break;
                case 3: findPhoneNumber(); break;
                case 4: replacePhoneNumber(); break;
                case 0: cout << "Exiting...\n"; break;
                default: cout << "Invalid choice. Try again.\n"; break;
            }
        } while (choice != 0);
    }
};

int main() {

    PhoneBook myBook;

    myBook.menu();

    return 0;
}