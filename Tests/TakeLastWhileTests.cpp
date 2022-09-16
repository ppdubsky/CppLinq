#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace CppLinq::Exceptions;

TEST(TakeLastWhile, ExecutionIsDeferred)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto isFunctionCalled = false;

    // Act.
    const auto actual = From(source).TakeLastWhile([&isFunctionCalled](const int /*value*/) { isFunctionCalled = true; return true; });

    // Assert.
    EXPECT_FALSE(isFunctionCalled);
}

TEST(TakeLastWhile, ReturnsExpectedValues_PredicateIsTrueForAll)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const int expected[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // Act.
    const auto actual = From(source).TakeLastWhile([](const int /*value*/){ return true; });

    // Assert.
    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(TakeLastWhile, ReturnsExpectedValues_PredicateIsFalseForAll)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // Act.
    const auto actual = From(source).TakeLastWhile([](const int /*value*/){ return false; });

    // Assert.
    ExpectSequenceIsEmpty(actual);
}

TEST(TakeLastWhile, ReturnsExpectedValues_PredicateIsTrueForValuesGreaterThanFive)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const int expected[]{ 6, 7, 8, 9, 10 };

    // Act.
    const auto actual = From(source).TakeLastWhile([](const int value){ return value > 5; });

    // Assert.
    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(TakeLastWhile, ReturnsSameResults)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    const auto query = From(source);

    // Act.
    const auto actual1 = query.TakeLastWhile([](const int value){ return value > 5; });
    const auto actual2 = query.TakeLastWhile([](const int value){ return value > 5; });

    // Assert.
    ExpectSequencesAreEquivalent(actual1, actual2);
}

TEST(TakeLastWhile, SourceThrowsOnMoveNext)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    const auto query = From(source).TakeLastWhile([](const int value){ return value > 5; });

    auto enumerator = query.GetEnumerator();
    while (enumerator.HasCurrent())
    {
        enumerator.MoveNext();
    }

    // Act.
    // Assert.
    EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
}

TEST(TakeLastWhile, SourceThrowsOnGetCurrent)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    const auto query = From(source).TakeLastWhile([](const int value){ return value > 5; });

    auto enumerator = query.GetEnumerator();
    while (enumerator.HasCurrent())
    {
        enumerator.MoveNext();
    }

    // Act.
    // Assert.
    EXPECT_THROW(enumerator.GetCurrent(), FinishedEnumeratorException);
}