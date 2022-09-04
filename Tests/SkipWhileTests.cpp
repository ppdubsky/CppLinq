#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace CppLinq::Exceptions;

TEST(SkipWhile, ExecutionIsDeferred)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto isFunctionCalled = false;

    const auto actual = From(source).SkipWhile([&isFunctionCalled](const int /*value*/) { isFunctionCalled = true; return false; });

    EXPECT_FALSE(isFunctionCalled);
}

TEST(SkipWhile, ReturnsExpectedValues_PredicateIsTrueForAll)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    const auto actual = From(source).SkipWhile([](const int /*value*/){ return true; });

    ExpectSequenceIsEmpty(actual);
}

TEST(SkipWhile, ReturnsExpectedValues_PredicateIsFalseForAll)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const int expected[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    const auto actual = From(source).SkipWhile([](const int /*value*/){ return false; });

    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(SkipWhile, ReturnsExpectedValues_PredicateIsTrueForValuesLessThanFive)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const int expected[]{ 5, 6, 7, 8, 9, 10 };

    const auto actual = From(source).SkipWhile([](const int value){ return value < 5; });

    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(SkipWhile, ReturnsSameResults)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source);

    const auto actual1 = query.SkipWhile([](const int value){ return value < 5; });
    const auto actual2 = query.SkipWhile([](const int value){ return value < 5; });

    ExpectSequencesAreEquivalent(actual1, actual2);
}

TEST(SkipWhile, SourceThrowsOnMoveNext)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source).SkipWhile([](const int value){ return value < 5; });

    auto& enumerator = query.GetEnumerator();
    while (!enumerator.IsFinished())
    {
        enumerator.MoveNext();
    }

    EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
}

TEST(SkipWhile, SourceThrowsOnGetCurrent)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source).SkipWhile([](const int value){ return value < 5; });

    auto& enumerator = query.GetEnumerator();
    while (!enumerator.IsFinished())
    {
        enumerator.MoveNext();
    }

    EXPECT_THROW(enumerator.GetCurrent(), FinishedEnumeratorException);
}