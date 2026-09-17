# Student Record Management System — Project Report

## 1. Introduction

The Student Record Management System is a menu-driven C++ console application. It provides the basic operations required to maintain student information and stores the records in a text file so that data remains available between program runs.

## 2. Objectives

The project applies fundamental C++ programming concepts in one small application. It uses variables, loops, functions, arrays, structures, file handling, formatted output, and input validation. The design also separates the responsibilities of loading, saving, searching, displaying, and modifying records.

## 3. Data design

A `Student` structure represents one record. It contains the student's roll number, name, age, course, and phone number. The active records are stored in a fixed-size array with room for 100 students. Roll numbers are treated as unique identifiers.

## 4. Program operation

When the application starts, it reads valid records from `students.txt`. The main loop then displays a menu and dispatches the selected operation to a dedicated function. Adding a student checks for duplicate roll numbers before inserting the record. Searching and updating use the same roll-number lookup function. Deleting shifts later array elements left so that the active records remain contiguous.

The save operation writes each record as one pipe-separated line. The program saves after an add, update, or delete operation, and it also saves before exit. Text input is checked for blank values, while numeric input is checked for a valid integer and an acceptable range.

## 5. Functions used

| Function | Responsibility |
| --- | --- |
| `loadStudents` | Reads records from the data file at startup. |
| `saveStudents` | Writes the current records to the data file. |
| `findStudent` | Locates a student by roll number. |
| `addStudent` | Validates and inserts a new student. |
| `viewStudents` | Prints all records in a formatted table. |
| `searchStudent` | Displays one matching record. |
| `updateStudent` | Replaces the editable fields of an existing record. |
| `deleteStudent` | Removes a record and compacts the array. |
| `readInteger` and `readNonEmpty` | Provide reusable input validation. |

## 6. Testing

The source was compiled with C++17 using warnings enabled. The test session covered starting with no records, adding a student, displaying the record, searching by roll number, updating the record, deleting it, saving, and exiting. The program also rejects duplicate roll numbers and invalid numeric input.

## 7. Conclusion

The completed application satisfies the requested features for the internship task. It has a clear menu, reusable functions, a structure-based data model, array processing, formatted output, validation, and persistent file storage. The source is intentionally kept within standard C++ facilities so that it can be compiled on common development environments.
