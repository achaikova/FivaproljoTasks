#include "gtest/gtest.h"
#include <my_vector_impl.h>
#include <test_types.h>

// name FooTest by convention
class MyVectorTest : public ::testing::Test {
protected:

    my_vector::my_vector<int> v1;
    my_vector::my_vector<Product> v2;
    my_vector::my_vector<NonDefaultCtorObj1 *> v3;
    std::vector<NonDefaultCtorObj1 *> v3_check;
    my_vector::my_vector<DefaultCtorObj1 *> v4;

    // Code here will be called immediately after the constructor (right
    // before each test).
    void SetUp() override {
        v1.push_back(10);
        v1.push_back(234);
        v1.push_back(76543);

        v2.push_back(Product("Starman", 42, 6.0));
        v2.push_back(Product("Starman", 42, 6.0));
        v2.push_back(Product("Starman", 42, 6.0));
        v2.push_back(Product("Starman", 42, 6.0));

        v3.push_back(new NonDefaultCtorObj1("Ground", 1));
        v3.push_back(new NonDefaultCtorObj1("Control", 2));
        v3.push_back(new NonDefaultCtorObj1("to", 3));
        v3.push_back(new NonDefaultCtorObj1("Major", 4));
        v3.push_back(new NonDefaultCtorObj1("Tom", 5));

        v3_check.push_back(new NonDefaultCtorObj1("Ground", 1));
        v3_check.push_back(new NonDefaultCtorObj1("Control", 2));
        v3_check.push_back(new NonDefaultCtorObj1("to", 3));
        v3_check.push_back(new NonDefaultCtorObj1("Major", 4));
        v3_check.push_back(new NonDefaultCtorObj1("Tom", 5));

        v4.push_back(new DefaultCtorObj1());
        v4.push_back(new DefaultCtorObj1(1, "Hi, Mark", 2));
        v4.push_back(new DefaultCtorObj1(2, "test", 3));
    }

    void TearDown() override {
        // Code here will be called immediately after each test (right
        // before the destructor).
        // in this test this is not necessary
    }

};

TEST_F(MyVectorTest, TestPushBack) {
    EXPECT_EQ(v1.size(), 3); // EXPECT_* generates nonfatal failures, which don't abort the current function
    EXPECT_EQ(v1[0], 10);

    EXPECT_EQ(v2.size(), 4);
    EXPECT_TRUE(v2[v2.size() - 1] == Product("Starman", 42, 6.0));

    ASSERT_EQ(v3.size(), 5); // ASSERT_* generates fatal failures when fails, and aborts the current function
    for (std::size_t i = 0; i < v3.size(); i++) {
        ASSERT_TRUE(*v3[i] == *v3_check[i]);// this could have been done with ASSERT_THAT(v3, ElementsAre(...))
        // but alas my vector does not have iterator (gtest mock)
    }
}

TEST_F(MyVectorTest, TestPopBack) {
    v1.pop_back();
    EXPECT_TRUE(!v1.empty());
    EXPECT_EQ(v1.size(), 2);

    v2.pop_back();
    v2.pop_back();
    v2.pop_back();
    EXPECT_EQ(v2.size(), 1);

    for (std::size_t i = 0; i < v3_check.size(); i++) {
        v3.pop_back();
    }
    EXPECT_TRUE(v3.empty());
    EXPECT_NE(v3.size(), 5);
    EXPECT_EQ(v3.capacity(), v3_check.capacity());

    v4.pop_back();
    v4.push_back(new DefaultCtorObj1());
    v4.pop_back();
    v4.pop_back();
    EXPECT_EQ(v4.size(), 1);
    EXPECT_TRUE(*v4[0] == DefaultCtorObj1());
}

