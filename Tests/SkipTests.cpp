#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;

TEST(Skip, ReturnsExpectedValues_CountIsZero)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const int expected[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    const auto actual = From(source).Skip(0U);

    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(Skip, ReturnsExpectedValues_CountIsLessThanSourceLength)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const int expected[]{ 6, 7, 8, 9, 10 };

    const auto actual = From(source).Skip(5U);

    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(Skip, ReturnsExpectedValues_CountIsEqualToSourceLength)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    const auto actual = From(source).Skip(10U);

    ExpectSequenceIsEmpty(actual);
}

TEST(Skip, ReturnsExpectedValues_CountIsGreaterThanSourceLength)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    const auto actual = From(source).Skip(15U);

    ExpectSequenceIsEmpty(actual);
}