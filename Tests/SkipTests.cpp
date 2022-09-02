#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;

TEST(Skip, First3)
{
    const int values[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const int expected[]{ 4, 5, 6, 7, 8, 9, 10 };

    const auto actual = From(values).Skip(3U);

    ExpectSequencesAreEqual(actual, expected);
}