TEST_F(MyVectorTest, TestResize) {
    my_vector::my_vector<int> v1_copy(v1);
    v1.resize(5);
    EXPECT_EQ(v1.size(), 5);
    for (std::size_t i = 0; i < v1_copy.size(); i++) {
        EXPECT_TRUE(v1[i] == v1_copy[i]);
    }

    my_vector::my_vector<DefaultCtorObj1 *> v4_copy(v4);
    v4.resize(1);
    EXPECT_EQ(v4.size(), 1);
    for (std::size_t i = 0; i < v4.size(); i++) {
        EXPECT_TRUE(v4[i] == v4_copy[i]);
    }
}

TEST_F(MyVectorTest, TestClear) {
    v1.clear();
    EXPECT_EQ(v1.size(), 0);
    EXPECT_TRUE(v1.empty());
    EXPECT_EQ(v1.capacity(), 4);

    v2.clear();
    EXPECT_EQ(v2.size(), 0);
    EXPECT_TRUE(v2.empty());
    EXPECT_EQ(v2.capacity(), 4);

    v3.clear();
    v3_check.clear();
    EXPECT_EQ(v3.size(), v3_check.size());
    EXPECT_EQ(v3.empty(), v3_check.empty());
    EXPECT_EQ(v3.capacity(), v3_check.capacity());
}

TEST_F(MyVectorTest, TestAccesToElem) {
    EXPECT_EQ(v1[0], 10);
    EXPECT_EQ(v1[1], 234);
    EXPECT_EQ(v1[2], 76543);

    EXPECT_TRUE(v2[0] == Product("Starman", 42, 6.0));

    EXPECT_TRUE(*v3[4] == NonDefaultCtorObj1("Tom", 5));

    EXPECT_TRUE(*v4[0] == DefaultCtorObj1());
}

TEST_F(MyVectorTest, TestCopyCtor) {
    my_vector::my_vector<int> v1_copy(v1);
    EXPECT_EQ(v1.size(), v1_copy.size());
    EXPECT_EQ(v1.size(), v1_copy.capacity());
    for (std::size_t i = 0; i < v1_copy.size(); i++) {
        EXPECT_TRUE(v1[i] == v1_copy[i]);
    }

    my_vector::my_vector<NonDefaultCtorObj1 *> v3_copy(v3);
    EXPECT_EQ(v3.size(), v3_copy.size());
    EXPECT_EQ(v3.size(), v3_copy.capacity());
    for (std::size_t i = 0; i < v3_copy.size(); i++) {
        EXPECT_TRUE(v3[i] == v3_copy[i]);
    }
}

TEST_F(MyVectorTest, TestOpEqual) {
    my_vector::my_vector<int> v1_eq;
    v1_eq.push_back(45);
    v1_eq.push_back(65432);
    v1_eq.push_back(34567);
    v1_eq.push_back(55555);
    v1_eq = v1;
    EXPECT_EQ(v1.size(), v1_eq.size());
    for (std::size_t i = 0; i < v1_eq.size(); i++) {
        EXPECT_TRUE(v1[i] == v1_eq[i]);
    }

    my_vector::my_vector<Product> v2_eq;
    v2_eq = v2;
    v2_eq.push_back(Product("rise", 12, 6.0));
    v2.push_back(Product("rize", 12, 6.0));
    EXPECT_EQ(v2.size(), v2_eq.size());
    for (std::size_t i = 0; i < v2_eq.size() - 1; i++) {
        EXPECT_TRUE(v2[i] == v2_eq[i]);
    }
    EXPECT_FALSE(v2[v2.size() - 1] == v2_eq[v2_eq.size() - 1]);

    my_vector::my_vector<NonDefaultCtorObj1 *> v3_eq;
    v3_eq.push_back(new NonDefaultCtorObj1("abba?", 12));
    v3 = v3_eq;
    EXPECT_EQ(v3.size(), v3_eq.size());
    for (std::size_t i = 0; i < v3.size(); i++) {
        EXPECT_TRUE(v3[i] == v3_eq[i]);
    }
}
