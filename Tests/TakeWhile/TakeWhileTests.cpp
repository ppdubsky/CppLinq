#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq::Exceptions;

namespace CppLinq::Tests::TakeWhile
{
    TEST(TakeWhile, ExecutionIsDeferred)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        auto isFunctionCalled = false;

        // Act.
        const auto actual = From(source).TakeWhile([&isFunctionCalled](const int /*value*/) { isFunctionCalled = true; return true; });

        // Assert.
        EXPECT_FALSE(isFunctionCalled);
    }

    TEST(TakeWhile, ReturnsExpectedValues_PredicateIsTrueForAll)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        const int expected[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        // Act.
        const auto actual = From(source).TakeWhile([](const int /*value*/){ return true; });

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(TakeWhile, ReturnsExpectedValues_PredicateIsFalseForAll)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        // Act.
        const auto actual = From(source).TakeWhile([](const int /*value*/){ return false; });

        // Assert.
        ExpectSequenceIsEmpty(actual);
    }

    TEST(TakeWhile, ReturnsExpectedValues_PredicateIsTrueForValuesLessThanFive)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        const int expected[]{ 1, 2, 3, 4 };

        // Act.
        const auto actual = From(source).TakeWhile([](const int value){ return value < 5; });

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(TakeWhile, ReturnsSameResults)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.TakeWhile([](const int value){ return value < 5; });
        const auto actual2 = query.TakeWhile([](const int value){ return value < 5; });

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }

    TEST(TakeWhile, SourceThrowsOnMoveNext)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        const auto query = From(source).TakeWhile([](const int value){ return value < 5; });

        auto enumerator = query.GetEnumerator();
        while (enumerator.HasCurrent())
        {
            enumerator.MoveNext();
        }

        // Act.
        // Assert.
        EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
    }

    TEST(TakeWhile, SourceThrowsOnGetCurrent)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        const auto query = From(source).TakeWhile([](const int value){ return value < 5; });

        auto enumerator = query.GetEnumerator();
        while (enumerator.HasCurrent())
        {
            enumerator.MoveNext();
        }

        // Act.
        // Assert.
        EXPECT_THROW(enumerator.GetCurrent(), FinishedEnumeratorException);
    }
}