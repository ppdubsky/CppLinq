#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;

TEST(Take, First3)
{
    const int values[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const int expected[]{ 1, 2, 3 };

    const auto actual = From(values).Take(3U);

    ExpectSequencesAreEqual(actual, expected);
}