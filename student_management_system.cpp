#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Student {
public:
    int id;
    string name;
    int age;

    void input() {
        cout << "\nEnter Student ID: ";
        cin >> id;
        cin.ignore();

        cout << "Enter Student Name: ";
        getline(cin, name);

        cout << "Enter Student Age: ";
        cin >> age;
    }

    void display() {
        cout << "\nID: " << id;
        cout << "\nName: " << name;
        cout << "\nAge: " << age << endl;
    }
};

void addStudent() {
    Student s;
    ofstream file("students.txt", ios::app);

    s.input();

    file << s.id << endl;
    file << s.name << endl;
    file << s.age << endl;

    file.close();

    cout << "\nStudent Added Successfully!\n";
}

void displayStudents() {
    Student s;
    ifstream file("students.txt");

    if (!file) {
        cout << "\nNo Records Found!\n";
        return;
    }

    while (file >> s.id) {
        file.ignore();
        getline(file, s.name);
        file >> s.age;

        s.display();
    }

    file.close();
}

void searchStudent() {
    int searchId;
    bool found = false;

    cout << "\nEnter Student ID to Search: ";
    cin >> searchId;

    Student s;
    ifstream file("students.txt");

    while (file >> s.id) {
        file.ignore();
        getline(file, s.name);
        file >> s.age;

        if (s.id == searchId) {
            cout << "\nStudent Found:\n";
            s.display();
            found = true;
            break;
        }
    }

    file.close();

    if (!found) {
        cout << "\nStudent Not Found!\n";
    }
}

void deleteStudent() {
    int deleteId;
    bool found = false;

    cout << "\nEnter Student ID to Delete: ";
    cin >> deleteId;

    Student s;
    ifstream file("students.txt");
    ofstream temp("temp.txt");

    while (file >> s.id) {
        file.ignore();
        getline(file, s.name);
        file >> s.age;

        if (s.id != deleteId) {
            temp << s.id << endl;
            temp << s.name << endl;
            temp << s.age << endl;
        } else {
            found = true;
        }
    }

    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "\nStudent Deleted Successfully!\n";
    else
        cout << "\nStudent Not Found!\n";
}

int main() {
    int choice;

    do {
        cout << "\n====== Student Management System ======\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Exit\n";
        cout << "Enter Your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                deleteStudent();
                break;

            case 5:
                cout << "\nExiting Program...\n";
                break;

            default:
                cout << "\nInvalid Choice! Try Again.\n";
        }

    } while (choice != 5);

    return 0;
}
