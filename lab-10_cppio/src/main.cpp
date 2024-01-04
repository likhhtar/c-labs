#include <iostream>
#include <cassert>
#include "employees.h"

int main() {
    EmployeesArray array;
    std::string command;

    while (std::cin >> command) {
        if (command == "exit"){
            break;
        }
        else if (command == "load") {
            std::string path;
            std::cin >> path;
            std::ifstream file(path, std::ios::in | std::ios::binary);
            file >> array;
            file.close();
        }
        else if (command == "save") {
            std::string path;
            std::cin >> path;
            std::ofstream file(path, std::ios::out | std::ios::binary);
            file << array;
            file.close();
        }
        else if (command == "add") {
            std::cin >> array;
        }
        else if (command == "list") {
            std::cout << array;
        }
        else {
            assert(1);
        }
    }

    return 0;
}