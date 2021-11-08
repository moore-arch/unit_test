# gtest笔记
引用知乎回答[陈萌萌](https://www.zhihu.com/question/27313846/answer/130954707).

基本作用: 让人在修改代码之后能感到安心，踏实
- 最基本的要求，测试用例能验证函数的正确性
- 测试用例尽可能涵盖边界条件，例如遍历一个链表，头指针是空，只有一个节点，链表有N个节点，N是问题描述下允许的最大节点数等等
- 一些异常和错误处理，例如往一个函数里传入空指针，传入空串，这个函数能否打印一些log，返回错误码，实现加法的Add函数如何检测和处理溢出等等
- 最理想的情况下（时间很多！），应该尽量多写测试用例，以保证代码功能的正确性符合预期，具有良好的容错性。如果代码较复杂，条件分支较多，测试用例最好能覆盖所有的分支路径。上述原则一般解决了很多“应该测试什么”的问题。

由于代码可能会面临变动，有时候需要修改已经写好的接口，因此需要同步更新单元测试，这个过程很多时候比较费时。

评价-first标准

- F: 快速：测试必须非常快，这样开发人员可以对每一个小更改运行测试，而不用中断思绪去等待测试运行。
- I: 隔离：不同的测试用例之间是隔离的。一个测试不会依赖另一个测试。不同测试的故障是相互隔离的。
- R: REPEATABLE: - 可重演 测试程序要可在不同环境跑.
- S: SLEF-VALIDATING: - 自我确认 测试结果应是简单的TRUE/FALSE, 无须人工确认.
- T: 及时,测试是及时的。程序员在代码上线前，及时地编写它们，以防止bug。

对于`c++`代码，一个比较好的单元测试框架是`google`开源的`gtest`。`gtest`会独立运行所有的测试用例，并最终统计出未通过的测试用例对应的case以及所在位置。
同时，`gmock`已经成为`gtest`项目的一部分，遇到有数据依赖或者无法构造出实际环境的case还可以直接使用`gmock`进行模拟。

## gtest配置

采用`cmake`管理项目，同时为了模拟`search root`模块的部分场景，引入`workflow`, `fmt`库，可以使用同样的方式引入`fastjson`等其他库。
具体依赖项的配置可以参考项目中的`CMakeLists.txt`，需要注意的是，由于`workflow`项目头文件目录无法被`FetchContent_MakeAvailable`正确处理，因此需要手动添加。

`gtest`可以自己添加`main`函数用于运行测试用例，也可以直接使用`gtest_main.lib`提供的默认`main`函数，默认的`main`函数如下：
```cpp
GTEST_API_ int main(int argc, char **argv) {
    printf("Running main() from gtest_main.cc\n");
    
    // 获取 googletest 标志，并删除所有已识别的标志。这允许用户通过各种标志来控制测试程序的行为
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```

### invoking tests
关于`gtest`的运行机制，事实上`TEST`, `TEST_F`等宏定义已经注册了对应的测试用例，不需要显式列出所有的测试项。使用`RUN_ALL_TESTS`可以运行所有注册过的测试用例，只有当所有测试用例都成功时返回-1。

## gtest基础

基本使用方式的区别，参考官方文档或者(stackoverflow)[https://stackoverflow.com/questions/58600728/what-is-the-difference-between-test-test-f-and-test-p].

(gtest primer)[https://google.github.io/googletest/primer.html]


`TEST()` is useful when you want to write unit tests for static or global functions or simple classes.
```cpp
TEST(TestSuiteName, TestName) {
  ... statements ...
}
```

`TEST_F()` is useful when you need access to objects and subroutines in the unit test.参数不能包含下划线。
```cpp
TEST_F(TestFixtureName, TestName) {
  ... statements ...
}
```

`TEST_P()` is useful when you want to write tests with a parameter. Instead of writing multiple tests with different values of the parameter,
you can write one test using `TEST_P()` which uses `GetParam()` and can be instantiated using `INSTANTIATE_TEST_SUITE_P()`.
简而言之，就是可以对一个测试语句传入不同的参数，从而运行多次。
```cpp
// EXPECT_TRUE运行多次，GetParam()每次从参数列表中取一个值
TEST_P(TestFixtureName, TestName) {
  ... statements ...
  EXPECT_TRUE(DoSomething(GetParam()));
}

INSTANTIATE_TEST_CASE_P(TestName, IsPrimeParamTest, testing::Values(3, 5, 11, 23, 17));
```


### simple tests
`simple tests`可以直接使用`TEST()`宏创建，`GTEST`按照`suite_name`对测试分组，因此相同单元的测试的`suite_name`应当相同。同时创建时要注意`test_suite_name`和`test_name`不能包含下划线。

### test fixtures
#### 创建和运行
`test fixture`可以避免多次执行相同的操作或者创建相同的数据，创建`test fixture`可以分为以下步骤：
1. 以`public`方式继承`::testing::Test`类，同时类内成员应当声明为`protected`，以便于访问其中的成员变量。
2. 声明需要创建的数据。 
3. （可选）有必要的时候可以创建`SetUp()`和`TearDown()`对每个测试用例构建和释放资源。

当使用`test fixtures`时，需要使用`TEST_F`才可以访问`test fixture`中的变量和方法（使用之前必须先定义）。使用`TEST_F`的第一个参数必须是`fixture class`，这也是其中F的含义。
每个`TEST_F`用到的数据都是经过`SetUp()`创建过的。每个`test case`结束之后，对应的`test fixture`会被删除掉。具体的过程：

1. 构造`OneTest`的`test fixture`
2. 运行`SetUp()`初始化
3. 测试当前用例
4. 运行`TearDown()`释放`test fixture`中的资源。
5. 销毁`test fixture`
6. 继续下一个`OneTest`测试。


#### quick test
`gtest`可以使用`test fixtures`构建包含用时的测试用例。

```cpp
class QuickTest : public testing::Test {
private:
    std::chrono::high_resolution_clock::time_point start_time_;

protected:

    void SetUp() override {
        start_time_ = std::chrono::high_resolution_clock::now();
    }

    void TearDown() override {
        using namespace std::literals;
//        usleep(std::chrono::duration_cast<std::chrono::microseconds>(5ms).count());
//        usleep((5000ns).count());
        std::chrono::high_resolution_clock::time_point finish_time =
                std::chrono::high_resolution_clock::now();
        auto cost = finish_time - start_time_;
//        auto limit = std::chrono::milliseconds(5);
        EXPECT_LE(cost, 5ms)
                            << fmt::format("cost too long, execute time: {}\n", cost);
    }
};
```



### 接口测试

接口测试可以用于测试公共方法的不同实现。构建接口测试时首先要创建一些工厂函数，然后定义使用类模板定义`test fixture`。最后使用公共的接口测试所有实现。
`gtest`提供了2中不同的方法可以测试接口对应的实现。

#### typed tests
当已经知道接口所有实现之后，可以使用这种方式。首先声明并指定类型参数，然后时使用`TYPED_TEST`构建测试用例，`gtest`会自动为`TypeList`中每个具体的实现构建测试，不需要用户重复构建测试用例。

// https://www.cnblogs.com/coderzh/archive/2009/04/08/1431297.html

```cpp
// TestCaseName 必须是fixture name
// TYPED_TEST_SUITE(TestCaseName, TypeList);

// The list of types we want to test.
typedef Types<OnTheFlyPrimeTable, PreCalculatedPrimeTable> Implementations;

TYPED_TEST_SUITE(PrimeTableTest, Implementations);

// Then use TYPED_TEST(TestCaseName, TestName) to define a typed test,
```


#### type-parameterized
这种构建方式比较复杂，但是可以适应更多的场景，复用性更好。
当无法获知接口有多少具体的实现方式时（比如你是接口的提供者，但不负责具体实现），可以使用`type-parameterized`构建测试用例。
1. 声明`test fixture`的模板类。
2. 使用`YPED_TEST_SUITE_P(parma)`完成定义，参数名是`test fixture name`。The _P suffix is for "parameterized" or "pattern".
3. 使用`TYPED_TEST_P(TestCaseName, TestName)`构建测试用例。
4. 枚举测试用例。
5. 添加需要运行的测试具体类型（可以定义在一个.h文件中，可以在`TYPED_TEST_P`之后定义）
```cpp
template <class T>
class PrimeTableTest2 : public PrimeTableTest<T> {
};

TYPED_TEST_SUITE_P(PrimeTableTest2);


TYPED_TEST_P(PrimeTableTest2, some_case) {
}


// you have to enumerate the tests you defined:
REGISTER_TYPED_TEST_SUITE_P(
    PrimeTableTest2,  // The first argument is the test case name.
    // The rest of the arguments are the test names.
    ReturnsFalseForNonPrimes, ReturnsTrueForPrimes, CanGetNextPrime);

typedef Types<OnTheFlyPrimeTable, PreCalculatedPrimeTable>
    PrimeTableImplementations;
INSTANTIATE_TYPED_TEST_SUITE_P(OnTheFlyAndPreCalculated,    // Instance name
                               PrimeTableTest2,             // Test case name
                               PrimeTableImplementations);  // Type list
```


### 参数化


### ASSERT_ & EXPECT_

`EXCEPT_*`可以在断言失败之后显示更详细的信息（可以使用`<<`操作符输出自定义的信息），当检查点失败时，继续往下执行。
包含`EXPECT_EQ, EXPECT_LE, ASSERT_DOUBLE_EQ, EXPECT_STREQ, EXPECT_THROW, EXPECT_ANY_THROW....`
`ASSERT_PRED(n)`:可以在调用返回false的时候打印出传入的参数，帮助定位问题。
`ASSERT_PRED_FORMAT(n)`:类似于`ASSERT_PRED(n)`，但可以自定义输出格式；


```cpp
// 打印调用时传入的参数
EXPECT_PRED2(TestFunction, m, n);


// 自定义输出信息，也许可以直接使用fmt输出
testing::AssertionResult AssertFoo(const char* m_expr, const char* n_expr, const char* k_expr, int m, int n, int k) {
    if (Foo(m, n) == k)
        return testing::AssertionSuccess();
    testing::Message msg;
    msg << m_expr << " 和 " << n_expr << " 的最大公约数应该是：" << Foo(m, n) << " 而不是：" << k_expr;
    return testing::AssertionFailure(msg);
}

TEST(AssertFooTest, HandleFail)
{
    EXPECT_PRED_FORMAT3(AssertFoo, 3, 6, 2);
}
```
`ASSERT_*`用于必须要满足的条件，当检查点失败时，退出当前函数（注意：并非退出当前案例）。


## 事件机制

“事件” 本质是框架给你提供了一个机会, 让你能在这样的几个机会来执行你自己定制的代码, 来给测试用例准备/清理数据。gtest提供了多种事件机制，总结一下gtest的事件一共有三种：

1、TestSuite事件

需要写一个类，继承testing::Test，然后实现两个静态方法：SetUpTestCase 方法在第一个TestCase之前执行；TearDownTestCase方法在最后一个TestCase之后执行。
这个类是`TEST_F`的第一个参数。

2、TestCase事件

是挂在每个案例执行前后的，需要实现的是SetUp方法和TearDown方法。SetUp方法在每个TestCase之前执行；TearDown方法在每个TestCase之后执行。

3、全局事件

要实现全局事件，必须写一个类，继承testing::Environment类，实现里面的SetUp和TearDown方法。SetUp方法在所有测试执行前执行；TearDown方法在所有测试执行后执行。
在main函数中通过testing::AddGlobalTestEnvironment方法将事件挂进来。
```cpp
// 待验证
int _tmain(int argc, _TCHAR* argv[])
{
    testing::AddGlobalTestEnvironment(new FooEnvironment);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```




















dd
