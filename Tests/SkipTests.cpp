#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace CppLinq::Exceptions;

TEST(Skip, ReturnsExpectedValues_CountIsZero)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const int expected[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // Act.
    const auto actual = From(source).Skip(0U);

    // Assert.
    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(Skip, ReturnsExpectedValues_CountIsLessThanSourceLength)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const int expected[]{ 6, 7, 8, 9, 10 };

    // Act.
    const auto actual = From(source).Skip(5U);

    // Assert.
    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(Skip, ReturnsExpectedValues_CountIsEqualToSourceLength)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // Act.
    const auto actual = From(source).Skip(10U);

    // Assert.
    ExpectSequenceIsEmpty(actual);
}

TEST(Skip, ReturnsExpectedValues_CountIsGreaterThanSourceLength)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // Act.
    const auto actual = From(source).Skip(15U);

    // Assert.
    ExpectSequenceIsEmpty(actual);
}

TEST(Skip, ReturnsSameResults)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source);

    // Act.
    const auto actual1 = query.Skip(5U);
    const auto actual2 = query.Skip(5U);

    // Assert.
    ExpectSequencesAreEquivalent(actual1, actual2);
}

TEST(Skip, SourceThrowsOnMoveNext)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source).Skip(5U);

    auto& enumerator = query.GetEnumerator();
    while (!enumerator.IsFinished())
    {
        enumerator.MoveNext();
    }

    // Act.
    // Assert.
    EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
}

TEST(Skip, SourceThrowsOnGetCurrent)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source).Skip(5U);

    auto& enumerator = query.GetEnumerator();
    while (!enumerator.IsFinished())
    {
        enumerator.MoveNext();
    }

    // Act.
    // Assert.
    EXPECT_THROW(enumerator.GetCurrent(), FinishedEnumeratorException);
}