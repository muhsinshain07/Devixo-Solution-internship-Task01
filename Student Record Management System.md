# Student Record Management System

This project is a console-based student record management system written in C++. It was created for Task 01 of the Devixo Solutions C++ Programming Internship.

## Features

The program can add, display, search, update, and delete student records. It also saves records in `students.txt`, loads them automatically when it starts, and validates numeric and text input.

Each record contains a unique roll number, name, age, course, and phone number. Records are held in an array of `Student` structures while the program is running.

## Requirements

- C++17-compatible compiler
- A terminal or command prompt

## Build and run

From this folder, compile the source code with:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic student_record_system.cpp -o student_record_system
```

Run the program with:

```bash
./student_record_system
```

On Windows, run `student_record_system.exe` instead.

The program creates `students.txt` in its current directory. The file uses a pipe-separated format so that records can be loaded during the next execution.

## Menu options

1. **Add student** — creates a new record after checking that the roll number is unique.
2. **View students** — displays all stored records in a table.
3. **Search student** — finds a record by roll number.
4. **Update student** — changes the name, age, course, and phone number for an existing roll number.
5. **Delete student** — removes a record and shifts the remaining array elements.
6. **Save records** — writes the current array to `students.txt`.
0. **Exit** — saves the latest records before closing.

## Files

- `student_record_system.cpp` — source code.
- `students.txt` — runtime data file, created after the first save.
- `report.md` — short project report.
- `sample_output.txt` — example console session for output screenshots or documentation.

## Implementation notes

The implementation uses functions to keep each menu operation separate. `readInteger` rejects malformed or out-of-range numeric input, while `readNonEmpty` rejects blank values and the delimiter used by the data file. Malformed lines found in an existing data file are ignored rather than causing the program to terminate.
