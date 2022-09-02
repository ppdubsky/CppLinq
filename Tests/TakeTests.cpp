#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace CppLinq::Exceptions;

TEST(Take, ReturnsExpectedValues_CountIsZero)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    const auto actual = From(source).Take(0U);

    ExpectSequenceIsEmpty(actual);
}

TEST(Take, ReturnsExpectedValues_CountIsLessThanSourceLength)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const int expected[]{ 1, 2, 3 , 4, 5 };

    const auto actual = From(source).Take(5U);

    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(Take, ReturnsExpectedValues_CountIsEqualToSourceLength)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const int expected[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    const auto actual = From(source).Take(10U);

    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(Take, ReturnsExpectedValues_CountIsGreaterThanSourceLength)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const int expected[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    const auto actual = From(source).Take(15U);

    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(Take, SourceThrowsOnMoveNext)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source).Take(5U);

    auto& enumerator = query.GetEnumerator();
    while (!enumerator.IsFinished())
    {
        enumerator.MoveNext();
    }

    EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
}

TEST(Take, SourceThrowsOnGetCurrent)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source).Take(5U);

    auto& enumerator = query.GetEnumerator();
    while (!enumerator.IsFinished())
    {
        enumerator.MoveNext();
    }

    EXPECT_THROW(enumerator.GetCurrent(), FinishedEnumeratorException);
}