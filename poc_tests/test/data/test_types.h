#ifndef LAB_12_TEST_TYPES_H
#define LAB_12_TEST_TYPES_H

#include <string>

class DefaultCtorObj1 {
public:
    DefaultCtorObj1() : n(0), s("init_string"), arr(new int[2]) {}

    DefaultCtorObj1(int n, std::string s, std::size_t size) : n(n), s(s), arr(new int[size]) {}

    ~DefaultCtorObj1() {
        delete[]arr;
    }

    bool operator==(const DefaultCtorObj1 &p) {
        return n == p.n && s == p.s;
    }

private:
    int n;
    std::string s;
    int *arr;
};


class NonDefaultCtorObj1 {
public:
    NonDefaultCtorObj1() = delete;

    NonDefaultCtorObj1(std::string a, std::size_t n) : s(a), arr(new int[n]) {}

    ~NonDefaultCtorObj1() {
        delete[] arr;
    }

    bool operator==(const NonDefaultCtorObj1 &n) {
        return s == n.s && sizeof(arr) == sizeof(n.arr);
    }

private:
    std::string s;
    int *arr;
};

class Product {
public:
    Product(const char *name, int quantity, double price) : name_((char *) name),
                                                            quantity_(quantity),
                                                            price_(price) {}

    friend std::ostream &operator<<(std::ostream &os, const Product &p) {
        os << p.name_ << ' ' << p.quantity_ << ' ' << p.price_ << ' ';
        return os;
    }

    bool operator==(const Product &p) {
        return name_ == p.name_ && quantity_ == p.quantity_ && price_ == p.price_;
    }

private:
    char *name_;
    int quantity_;
    double price_;
};

#endif //LAB_12_TEST_TYPES_H
