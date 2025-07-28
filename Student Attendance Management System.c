#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_NAME 50

// Structure for student details
struct Student {
    int id;
    char name[MAX_NAME];
};

// Structure for attendance record
struct Attendance {
    int student_id;
    char date[11]; // Format: YYYY-MM-DD
    int status;    // 1 for present, 0 for absent
};

// Global arrays to store data
struct Student students[MAX_STUDENTS];
struct Attendance attendance[MAX_STUDENTS * 30]; // Assuming 30 days max
int student_count = 0;
int attendance_count = 0;

// Function prototypes
void addStudent();
void markAttendance();
void viewAttendance();
void saveData();
void loadData();
int findStudent(int id);

int main() {
    loadData(); // Load existing data from file
    int choice;
    char continue_program;

    do {
        // Display menu
        printf("\nStudent Attendance Management System\n");
        printf("1. Add Student\n");
        printf("2. Mark Attendance\n");
        printf("3. View Attendance\n");
        printf("4. Exit\n");
        printf("Enter your choice (1-4): ");
        scanf("%d", &choice);

        // Process user choice
        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                markAttendance();
                break;
            case 3:
                viewAttendance();
                break;
            case 4:
                saveData();
                printf("Exiting program. Data saved.\n");
                return 0;
            default:
                printf("Invalid choice! Please select a valid option.\n");
        }

        printf("Do you want to continue? (y/n): ");
        scanf(" %c", &continue_program);
    } while (continue_program == 'y' || continue_program == 'Y');

    saveData(); // Save data before exiting
    return 0;
}

void addStudent() {
    if (student_count >= MAX_STUDENTS) {
        printf("Error: Maximum student limit reached!\n");
        return;
    }

    struct Student new_student;
    printf("Enter student ID: ");
    scanf("%d", &new_student.id);

    // Check for duplicate ID
    if (findStudent(new_student.id) != -1) {
        printf("Error: Student ID already exists!\n");
        return;
    }

    printf("Enter student name: ");
    scanf(" %[^\n]s", new_student.name); // Read string with spaces

    students[student_count++] = new_student;
    printf("Student added successfully!\n");
}

void markAttendance() {
    int id, status;
    char date[11];

    printf("Enter student ID: ");
    scanf("%d", &id);

    int student_index = findStudent(id);
    if (student_index == -1) {
        printf("Error: Student ID not found!\n");
        return;
    }

    printf("Enter date (YYYY-MM-DD): ");
    scanf("%s", date);
    printf("Enter status (1 for present, 0 for absent): ");
    scanf("%d", &status);

    if (status != 0 && status != 1) {
        printf("Error: Invalid status! Use 1 for present, 0 for absent.\n");
        return;
    }

    struct Attendance record = {id, "", status};
    strcpy(record.date, date);
    attendance[attendance_count++] = record;
    printf("Attendance marked successfully!\n");
}

void viewAttendance() {
    int id;
    printf("Enter student ID (or 0 for all students): ");
    scanf("%d", &id);

    if (id == 0) {
        for (int i = 0; i < attendance_count; i++) {
            int student_index = findStudent(attendance[i].student_id);
            if (student_index != -1) {
                printf("Student: %s, ID: %d, Date: %s, Status: %s\n",
                       students[student_index].name,
                       attendance[i].student_id,
                       attendance[i].date,
                       attendance[i].status ? "Present" : "Absent");
            }
        }
    } else {
        int student_index = findStudent(id);
        if (student_index == -1) {
            printf("Error: Student ID not found!\n");
            return;
        }

        printf("Attendance for %s (ID: %d):\n", students[student_index].name, id);
        int present = 0, total = 0;
        for (int i = 0; i < attendance_count; i++) {
            if (attendance[i].student_id == id) {
                printf("Date: %s, Status: %s\n",
                       attendance[i].date,
                       attendance[i].status ? "Present" : "Absent");
                total++;
                if (attendance[i].status) present++;
            }
        }
        if (total > 0) {
            float percentage = (float)present / total * 100;
            printf("Attendance Percentage: %.2f%%\n", percentage);
        } else {
            printf("No attendance records found.\n");
        }
    }
}

int findStudent(int id) {
    for (int i = 0; i < student_count; i++) {
        if (students[i].id == id) return i;
    }
    return -1;
}

void saveData() {
    FILE *student_file = fopen("students.txt", "w");
    if (student_file) {
        for (int i = 0; i < student_count; i++) {
            fprintf(student_file, "%d,%s\n", students[i].id, students[i].name);
        }
        fclose(student_file);
    }

    FILE *attendance_file = fopen("attendance.txt", "w");
    if (attendance_file) {
        for (int i = 0; i < attendance_count; i++) {
            fprintf(attendance_file, "%d,%s,%d\n",
                    attendance[i].student_id, attendance[i].date, attendance[i].status);
        }
        fclose(attendance_file);
    }
}

void loadData() {
    FILE *student_file = fopen("students.txt", "r");
    if (student_file) {
        while (student_count < MAX_STUDENTS &&
               fscanf(student_file, "%d,%[^\n]\n",
                      &students[student_count].id,
                      students[student_count].name) == 2) {
            student_count++;
        }
        fclose(student_file);
    }

    FILE *attendance_file = fopen("attendance.txt", "r");
    if (attendance_file) {
        while (attendance_count < MAX_STUDENTS * 30 &&
               fscanf(attendance_file, "%d,%[^,],%d\n",
                      &attendance[attendance_count].student_id,
                      attendance[attendance_count].date,
                      &attendance[attendance_count].status) == 3) {
            attendance_count++;
        }
        fclose(attendance_file);
    }
}