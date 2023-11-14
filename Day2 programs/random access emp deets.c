#include <stdio.h>
#include <stdlib.h>

struct Employee {
    int id;
    char name[50];
    float salary;
};

void addEmployee(FILE* file, const struct Employee* emp) {
    fseek(file, 0, SEEK_END);
    fwrite(emp, sizeof(struct Employee), 1, file);
}

void readEmployee(FILE* file, int id) {
    struct Employee emp;
    int found = 0;

    fseek(file, 0, SEEK_SET);

    while (fread(&emp, sizeof(struct Employee), 1, file) == 1) {
        if (emp.id == id) {
            printf("Employee ID: %d\n", emp.id);
            printf("Name: %s\n", emp.name);
            printf("Salary: %.2f\n", emp.salary);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Employee with ID %d not found.\n", id);
    }
}

int main() {
    FILE* file;
    int choice;

    file = fopen("employee.dat", "rb+");

    if (file == NULL) {
        file = fopen("employee.dat", "wb+");
        if (file == NULL) {
            perror("Failed to create or open the file.");
            return 1;
        }
    }

    printf("Employee Details Management\n");

    while (1) {
        printf("Options:\n");
        printf("1. Add Employee\n");
        printf("2. Read Employee by ID\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                {
                    struct Employee emp;
                    printf("Enter Employee ID: ");
                    scanf("%d", &emp.id);
                    printf("Enter Employee Name: ");
                    scanf("%s", emp.name);
                    printf("Enter Employee Salary: ");
                    scanf("%f", &emp.salary);
                    addEmployee(file, &emp);
                }
                break;
            case 2:
                {
                    int id;
                    printf("Enter Employee ID to read: ");
                    scanf("%d", &id);
                    readEmployee(file, id);
                }
                break;
            case 3:
                printf("Exiting the program.\n");
                fclose(file);
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
