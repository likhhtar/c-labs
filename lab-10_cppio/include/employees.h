#ifndef LAB10_EMPLOYEES_H_INCLUDED
#define LAB10_EMPLOYEES_H_INCLUDED

#include <cstdint>
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include "bin_manip.h"

class Employee {
public:
    const int _max_name_length = 120;

    Employee();
    explicit Employee(const char *name, int32_t base_salary);
    virtual ~Employee();
    virtual int salary() const = 0;
    friend std::ostream &operator<<(std::ostream &out, const Employee &employee);
    friend std::istream &operator>>(std::istream &in, Employee &employee);
    friend std::ofstream &operator<<(std::ofstream &out, const Employee &employee) ;
    friend std::ifstream &operator >>(std::ifstream &in, Employee &employee);

    virtual std::ostream &write_to_ostream(std::ostream &out) const;
    virtual std::ofstream &write_to_ofstream(std::ofstream &out) const;
    virtual std::istream &read_from_istream(std::istream &in);
    virtual std::ifstream &read_from_ifstream(std::ifstream &in);
protected:
    char* _name;
    int32_t _base_salary;
};

class Developer : public Employee{
public:
    Developer();

    Developer(const char* name, int32_t base_salary, bool has_bonus);
    int salary() const;

    std::ostream &write_to_ostream(std::ostream &out) const;
    std::ofstream &write_to_ofstream(std::ofstream &out) const;
    std::istream &read_from_istream(std::istream &in);
    std::ifstream &read_from_ifstream(std::ifstream &in);

    Developer(std::ifstream &in);
    Developer(std::istream &in);
private:
  bool _has_bonus;
};

class SalesManager : public Employee{
public:
    SalesManager();
    SalesManager(const char* name, int32_t base_salary, int32_t sold_items, int32_t price);
    int salary() const;


    std::ostream &write_to_ostream(std::ostream &out) const;
    std::ofstream &write_to_ofstream(std::ofstream &out) const;
    std::istream &read_from_istream(std::istream &in);
    std::ifstream &read_from_ifstream(std::ifstream &in);

    SalesManager(std::ifstream &in);
    SalesManager(std::istream &in);
private:
  int32_t _sold_items, _price;
};

class EmployeesArray {
public:
    EmployeesArray();
    ~EmployeesArray();
    void add(const Employee* e);
    int total_salary() const;
    friend std::ostream& operator<<(std::ostream& out, const EmployeesArray& ea);
    friend std::ofstream& operator<<(std::ofstream& out, const EmployeesArray& ea);
    friend std::ifstream& operator>>(std::ifstream& in, EmployeesArray& ea);
    friend std::istream& operator>>(std::istream& in, EmployeesArray& ea);
private:
  std::vector<Employee*> _employees;
  int32_t _size;
};

#endif
