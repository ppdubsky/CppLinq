#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace CppLinq::Exceptions;

TEST(TakeWhile, ExecutionIsDeferred)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto isFunctionCalled = false;

    const auto actual = From(source).TakeWhile([&isFunctionCalled](const int /*value*/) { isFunctionCalled = true; return true; });

    EXPECT_FALSE(isFunctionCalled);
}

TEST(TakeWhile, ReturnsExpectedValues_PredicateIsTrueForAll)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const int expected[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    const auto actual = From(source).TakeWhile([](const int /*value*/){ return true; });

    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(TakeWhile, ReturnsExpectedValues_PredicateIsFalseForAll)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    const auto actual = From(source).TakeWhile([](const int /*value*/){ return false; });

    ExpectSequenceIsEmpty(actual);
}

TEST(TakeWhile, ReturnsExpectedValues_PredicateIsTrueForValuesLessThanFive)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const int expected[]{ 1, 2, 3, 4 };

    const auto actual = From(source).TakeWhile([](const int value){ return value < 5; });

    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(TakeWhile, ReturnsSameResults)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source);

    const auto actual1 = query.TakeWhile([](const int value){ return value < 5; });
    const auto actual2 = query.TakeWhile([](const int value){ return value < 5; });

    ExpectSequencesAreEquivalent(actual1, actual2);
}

TEST(TakeWhile, SourceThrowsOnMoveNext)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source).TakeWhile([](const int value){ return value < 5; });

    auto& enumerator = query.GetEnumerator();
    while (!enumerator.IsFinished())
    {
        enumerator.MoveNext();
    }

    EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
}

TEST(TakeWhile, SourceThrowsOnGetCurrent)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source).TakeWhile([](const int value){ return value < 5; });

    auto& enumerator = query.GetEnumerator();
    while (!enumerator.IsFinished())
    {
        enumerator.MoveNext();
    }

    EXPECT_THROW(enumerator.GetCurrent(), FinishedEnumeratorException);
}