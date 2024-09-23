#include "MainTask.h"
#include "Key.h"
#include "Serial.hpp"
#include "cmsis_os.h"
#include <algorithm>
#include <functional>
#include <map>
#include <memory> // std::make_unique
#include <set>
#include <stdint.h>
#include <stdio.h>
#include <string>
#include <type_traits>
#include <utility> // std::move
#include <vector>

class Person {
public:
    Person(std::string name, int age)
        : name(name)
        , age(age)
    {
    }

    std::string name;
    int age;
};

void vectorWithBuiltInTypesTest();
void vectorWithCustomTypesTest();
void vectorWithCustomTypePointersTest();
void vectorWithNestedVectorTest();
void stringConstructorTest();
void stringAssignmentTest();
void stringConcatenationTest();
void stringFindTest();
void stringReplaceTest();
void stringCompareTest();
void stringInsertAndEraseTest();
void stringSubstrTest();
void vectorConstructorTest();
void vectorAssignmentTest();
void setConstructorAndAssignmentTest();
void setFindAndCountTest();
void setWithCustomTypeTest();
void mapConstructorAndAssignmentTest();
void mapInsertAndEraseTest();

std::tuple<double, char, std::string> getStudent(int id)
{
    if (id == 0) {
        return std::make_tuple(3.8, 'A', "Lisa Simpson");
    } else if (id == 1) {
        return std::make_tuple(2.9, 'C', "Milhouse Van Houten");
    } else if (id == 2) {
        return std::make_tuple(1.7, 'D', "Ralph Wiggum");
    } else {
        return std::make_tuple(0.0, 'F', "N/A");
    }
}

void MainTask_Run(void)
{
    auto student = getStudent(0);
    printf("ID: 0, GPA: %.1f, Grade: %c, Name: %s\r\n",
        std::get<0>(student), std::get<1>(student), std::get<2>(student).c_str());

    double gpa;
    char grade;
    std::string name;

    // 元组进行拆包
    std::tie(gpa, grade, name) = getStudent(1);
    printf("ID: 1, GPA: %.1f, Grade: %c, Name: %s\r\n", gpa, grade, name.c_str());

#pragma region STL容器测试
// vectorWithBuiltInTypesTest();
// vectorWithCustomTypesTest();
// vectorWithCustomTypePointersTest();
// vectorWithNestedVectorTest();
// stringConstructorTest();
// stringAssignmentTest();
// stringConcatenationTest();
// stringFindTest();
// stringReplaceTest();
// stringCompareTest();
// stringInsertAndEraseTest();
// stringSubstrTest();
// vectorConstructorTest();
// vectorAssignmentTest();
// setConstructorAndAssignmentTest();
// setFindAndCountTest();
// setWithCustomTypeTest();
// mapConstructorAndAssignmentTest();
// mapInsertAndEraseTest();
#pragma endregion

    while (true) {
        osDelay(1);
    }
}

#pragma region STL容器测试

void printVector(std::vector<int>& v)
{
    using namespace std;

    for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
        printf("%d ", *it);
    }

    printf("\r\n");
}

void printSet(std::set<int>& s)
{
    using namespace std;

    for (set<int>::iterator it = s.begin(); it != s.end(); it++) {
        printf("%d ", *it);
    }

    printf("\r\n");
}

void printMap(std::map<uint32_t, uint32_t>& m)
{
    using namespace std;

    for (map<uint32_t, uint32_t>::iterator it = m.begin(); it != m.end(); it++) {
        printf("%ld: %ld\r\n", it->first, it->second);
    }
}

// vector存放内置数据类型测试
void vectorWithBuiltInTypesTest()
{
    using namespace std;

    vector<int> v;

    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    // 第一种遍历方式
    // vector<int>::iterator itBegin = v.begin(); // 起始迭代器, 指向第一个元素
    // vector<int>::iterator itEnd = v.end(); // 结束迭代器, 指向最后一个元素的下一个位置

    // while (itBegin != itEnd) {
    //     printf("%d ", *itBegin);
    //     itBegin++;
    // }
    // printf("\r\n");

    // 第二种遍历方式
    // for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
    //     printf("%d ", *it);
    // }
    // printf("\r\n");

    // 第三种遍历方式, 利用STL中的遍历算法
    for_each(v.begin(), v.end(), [](int i) {
        printf("%d ", i);
    });
    printf("\r\n");
}

