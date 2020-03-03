#include <iostream>
#include <vector>

#include "my_vector_impl.h"

namespace product {

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
        char *name_;  // Указатель владеет C-style строкой, на которую указывает.
        int quantity_;
        double price_;
    };

    void print(const my_vector::my_vector<Product> &v) {
        std::cout << v << std::endl;
    }

}  // namespace product

template<typename T>
void test_my_vector(T first, T second) {
    //test my_vector
    my_vector::my_vector<T> test;
    test.push_back(first);
    test.push_back(second);

    //stl vector to compare with
    std::vector<T> check;
    check.push_back(first);
    check.push_back(second);

    assert(test.size() == check.size());
    assert(test.capacity() == check.capacity());

    test.reserve(10);
    check.reserve(10);
    for (std::size_t i = 0; i < test.size(); i++) {
        assert(test[i] == check[i]);
    }
    assert(test.capacity() == check.capacity());

    //test ctor
    my_vector::my_vector<T> test_ctor(test);
    std::vector<T> check_ctor(check);
    for (std::size_t i = 0; i < test.size(); i++) {
        assert(test_ctor[i] == check_ctor[i]);
    }
    assert(test_ctor.capacity() == check_ctor.capacity());

    //test op=
    my_vector::my_vector<T> test_op_eq;
    test_op_eq.push_back(first);
    test_op_eq.push_back(first);
    test_op_eq.push_back(second);
    test_op_eq.push_back(second);
    test_op_eq = test;
    std::vector<T> check_op_eq;
    check_op_eq.push_back(first);
    check_op_eq.push_back(first);
    check_op_eq.push_back(second);
    check_op_eq.push_back(second);
    check_op_eq = check;
    assert(test_op_eq.size() == check_op_eq.size());
    for (std::size_t i = 0; i < test_op_eq.size(); i++) {
        assert(test_op_eq[i] == check_op_eq[i]);
    }

    //test clear and empty
    my_vector::my_vector<T> test_clear;
    test_clear.push_back(first);
    test_clear.push_back(first);
    test_clear.push_back(second);
    test_clear.push_back(second);
    std::vector<T> check_clear;
    check_clear.push_back(first);
    check_clear.push_back(first);
    check_clear.push_back(second);
    check_clear.push_back(second);
    test_clear.clear();
    check_clear.clear();
    assert(test_clear.size() == check_clear.size());
    assert(test_clear.capacity() == check_clear.capacity());
    assert(test_clear.empty() == check_clear.empty());

    //test pop_back
    my_vector::my_vector<T> test_pop_back;
    test_pop_back.push_back(first);
    test_pop_back.push_back(first);
    test_pop_back.push_back(second);
    std::vector<T> check_pop_back;
    check_pop_back.push_back(first);
    check_pop_back.push_back(first);
    check_pop_back.push_back(second);
    test_pop_back.pop_back();
    check_pop_back.pop_back();
    assert(test_pop_back.size() == check_pop_back.size());
    assert(test_pop_back[test_pop_back.size() - 1] == check_pop_back[check_pop_back.size() - 1]);
    test_pop_back.pop_back();
    check_pop_back.pop_back();
    assert(test_pop_back.size() == check_pop_back.size());
    assert(test_pop_back[test_pop_back.size() - 1] == check_pop_back[check_pop_back.size() - 1]);
    test_pop_back.push_back(first);
    check_pop_back.push_back(first);
    assert(test_pop_back.size() == check_pop_back.size());
    assert(test_pop_back[test_pop_back.size() - 1] == check_pop_back[check_pop_back.size() - 1]);
    test_pop_back.pop_back();
    check_pop_back.pop_back();
    assert(test_pop_back.size() == check_pop_back.size());
    assert(test_pop_back[test_pop_back.size() - 1] == check_pop_back[check_pop_back.size() - 1]);
}

int main() {
    test_my_vector<int>(5, 10);
    test_my_vector<product::Product>(
            product::Product("asdf", 4, 12.0),
            product::Product("qwe", -1, 7.5));

}