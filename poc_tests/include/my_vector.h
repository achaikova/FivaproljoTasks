#ifndef LAB_12_MY_VECTOR_H
#define LAB_12_MY_VECTOR_H

#include <cstddef>
#include <cmath>
#include "test_types.h"

namespace my_vector {

    template<typename T>
    class my_vector {
    public:

        my_vector();

        explicit my_vector(std::size_t n);

        my_vector(my_vector<T> const &other);

        my_vector(my_vector &&) noexcept;

        my_vector &operator=(my_vector const &other);

        my_vector &operator=(my_vector &&) noexcept;

        void swap(my_vector &other) noexcept;

        ~my_vector();

        std::size_t size() const noexcept;

        std::size_t capacity() const noexcept;

        bool empty() const noexcept;

        void resize(std::size_t n);

        void reserve(std::size_t n);

        // ??

        T &operator[](std::size_t index);

        T const &operator[](std::size_t index) const;

        void push_back(T const &);

        void push_back(T &&);

        void pop_back();

        void clear();

        friend std::ostream &operator<<(std::ostream &os, const my_vector<T> &v) {
            for (std::size_t i = 0; i < v.size(); i++) {
                os << v.array_[i];
            }
            return os;
        }

        friend std::ostream &operator<<(std::ostream &os, my_vector<T> &&v) {
            for (std::size_t i = 0; i < v.size(); i++) {
                os << v.array_[i];
            }
            return os;
        }

        std::size_t min(std::size_t a, std::size_t b);

    private:
        static constexpr int DEFAULT_VECTOR_SIZE = 0;

    private:
        size_t capacity_;
        size_t size_;
        T *array_;
    };


}
//#include "my_vector_impl.h"

#endif //LAB_12_MY_VECTOR_H
