#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace CppLinq::Exceptions;

TEST(SkipLastWhile, ExecutionIsDeferred)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto isFunctionCalled = false;

    // Act.
    const auto actual = From(source).SkipLastWhile([&isFunctionCalled](const int /*value*/) { isFunctionCalled = true; return false; });

    // Assert.
    EXPECT_FALSE(isFunctionCalled);
}

TEST(SkipLastWhile, ReturnsExpectedValues_PredicateIsTrueForAll)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // Act.
    const auto actual = From(source).SkipLastWhile([](const int /*value*/){ return true; });

    // Assert.
    ExpectSequenceIsEmpty(actual);
}

TEST(SkipLastWhile, ReturnsExpectedValues_PredicateIsFalseForAll)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const int expected[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // Act.
    const auto actual = From(source).SkipLastWhile([](const int /*value*/){ return false; });

    // Assert.
    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(SkipLastWhile, ReturnsExpectedValues_PredicateIsTrueForValuesGreaterThanFive)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const int expected[]{ 1, 2, 3, 4, 5 };

    // Act.
    const auto actual = From(source).SkipLastWhile([](const int value){ return value > 5; });

    // Assert.
    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(SkipLastWhile, ReturnsSameResults)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    const auto query = From(source);

    // Act.
    const auto actual1 = query.SkipLastWhile([](const int value){ return value > 5; });
    const auto actual2 = query.SkipLastWhile([](const int value){ return value > 5; });

    // Assert.
    ExpectSequencesAreEquivalent(actual1, actual2);
}

TEST(SkipLastWhile, SourceThrowsOnMoveNext)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    const auto query = From(source).SkipLastWhile([](const int value){ return value > 5; });

    auto enumerator = query.GetEnumerator();
    while (enumerator.HasCurrent())
    {
        enumerator.MoveNext();
    }

    // Act.
    // Assert.
    EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
}

TEST(SkipLastWhile, SourceThrowsOnGetCurrent)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    const auto query = From(source).SkipLastWhile([](const int value){ return value > 5; });

    auto enumerator = query.GetEnumerator();
    while (enumerator.HasCurrent())
    {
        enumerator.MoveNext();
    }

    // Act.
    // Assert.
    EXPECT_THROW(enumerator.GetCurrent(), FinishedEnumeratorException);
}