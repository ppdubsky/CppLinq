#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;

TEST(StaticCast, DoubleToInteger)
{
    const double values[]{ 1.1, 2.2, 3.3, 4.4, 5.5 };
    const int expected[]{ 1, 2, 3, 4, 5 };

    const auto actual = From(values).StaticCast<int>();

    ExpectSequencesAreEqual(actual, expected);
}