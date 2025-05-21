#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee {
    int id;
    char name[25];
    float salary;
} records[5];

struct EmployeeList {
    struct Employee *employees;
    int size;
    int capacity;
};

void initializeList(struct EmployeeList *list) {
    list->employees = NULL;
    list->size = 0;
    list->capacity = 0;
}

int findEmployee(struct EmployeeList *list, int id) {
    for (int i = 0; i < list->size; i++) {
        if (list->employees[i].id == id) {
            return i;
        }
    }
    return -1;
}

void insertAtBeginning(struct EmployeeList *list, struct Employee employee) {
    if (findEmployee(list, employee.id) != -1) {
        printf("Error: Employee with ID %d already exists.\n", employee.id);
        return;
    }

    if (list->capacity == 0) {
        list->capacity = 5;
        list->employees = (struct Employee*)malloc(list->capacity * sizeof(struct Employee));
    } else if (list->size == list->capacity) {
        list->capacity *= 2;
        list->employees = (struct Employee*)realloc(list->employees, list->capacity * sizeof(struct Employee));
    }

    for (int i = list->size; i > 0; i--) {
        list->employees[i] = list->employees[i - 1];
    }

    list->employees[0] = employee;
    list->size++;
}

void sortEmployees(struct EmployeeList *list) {
    for (int i = 0; i < list->size - 1; i++) {
        for (int j = 0; j < list->size - i - 1; j++) {
            if (list->employees[j].id > list->employees[j + 1].id) {
                struct Employee temp = list->employees[j];
                list->employees[j] = list->employees[j + 1];
                list->employees[j + 1] = temp;
            }
        }
    }
}

int isEmpty(struct EmployeeList *list) {
    return list->size == 0;
}

void displayEmployees(struct EmployeeList *list) {
    if (isEmpty(list)) {
        printf("The list is empty.\n");
        return;
    }

    printf("Employees:\n");
    for (int i = 0; i < list->size; i++) {
        printf("ID: %d, Name: %s, Salary: %.2f\n",
               list->employees[i].id,
               list->employees[i].name,
               list->employees[i].salary);
    }
}

int main() {
    struct EmployeeList list;
    initializeList(&list);

    int choice;
    struct Employee employee;

    while (1) {
        printf("\n\t\t=========== MENU ===========\n");
        printf("1. Insert an employee into the list\n");
        printf("2. Check if the list is empty\n");
        printf("3. Display all the employees in the list\n");
        printf("4. Sort employees in the list\n");
        printf("5. Exit the program\n");
        printf("\t\t============================\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
            printf("Enter employee ID: ");
            if (scanf("%d", &employee.id) != 1) {
                printf("Invalid input. Please enter a number for the employee ID.\n\n");
                while (getchar() != '\n');
                break;
            }
            while (getchar() != '\n');

            printf("Enter employee name: ");
            while (1) {
                fgets(employee.name, sizeof(employee.name), stdin);

                size_t len = strlen(employee.name);
                if (len > 0 && employee.name[len - 1] == '\n') {
                    employee.name[len - 1] = '\0';
                }

                int valid = 1;
                for (int i = 0; i < strlen(employee.name); i++) {
                    if (!((employee.name[i] >= 'A' && employee.name[i] <= 'Z') ||
                        (employee.name[i] >= 'a' && employee.name[i] <= 'z') ||
                        employee.name[i] == ' ')) {
                        valid = 0;
                        break;
                    }
                }

                if (!valid || strlen(employee.name) == 0) {
                    printf("Invalid name. Please enter letters only (no numbers or special characters): ");
                } else {
                    break;
                }
            }

            char salaryInput[50];
            while (1) {
                printf("Enter employee salary: ");
                fgets(salaryInput, sizeof(salaryInput), stdin);

                size_t len = strlen(salaryInput);
                if (len > 0 && salaryInput[len - 1] == '\n') {
                    salaryInput[len - 1] = '\0';
                }

                if (sscanf(salaryInput, "%f", &employee.salary) != 1) {
                    printf("Invalid input. Please enter a valid salary.\n");
                } else {
                    break;
                }
            }

            insertAtBeginning(&list, employee);
            break;

            case 2:
                if (isEmpty(&list)) {
                    printf("The list is empty.\n");
                } else {
                    printf("The list is not empty.\n");
                }
                break;

            case 3:
                displayEmployees(&list);
                break;

            case 4:
                sortEmployees(&list);
                printf("Employees sorted by ID.\n");
                break;

            case 5:
                printf("Exiting program.\n");
                free(list.employees);
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
