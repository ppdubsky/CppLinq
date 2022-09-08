#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace CppLinq::Exceptions;

TEST(Take, ReturnsExpectedValues_CountIsZero)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // Act.
    const auto actual = From(source).Take(0U);

    // Assert.
    ExpectSequenceIsEmpty(actual);
}

TEST(Take, ReturnsExpectedValues_CountIsLessThanSourceLength)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const int expected[]{ 1, 2, 3 , 4, 5 };

    // Act.
    const auto actual = From(source).Take(5U);

    // Assert.
    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(Take, ReturnsExpectedValues_CountIsEqualToSourceLength)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const int expected[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // Act.
    const auto actual = From(source).Take(10U);

    // Assert.
    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(Take, ReturnsExpectedValues_CountIsGreaterThanSourceLength)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const int expected[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // Act.
    const auto actual = From(source).Take(15U);

    // Assert.
    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(Take, ReturnsSameResults)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    const auto query = From(source);

    // Act.
    const auto actual1 = query.Take(5U);
    const auto actual2 = query.Take(5U);

    // Assert.
    ExpectSequencesAreEquivalent(actual1, actual2);
}

TEST(Take, SourceThrowsOnMoveNext)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    const auto query = From(source).Take(5U);

    auto enumerator = query.GetEnumerator();
    while (enumerator.HasCurrent())
    {
        enumerator.MoveNext();
    }

    // Act.
    // Assert.
    EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
}

TEST(Take, SourceThrowsOnGetCurrent)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    const auto query = From(source).Take(5U);

    auto enumerator = query.GetEnumerator();
    while (enumerator.HasCurrent())
    {
        enumerator.MoveNext();
    }

    // Act.
    // Assert.
    EXPECT_THROW(enumerator.GetCurrent(), FinishedEnumeratorException);
}