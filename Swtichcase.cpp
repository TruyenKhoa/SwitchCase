#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

struct Employee {
    int id;
    std::string name;
    float salary;
};

bool isNameValid(const std::string& name) {
    for (char c : name) {
        if (!isalpha(c) && c != ' ') {
            return false;
        }
    }
    return !name.empty();
}

bool isNumber(const std::string& s) {
    if (s.empty()) return false;
    size_t i = 0;
    if (s[0] == '-' || s[0] == '+') i = 1;
    bool decimalPointFound = false;
    for (; i < s.size(); ++i) {
        if (!isdigit(s[i])) {
            if (s[i] == '.' && !decimalPointFound) {
                decimalPointFound = true;
            } else {
                return false;
            }
        }
    }
    return true;
}

int main() {
    std::vector<Employee> employees;
    int choice;

    while (true) {
        std::cout << "\t\t===========MENU==========\n";
        std::cout << "1. Insert an employee into the list\n";
        std::cout << "2. Check if the list is empty\n";
        std::cout << "3. Display all the employees in the list\n";
        std::cout << "4. Sort employees in the list\n";
        std::cout << "5. Exit the program\n";
        std::cout << "\t\t=========================\n\n";
        std::cout << "Enter your choice: ";
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1) {
            Employee e;

            std::string input;

            while (true) {
                std::cout << "Enter employee ID: ";
                std::getline(std::cin, input);
                if (isNumber(input)) {
                    try {
                        e.id = std::stoi(input);
                        bool exists = false;
                        for (const auto& emp : employees) {
                            if (emp.id == e.id) {
                                exists = true;
                                break;
                            }
                        }
                        if (exists) {
                            std::cout << "Error: Employee with ID " << e.id << " already exists.\n";
                            continue;
                        }
                        break;
                    } catch (...) {
                        std::cout << "Invalid input. Please enter a valid number for ID.\n";
                    }
                } else {
                    std::cout << "Invalid input. Please enter a valid number for ID.\n";
                }
            }

            while (true) {
                std::cout << "Enter employee name: ";
                std::getline(std::cin, e.name);
                if (isNameValid(e.name)) {
                    break;
                } else {
                    std::cout << "Invalid name. Please enter letters and spaces only.\n";
                }
            }

            while (true) {
                std::cout << "Enter employee salary: ";
                std::getline(std::cin, input);
                try {
                    if (input.empty() || !isNumber(input)) {
                        throw std::invalid_argument("Invalid");
                    }
                    e.salary = std::stof(input);
                    break;
                } catch (...) {
                    std::cout << "Invalid input. Please enter a valid salary.\n";
                }
            }

            employees.insert(employees.begin(), e);
        }
        else if (choice == 2) {
            if (employees.empty()) {
                std::cout << "The list is empty.\n";
            } else {
                std::cout << "The list is not empty.\n";
            }
        }
        else if (choice == 3) {
            if (employees.empty()) {
                std::cout << "The list is empty.\n";
            } else {
                std::cout << "Employees:\n";
                for (const auto& emp : employees) {
                    std::cout << "ID: " << emp.id << ", Name: " << emp.name << ", Salary: " << emp.salary << "\n";
                }
            }
        }
        else if (choice == 4) {
            std::sort(employees.begin(), employees.end(), [](const Employee& a, const Employee& b) {
                return a.id < b.id;
            });
            std::cout << "Employees sorted by ID.\n";
        }
        else if (choice == 5) {
            break;
        }
        else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}
