#include "employees.h"
#include "bin_manip.h"

// EMPLOYEE
Employee::Employee(const char *name, int32_t base_salary){
    _name = new char[strlen(name) + 1];
    strcpy(_name, name);
    _base_salary = base_salary;
}

Employee::Employee() {
    _name = nullptr;
    _base_salary = 0;
}

Employee::~Employee() {
    delete[] _name;
}

std::ostream &operator<<(std::ostream &out, const Employee &employee) {
    return employee.write_to_ostream(out);
}

std::ofstream &operator<<(std::ofstream &out, const Employee &employee) {
    return employee.write_to_ofstream(out);
}

std::istream &operator>>(std::istream &in, Employee &employee) {
    return employee.read_from_istream(in);
}

std::ifstream &operator>>(std::ifstream &in, Employee &employee) {
    return employee.read_from_ifstream(in);
}

std::istream &Employee::read_from_istream(std::istream &in){
    char name[_max_name_length + 1];
    in >> name >> _base_salary;
    delete _name;
    _name = new char[strlen(name) + 1];
    strcpy(_name, name);
    return in;
}

std::ifstream &Employee::read_from_ifstream(std::ifstream &in){
    char name[_max_name_length + 1];
    in >> read_c_str(name, _max_name_length * sizeof(char))
       >> read_le_int32(_base_salary);
    delete _name;
    _name = new char[strlen(name) + 1];
    strcpy(_name, name);
    return in;
}

std::ostream &Employee::write_to_ostream(std::ostream &out) const {
    out << "Name: " << _name << std::endl
        << "Base Salary: " << _base_salary << std::endl;
    return out;
}

std::ofstream &Employee::write_to_ofstream(std::ofstream &out) const {
    out << write_c_str(_name)
        << write_le_int32(_base_salary);
    return out;
}


// DEVELOPER
Developer::Developer(const char* name, int32_t base_salary, bool has_bonus) : Employee (name, base_salary) {
    _has_bonus = has_bonus;
}

int Developer::salary() const {
    int salary = _base_salary;
    if (_has_bonus) { salary += 1000; }
    return salary;
}

std::ostream &Developer::write_to_ostream(std::ostream &out) const {
    out << "Developer" << std::endl;
    Employee::write_to_ostream(out);
    out << "Has bonus: " << (_has_bonus ? '+' : '-') << std::endl;
    return out;
}

std::ofstream &Developer::write_to_ofstream(std::ofstream &out) const {
    out << write_le_int32(1);
    Employee::write_to_ofstream(out);
    out << write_bool(_has_bonus);
    return out;
}

std::istream &Developer::read_from_istream(std::istream &in) {
    Employee::read_from_istream(in);
    in >> _has_bonus;
    return in;
}

std::ifstream &Developer::read_from_ifstream(std::ifstream &in) {
    Employee::read_from_ifstream(in);
    in >> read_bool(_has_bonus);
    return in;
}

Developer::Developer(std::ifstream &in) : Developer() {
    Developer::read_from_ifstream(in);
}

Developer::Developer(std::istream &in) : Developer() {
    Developer::read_from_istream(in);
}

Developer::Developer() : Employee() {
    _has_bonus = false;
}

// Sales Manger
SalesManager::SalesManager(const char* name, int32_t base_salary, int32_t sold_items, int32_t price) : Employee(name, base_salary) {
    _sold_items = sold_items;
    _price = price;
}

int SalesManager::salary() const {
    return _base_salary + _sold_items * _price * 0.01;
}

std::ostream &SalesManager::write_to_ostream(std::ostream &out) const {
    out << "Sales Manager" << std::endl;
    Employee::write_to_ostream(out);
    out << "Sold items: " << _sold_items << std::endl
        << "Item price: " << _price << std::endl;
    return out;
}

std::ofstream &SalesManager::write_to_ofstream(std::ofstream &out) const {
    out << write_le_int32(2);
    Employee::write_to_ofstream(out);
    out << write_le_int32(_sold_items)
        << write_le_int32(_price);
    return out;
}

std::istream &SalesManager::read_from_istream(std::istream &in){
    Employee::read_from_istream(in);
    in >> _sold_items
       >> _price;
    return in;
}

std::ifstream &SalesManager::read_from_ifstream(std::ifstream &in){
    Employee::read_from_ifstream(in);
    in >> read_le_int32(_sold_items)
       >> read_le_int32(_price);
    return in;
}

SalesManager::SalesManager(std::ifstream &in) : SalesManager() {
    SalesManager::read_from_ifstream(in);
}

SalesManager::SalesManager(std::istream &in) : SalesManager() {
    SalesManager::read_from_istream(in);
}

SalesManager::SalesManager() : Employee() {
    _sold_items = 0;
    _price = 0;
}

// Employees Array
EmployeesArray::EmployeesArray() : _size(0) {}

EmployeesArray::~EmployeesArray() {
    for (int i = 0; i < _size; i++)
        delete _employees[i];
}

void EmployeesArray::add(const Employee* e) {
    _employees.push_back((Employee*)e);
    _size++;
}

int EmployeesArray::total_salary() const {
    int sum = 0;
    for (int i = 0; i < _size; i++)
        sum += _employees[i]->salary();
    return sum;
}

std::ostream& operator<<(std::ostream& out, const EmployeesArray& ea) {
    for (int32_t i = 0; i < (int32_t) ea._employees.size(); i++) {
        out << (i + 1) << ". " << *ea._employees[i];
    }
    out << "== Total salary: " << ea.total_salary() << std::endl << std::endl;
    return out;
}

std::ofstream& operator<<(std::ofstream& out, const EmployeesArray& ea) {
    out << write_le_int32((int32_t) ea._employees.size());
    for (auto _employee : ea._employees) {
        out << *_employee;
    }
    return out;
}

std::ifstream& operator>>(std::ifstream& in, EmployeesArray& ea) {
    int32_t size;
    in >> read_le_int32(size);
    for (int32_t i = 0; i < size; i++) {
        int32_t type;
        in >> read_le_int32(type);
        Employee *employee;
        if (type == 1){
            employee = new Developer(in);
        }
        else if (type == 2) {
            employee = new SalesManager(in);
        }
        ea.add(employee);
    }
    return in;
}

std::istream& operator>>(std::istream& in, EmployeesArray& ea) {
    int type;
    in >> type;
    Employee *employee;
    if (type == 1) {
        employee = new Developer(in);
    }
    else if (type == 2) {
        employee = new SalesManager(in);
    }
    ea.add(employee);
    return in;
}
