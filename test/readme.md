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
- T: 及时：测试是及时的。程序员在代码上线前，及时地编写它们，以防止bug。

对于`c++`代码，一个比较好的单元测试框架是`google`开源的`gtest`。`gtest`会独立运行所有的测试用例，并最终统计出未通过的测试用例对应的case以及所在位置。
同时，`gmock`已经成为`gtest`项目的一部分，遇到有数据依赖或者无法构造出实际环境的case还可以直接使用`gmock`进行模拟。

## gtest配置

采用`cmake`管理项目，同时为了模拟`search root`模块的部分场景，引入`workflow`, `fmt`库，可以使用同样的方式引入`fastjson`等其他库。
具体依赖项的配置可以参考项目中的`CMakeLists.txt`，需要注意的是，由于`workflow`项目头文件目录无法被`FetchContent_MakeAvailable`正确处理，因此需要手动添加。

`gtest`可以自己添加`main`函数用于运行测试用例，也可以直接使用`gtest_main.lib`提供的默认`main`函数，默认的`main`函数如下：
```cpp
GTEST_API_ int main(int argc, char **argv) {
    printf("Running main() from gtest_main.cc\n");
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```

## gtest基础

基本使用方式的区别，参考官方文档或者(stackoverflow)[https://stackoverflow.com/questions/58600728/what-is-the-difference-between-test-test-f-and-test-p].


`TEST()` is useful when you want to write unit tests for static or global functions or simple classes.

`TEST_F()` is useful when you need access to objects and subroutines in the unit test.

`TEST_P()` is useful when you want to write tests with a parameter. Instead of writing multiple tests with different values of the parameter,
you can write one test using `TEST_P()` which uses `GetParam()` and can be instantiated using `INSTANTIATE_TEST_SUITE_P()`.

其中`TEST`的两个参数分别为`test_suite_name`和`test_name`。

`TEST_F(test_fixture,test_name)`，第一个参数必须和待测试类名一致？待确认具体要求。第二个参数用于标识用。



“事件” 本质是框架给你提供了一个机会, 让你能在这样的几个机会来执行你自己定制的代码, 来给测试用例准备/清理数据。gtest提供了多种事件机制，总结一下gtest的事件一共有三种：

1、TestSuite事件

需要写一个类，继承testing::Test，然后实现两个静态方法：SetUpTestCase 方法在第一个TestCase之前执行；TearDownTestCase方法在最后一个TestCase之后执行。

2、TestCase事件

是挂在每个案例执行前后的，需要实现的是SetUp方法和TearDown方法。SetUp方法在每个TestCase之前执行；TearDown方法在每个TestCase之后执行。

3、全局事件

要实现全局事件，必须写一个类，继承testing::Environment类，实现里面的SetUp和TearDown方法。SetUp方法在所有案例执行前执行；TearDown方法在所有案例执行后执行。





















dd
