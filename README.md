Student Attendance Management System
A C program for managing student attendance with data persistence.
Description
This program allows users to add students, mark attendance, view attendance records for individual students or all students, and save/load data to/from files (students.txt and attendance.txt). It supports up to 100 students and 30 days of attendance records.
How to Use

Compile the program using a C compiler (e.g., gcc StudentAttendance.c -o StudentAttendance).
Run the executable (e.g., ./StudentAttendance on Linux or StudentAttendance.exe on Windows).
Choose options from the menu to:
Add a student (ID and name).
Mark attendance (student ID, date, status: present/absent).
View attendance for a specific student or all students.
Exit (saves data automatically).


Data is saved to students.txt and attendance.txt and loaded on startup.

Example
Student Attendance Management System
1. Add Student
2. Mark Attendance
3. View Attendance
4. Exit
Enter your choice (1-4): 1
Enter student ID: 101
Enter student name: John Doe
Student added successfully!

License
This project is licensed under the MIT License. See the LICENSE file for details.
