#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include "matrix.hpp"

std::map<std::string, Matrix*> matrices;

void do_load() {
    std::string reg, filename;
    std::cin >> reg >> filename;

    Matrix* m;
    m = Matrix::load(filename);

    delete matrices[reg];
    matrices[reg] = m;
}

void do_print() {
    std::string reg;
    std::cin >> reg;
    matrices[reg]->print(stdout);
}

void do_add() {
    std::string reg1, reg2;
    std::cin >> reg1 >> reg2;
    *matrices[reg1] += *matrices[reg2];
}

void do_mul() {
    std::string reg1, reg2;
    std::cin >> reg1 >> reg2;
    *matrices[reg1] *= *matrices[reg2];
}

void do_elem() {
    std::string reg;
    std::string row, column;
    std::cin >> reg >> row >> column;
    std::cout << matrices[reg]->get(stoi(row), stoi(column)) << std::endl;
}

int main() {
    std::string cmd, reg;
    const int n = 10;
    for (int i = 0; i < n; i++) {
        reg = "$" + std::to_string(i);
        matrices[reg] = new Matrix();
    }

    while (std::cin >> cmd) {
        try{
            if(cmd == "exit") {
                break;
            }
            if (cmd == "load") {
                do_load();
            }
            else if (cmd == "print") {
               do_print();
            }
            else if (cmd == "add") {
                do_add();
            }
            else if (cmd == "mul") {
                do_mul();
            }
            else if (cmd == "elem") {
                do_elem();
            }
        }
        catch (const std::exception &e) {
            std::cout << e.what() << std::endl;
        }
    }

    for (auto u : matrices) {
        delete u.second;
    }
}