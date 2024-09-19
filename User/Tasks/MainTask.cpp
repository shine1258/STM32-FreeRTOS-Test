#include "MainTask.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <type_traits>

class Person {
public:
    int age = 10;
    int height = 100;
};

template <class T>
bool myCompare(T a, T b)
{
    return a == b;
}

template <>
bool myCompare(Person a, Person b)
{
    return a.age == b.age && a.height == b.height;
}

void MainTask_Run(void)
{
    // uint32_t a = 10;
    // uint32_t b = 20;

    // myPrint<uint32_t>(a, b, 100);

    char c1 = 'a';
    char c2 = 'b';

    printf("%d\r\n", myCompare(c1, c2));

    Person p1;
    Person p2;

    printf("%d\r\n", myCompare(p1, p2));

    while (true) { }
}
