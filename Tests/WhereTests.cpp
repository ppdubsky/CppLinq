#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;

TEST(Where, EvenIntegers)
{
    const int values[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const int expected[]{ 2, 4, 6, 8, 10 };

    const auto actual = From(values).Where([](const int value){ return value % 2 == 0; });

    ExpectSequencesAreEqual(actual, expected);
}