#include <iostream>
#include <cstring>
#include <cassert>

#include "my_vector.hpp"

namespace product {

class Product {
public:
    Product() : name_(nullptr), quantity_(0), price_(0){}

    Product(const char* name, int quantity, double price) {
        name_ = new char[strlen(name) + 1];
        strcpy(name_, name);
        quantity_ = quantity;
        price_ = price;
    }

    ~Product() {
        delete[] name_;
    }

    Product(const Product &other) {
        name_ = other.name_;
        quantity_ = other.quantity_;
        price_ = other.price_;
    }

    bool operator==(const Product &other) const {
        return !strcmp(name_, other.name_) &&
               quantity_ == other.quantity_ &&
               price_ == other.price_;
    }

    Product& operator=(Product &other) {
        quantity_ = other.quantity_;
        price_ = other.price_;
        delete name_;
        name_ = new char[strlen(other.name_) + 1];
        strcpy(name_, other.name_);
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &out, const Product &product) {
        return out << product.name_ << ' '
                   << product.quantity_ << ' '
                   << product.price_;
    }

    void swap(Product &other) {
        using std::swap;
        swap(name_, other.name_);
        swap(quantity_, other.quantity_);
        swap(price_, other.price_);
    }

private:
    char *name_;
    int quantity_;
    double price_;
};

}  // namespace product

namespace tests {
    template<typename T>
    void test_my_vector(T a, T b) {
        containers::my_vector<T> arr;

        arr.push_back(a);
        assert(arr.size() == 1);
        assert(arr[0] == a);

        arr.push_back(b);
        assert(arr.capacity() == 2);
        assert(!arr.empty());
        assert(arr[0] == a);
        assert(arr[1] == b);

        arr.pop_back();
        assert(arr.size() == 1);
        assert(arr[0] == a);

        arr.clear();
        assert(arr.size() == 0);
        assert(arr.empty());

        arr.reserve(5);
        assert(arr.capacity() == 8);

        containers::my_vector<T> cpy(arr);
        assert(cpy.capacity() == 5);

        cpy.push_back(b);
        cpy.push_back(a);
        arr = cpy;
        assert(arr[0] == b);
        assert(arr[1] == a);

        cpy.reserve(8);
        assert(cpy.capacity() == 8);

        arr.swap(cpy);
        assert(arr.capacity() == 8);
        assert(cpy.size() == 2);
    }

    template<typename T>
    void test_my_vector_default_constructible(T x, T y) {
        test_my_vector<T>(x, y);
        containers::my_vector<T> arr(5);
        assert(arr.size() == 5);
        assert(arr.capacity() == 8);

        arr[0] = x;
        assert(arr[0] == x);

        arr.resize(2);
        assert(arr.size() == 2);
        assert(arr.capacity() == 8);
    }
}

int main() {
	containers::my_vector<int> v;
	v.push_back(2);
	const int n{3};
	v.push_back(n);
	std::cout << v << std::endl;

    tests::test_my_vector<int>(5, 10);
    tests::test_my_vector<product::Product>(product::Product("asdf", 4, 12.0), product::Product("qwe", -1, 7.5));
    tests::test_my_vector_default_constructible(2, 3);
    return 0;
}
