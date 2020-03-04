## Template
Если пишете 2 или более теста, которые зависят от одних входных данных, лучше завести test fixture. 
```c++
class FooTest : public ::testing::Test {
protected:
      (...) // data
      void SetUp() override {} // Set up test input
      void TearDown() override {}  // Code here will be called immediately after each test 
 };
 
 TEST_F(FooTest, TestName) {...}
```

Если тестируете отдельную функцию, можно использовать только TEST:
```c++
TEST(TestSuiteName, TestName) {
  ... test body ...
}
```
## Use of macros
* Gtest поддерживает два вида - ASSERT_* и EXPECT_* . В большинстве случаев использовать  EXPECT_* , чтобы несмотря на падение одного теста, остальные в этой функции выполнились. 
* Если в тестах приходится использовать сложные assert-ы, то возможно стоит взглянуть на google mock - есть удобные matchers. Например, проверка элементов массива через простые EXPECT-ы и используя mock:
```c++
// Bad way
  for (std::size_t i = 0; i < v.size(); i++) {
        EXPECT_TRUE(v[i] == v_copy[i]);
  }
  
// Using mock
EXPECT_THAT(v, ElementsAre(5, 10, 15)); // Note that ElementsAre (as well as other matchers) needs iterators and size() on a class to work
```