// vector存放自定义数据类型测试
void vectorWithCustomTypesTest()
{
    using namespace std;

    vector<Person> v;

    Person p1("Tom", 20);
    Person p2("Jerry", 30);
    Person p3("Jack", 40);
    Person p4("Rose", 50);
    Person p5("Rose", 50);

    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    v.push_back(p4);
    v.push_back(p5);

    for (vector<Person>::iterator it = v.begin(); it != v.end(); it++) {
        printf("Name: %s, Age: %d\r\n", it->name.c_str(), it->age);
    }
}

// vector存放自定义数据类型的指针测试
void vectorWithCustomTypePointersTest()
{
    using namespace std;

    vector<Person*> v;

    Person p1("Tom", 20);
    Person p2("Jerry", 30);
    Person p3("Jack", 40);
    Person p4("Rose", 50);
    Person p5("Rose", 50);

    v.push_back(&p1);
    v.push_back(&p2);
    v.push_back(&p3);
    v.push_back(&p4);
    v.push_back(&p5);

    for (vector<Person*>::iterator it = v.begin(); it != v.end(); it++) {
        printf("Name: %s, Age: %d\r\n", (*it)->name.c_str(), (*it)->age);
    }
}

// vector容器嵌套容器测试
void vectorWithNestedVectorTest()
{
    using namespace std;

    printf("create v\r\n");
    vector<vector<int>> v;

    printf("create v1\r\n");
    vector<int> v1 { 1, 2, 3 };
    printf("create v2\r\n");
    vector<int> v2 { 4, 5, 6 };
    printf("create v3\r\n");
    vector<int> v3 { 7, 8, 9 };
    printf("create v4\r\n");
    vector<int> v4 { 10, 11, 12 };

    printf("push_back v1\r\n");
    v.push_back(v1);
    printf("push_back v2\r\n");
    v.push_back(v2);
    printf("push_back v3\r\n");
    v.push_back(v3);
    printf("push_back v4\r\n");
    v.push_back(v4);

    printf("print v\r\n");
    for (vector<vector<int>>::iterator it = v.begin(); it != v.end(); it++) {
        for (vector<int>::iterator it2 = it->begin(); it2 != it->end(); it2++) {
            printf("%d ", *it2);
        }
        printf("\r\n");
    }
}

// string构造函数测试
void stringConstructorTest()
{
    using namespace std;

    string s1; // 默认构造函数

    const char* str = "Hello, World!";
    string s2(str); // 从C风格字符串构造
    printf("s2: %s\r\n", s2.c_str());

    string s3(s2); // 从string构造
    printf("s3: %s\r\n", s3.c_str());

    string s4(10, 'a'); // 重复n次字符构造
    printf("s4: %s\r\n", s4.c_str());
}

// string赋值操作测试
void stringAssignmentTest()
{
    using namespace std;

    string str1;
    str1 = "Hello, World!";
    printf("str1: %s\r\n", str1.c_str());

    string str2;
    str2 = str1;
    printf("str2: %s\r\n", str2.c_str());

    string str3;
    str3 = 'a';
    printf("str3: %s\r\n", str3.c_str());

    string str4;
    str4.assign("Hello, C++!");
    printf("str4: %s\r\n", str4.c_str());

    string str5;
    str5.assign("Hello, C++!", 5); // 头n个字符赋值
    printf("str5: %s\r\n", str5.c_str());

    string str6;
    str6.assign(str5);
    printf("str6: %s\r\n", str6.c_str());

    string str7;
    str7.assign(10, 'a'); // 重复n次字符赋值
    printf("str7: %s\r\n", str7.c_str());
}

// string拼接操作测试
void stringConcatenationTest()
{
    using namespace std;

    string str1 = "我";
    str1 += "爱玩游戏:";
    printf("str1: %s\r\n", str1.c_str());

    string str2 = "LOL DNF";
    str1 += str2;
    printf("str1: %s\r\n", str1.c_str());

    string str3 = "I ";
    str3.append("love ");
    printf("str3: %s\r\n", str3.c_str());

    str3.append(str2);
    printf("str3: %s\r\n", str3.c_str());

    str3.append(str2, 4, 3); // 从str2的第4个字符开始，截取拼接3个字符
    printf("str3: %s\r\n", str3.c_str());
}

// string查找操作测试
void stringFindTest()
{
    using namespace std;

    string str1 = "abcdefgde";
    auto pos = str1.find("de");

    if (pos == string::npos) {
        printf("not found\r\n");
    } else {
        printf("pos: %d\r\n", pos);
    }

    pos = str1.rfind("de"); // rfind从右往左查找
    printf("pos: %d\r\n", pos);
}

// string替换操作测试
void stringReplaceTest()
{
    using namespace std;

    string str1 = "abcdefgde";
    str1.replace(1, 3, "1111"); // 从第1个字符开始，替换3个字符为"1111"
    printf("str1: %s\r\n", str1.c_str());
}

