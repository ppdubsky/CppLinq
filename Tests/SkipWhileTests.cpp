#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace CppLinq::Exceptions;

TEST(SkipWhile, ExecutionIsDeferred)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto isFunctionCalled = false;

    // Act.
    const auto actual = From(source).SkipWhile([&isFunctionCalled](const int /*value*/) { isFunctionCalled = true; return false; });

    // Assert.
    EXPECT_FALSE(isFunctionCalled);
}

TEST(SkipWhile, ReturnsExpectedValues_PredicateIsTrueForAll)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // Act.
    const auto actual = From(source).SkipWhile([](const int /*value*/){ return true; });

    // Assert.
    ExpectSequenceIsEmpty(actual);
}

TEST(SkipWhile, ReturnsExpectedValues_PredicateIsFalseForAll)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const int expected[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // Act.
    const auto actual = From(source).SkipWhile([](const int /*value*/){ return false; });

    // Assert.
    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(SkipWhile, ReturnsExpectedValues_PredicateIsTrueForValuesLessThanFive)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const int expected[]{ 5, 6, 7, 8, 9, 10 };

    // Act.
    const auto actual = From(source).SkipWhile([](const int value){ return value < 5; });

    // Assert.
    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(SkipWhile, ReturnsSameResults)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source);

    // Act.
    const auto actual1 = query.SkipWhile([](const int value){ return value < 5; });
    const auto actual2 = query.SkipWhile([](const int value){ return value < 5; });

    // Assert.
    ExpectSequencesAreEquivalent(actual1, actual2);
}

TEST(SkipWhile, SourceThrowsOnMoveNext)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source).SkipWhile([](const int value){ return value < 5; });

    auto& enumerator = query.GetEnumerator();
    while (!enumerator.IsFinished())
    {
        enumerator.MoveNext();
    }

    // Act.
    // Assert.
    EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
}

TEST(SkipWhile, SourceThrowsOnGetCurrent)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source).SkipWhile([](const int value){ return value < 5; });

    auto& enumerator = query.GetEnumerator();
    while (!enumerator.IsFinished())
    {
        enumerator.MoveNext();
    }

    // Act.
    // Assert.
    EXPECT_THROW(enumerator.GetCurrent(), FinishedEnumeratorException);
}