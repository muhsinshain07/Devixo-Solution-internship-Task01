#include <algorithm>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

using namespace std;

const int MAX_STUDENTS = 100;
const string DATA_FILE = "students.txt";

struct Student {
    int rollNumber{};
    string name;
    int age{};
    string course;
    string phone;
};

string trim(const string& text) {
    const size_t first = text.find_first_not_of(" \t\r\n");
    if (first == string::npos) {
        return "";
    }

    const size_t last = text.find_last_not_of(" \t\r\n");
    return text.substr(first, last - first + 1);
}

string readNonEmpty(const string& prompt) {
    string value;

    while (true) {
        cout << prompt;
        getline(cin, value);
        value = trim(value);

        if (!value.empty() && value.find('|') == string::npos) {
            return value;
        }

        cout << "Please enter a valid value without the '|' character.\n";
    }
}

int readInteger(const string& prompt, int minimum, int maximum) {
    string input;
    int value;

    while (true) {
        cout << prompt;
        getline(cin, input);
        stringstream converter(input);
        char extraCharacter;

        if ((converter >> value) && !(converter >> extraCharacter) &&
            value >= minimum && value <= maximum) {
            return value;
        }

        cout << "Enter a whole number between " << minimum << " and " << maximum << ".\n";
    }
}

void loadStudents(Student students[], int& count) {
    ifstream input(DATA_FILE);
    string line;
    count = 0;

    while (getline(input, line) && count < MAX_STUDENTS) {
        stringstream row(line);
        string roll, name, age, course, phone;

        if (getline(row, roll, '|') && getline(row, name, '|') &&
            getline(row, age, '|') && getline(row, course, '|') &&
            getline(row, phone)) {
            try {
                Student student;
                student.rollNumber = stoi(roll);
                student.name = name;
                student.age = stoi(age);
                student.course = course;
                student.phone = phone;

                if (student.rollNumber > 0 && student.age > 0) {
                    students[count++] = student;
                }
            } catch (const exception&) {
                // Ignore malformed records instead of stopping the application.
            }
        }
    }
}

bool saveStudents(const Student students[], int count) {
    ofstream output(DATA_FILE);

    if (!output) {
        return false;
    }

    for (int index = 0; index < count; ++index) {
        output << students[index].rollNumber << '|'
               << students[index].name << '|'
               << students[index].age << '|'
               << students[index].course << '|'
               << students[index].phone << '\n';
    }

    return true;
}

int findStudent(const Student students[], int count, int rollNumber) {
    for (int index = 0; index < count; ++index) {
        if (students[index].rollNumber == rollNumber) {
            return index;
        }
    }

    return -1;
}

void printStudent(const Student& student) {
    cout << "Roll number : " << student.rollNumber << '\n'
         << "Name        : " << student.name << '\n'
         << "Age         : " << student.age << '\n'
         << "Course      : " << student.course << '\n'
         << "Phone       : " << student.phone << '\n';
}

void addStudent(Student students[], int& count) {
    if (count == MAX_STUDENTS) {
        cout << "The record list is full.\n";
        return;
    }

    cout << "\n--- Add Student ---\n";
    const int rollNumber = readInteger("Roll number: ", 1, 1000000);

    if (findStudent(students, count, rollNumber) != -1) {
        cout << "A student with that roll number already exists.\n";
        return;
    }

    Student student;
    student.rollNumber = rollNumber;
    student.name = readNonEmpty("Name: ");
    student.age = readInteger("Age: ", 3, 100);
    student.course = readNonEmpty("Course: ");
    student.phone = readNonEmpty("Phone: ");

    students[count++] = student;
    saveStudents(students, count);
    cout << "Student added and records saved.\n";
}

void viewStudents(const Student students[], int count) {
    cout << "\n--- Student Records ---\n";

    if (count == 0) {
        cout << "No student records are available.\n";
        return;
    }

    cout << left << setw(12) << "Roll No."
         << setw(24) << "Name"
         << setw(8) << "Age"
         << setw(22) << "Course"
         << "Phone\n";
    cout << string(78, '-') << '\n';

    for (int index = 0; index < count; ++index) {
        cout << left << setw(12) << students[index].rollNumber
             << setw(24) << students[index].name.substr(0, 22)
             << setw(8) << students[index].age
             << setw(22) << students[index].course.substr(0, 20)
             << students[index].phone << '\n';
    }
}

void searchStudent(const Student students[], int count) {
    cout << "\n--- Search Student ---\n";
    const int rollNumber = readInteger("Enter roll number: ", 1, 1000000);
    const int position = findStudent(students, count, rollNumber);

    if (position == -1) {
        cout << "No student was found with that roll number.\n";
        return;
    }

    printStudent(students[position]);
}

void updateStudent(Student students[], int count) {
    cout << "\n--- Update Student ---\n";
    const int rollNumber = readInteger("Enter roll number: ", 1, 1000000);
    const int position = findStudent(students, count, rollNumber);

    if (position == -1) {
        cout << "No student was found with that roll number.\n";
        return;
    }

    Student& student = students[position];
    cout << "Enter the new details for this student.\n";
    student.name = readNonEmpty("Name: ");
    student.age = readInteger("Age: ", 3, 100);
    student.course = readNonEmpty("Course: ");
    student.phone = readNonEmpty("Phone: ");

    saveStudents(students, count);
    cout << "Student updated and records saved.\n";
}

void deleteStudent(Student students[], int& count) {
    cout << "\n--- Delete Student ---\n";
    const int rollNumber = readInteger("Enter roll number: ", 1, 1000000);
    const int position = findStudent(students, count, rollNumber);

    if (position == -1) {
        cout << "No student was found with that roll number.\n";
        return;
    }

    for (int index = position; index < count - 1; ++index) {
        students[index] = students[index + 1];
    }
    --count;

    saveStudents(students, count);
    cout << "Student deleted and records saved.\n";
}

void printMenu() {
    cout << "\n========================================\n"
         << "       STUDENT RECORD MANAGEMENT       \n"
         << "========================================\n"
         << "1. Add student\n"
         << "2. View students\n"
         << "3. Search student\n"
         << "4. Update student\n"
         << "5. Delete student\n"
         << "6. Save records\n"
         << "0. Exit\n"
         << "========================================\n";
}

int main() {
    Student students[MAX_STUDENTS];
    int count = 0;
    loadStudents(students, count);

    cout << "Loaded " << count << " student record(s).\n";

    while (true) {
        printMenu();
        const int choice = readInteger("Choose an option: ", 0, 6);

        switch (choice) {
            case 1:
                addStudent(students, count);
                break;
            case 2:
                viewStudents(students, count);
                break;
            case 3:
                searchStudent(students, count);
                break;
            case 4:
                updateStudent(students, count);
                break;
            case 5:
                deleteStudent(students, count);
                break;
            case 6:
                cout << (saveStudents(students, count)
                             ? "Records saved successfully.\n"
                             : "Unable to save records.\n");
                break;
            case 0:
                saveStudents(students, count);
                cout << "Thank you for using the system. Goodbye!\n";
                return 0;
        }
    }
}