// string比较操作测试
void stringCompareTest()
{
    using namespace std;

    string str1 = "xello";
    string str2 = "hello";

    if (str1.compare(str2) == 0) {
        printf("str1 == str2\r\n");
    } else if (str1.compare(str2) < 0) {
        printf("str1 < str2\r\n");
    } else {
        printf("str1 > str2\r\n");
    }
}

// string插入和删除操作测试
void stringInsertAndEraseTest()
{
    using namespace std;

    string str = "hello";
    str.insert(1, "2222"); // 从第1个字符开始插入"2222"
    printf("str: %s\r\n", str.c_str());

    str.erase(1, 3); // 从第1个字符开始删除3个字符
    printf("str: %s\r\n", str.c_str());
}

// string字串操作测试
void stringSubstrTest()
{
    using namespace std;

    string str = "hello, world!";
    string subStr = str.substr(1, 3); // 从第1个字符开始，截取3个字符
    printf("subStr: %s\r\n", subStr.c_str());
}

// vector构造函数测试
void vectorConstructorTest()
{
    using namespace std;

    vector<int> v1;

    for (uint8_t i = 0; i < 10; i++) {
        v1.push_back(i);
    }

    printVector(v1);

    vector<int> v2(v1.begin(), v1.end());
    printVector(v2);

    vector<int> v3(10, 100); // 初始化10个元素，每个元素的值为100
    printVector(v3);

    vector<int> v4(v3);
    printVector(v4);
}

// vector赋值操作测试
void vectorAssignmentTest()
{
    using namespace std;

    vector<int> v1;

    for (uint8_t i = 0; i < 10; i++) {
        v1.push_back(i);
    }

    vector<int> v2;
    v2 = v1;
    printVector(v2);

    vector<int> v3;
    v3.assign(v1.begin(), v1.end());
    printVector(v3);
}

// set构造和赋值操作测试
void setConstructorAndAssignmentTest()
{
    using namespace std;

    set<int> s1;

    s1.insert(1);
    s1.insert(2);
    s1.insert(3);
    s1.insert(4);
    s1.insert(3);
    s1.insert(3);

    printSet(s1);
}

// set查找和统计操作测试
void setFindAndCountTest()
{
    using namespace std;

    set<int> s1;

    s1.insert(1);
    s1.insert(2);
    s1.insert(3);
    s1.insert(4);
    s1.insert(3);
    s1.insert(3);

    set<int>::iterator it = s1.find(3);
    if (it != s1.end()) {
        printf("found\r\n");
    } else {
        printf("not found\r\n");
    }

    int count = s1.count(3);
    printf("count: %d\r\n", count);
}

// set存放自定义类型数据时的排序规则测试
void setWithCustomTypeTest()
{
    using namespace std;

    auto sort = [](const Person& p1, const Person& p2) {
        return p1.age < p2.age;
    };

    set<Person, decltype(sort)> s(sort);

    Person p1("Tom", 20);
    Person p2("Jerry", 30);
    Person p3("Jack", 40);
    Person p4("Rose", 50);
    Person p5("Rose", 50);

    s.insert(p1);
    s.insert(p2);
    s.insert(p3);
    s.insert(p4);
    s.insert(p5);

    for (auto& person : s) {
        printf("Name: %s, Age: %d\r\n", person.name.c_str(), person.age);
    }
}

// map构造函数和赋值操作测试
void mapConstructorAndAssignmentTest()
{
    using namespace std;

    map<uint32_t, uint32_t> m1;
    m1.insert(pair<uint32_t, uint32_t>(1, 10));
    m1.insert(pair<uint32_t, uint32_t>(2, 10));
    m1.insert(pair<uint32_t, uint32_t>(3, 10));
    m1.insert(pair<uint32_t, uint32_t>(4, 10));
    printMap(m1);

    map<uint32_t, uint32_t> m2(m1);
    printMap(m2);

    map<uint32_t, uint32_t> m3 = m1;
    printMap(m3);
}

// map插入和删除操作测试
void mapInsertAndEraseTest()
{
    using namespace std;

    map<uint32_t, uint32_t> m1;
    m1.insert(pair<uint32_t, uint32_t>(1, 10));
    m1.insert(make_pair(2, 20));
    m1.insert(map<uint32_t, uint32_t>::value_type(3, 30));
    m1[4] = 40;
    printMap(m1);

    m1.erase(m1.begin());
    m1.erase(3); // 删除key为3的元素
    printMap(m1);

    m1.clear();
    printMap(m1);
}

#pragma endregion