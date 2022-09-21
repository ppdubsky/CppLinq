#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq::Exceptions;

namespace CppLinq::Tests::TakeLast
{
    TEST(TakeLast, ReturnsExpectedValues_CountIsZero)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        // Act.
        const auto actual = From(source).TakeLast(0U);

        // Assert.
        ExpectSequenceIsEmpty(actual);
    }

    TEST(TakeLast, ReturnsExpectedValues_CountIsLessThanSourceLength)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        const int expected[]{ 6, 7, 8, 9, 10 };

        // Act.
        const auto actual = From(source).TakeLast(5U);

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(TakeLast, ReturnsExpectedValues_CountIsEqualToSourceLength)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        const int expected[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        // Act.
        const auto actual = From(source).TakeLast(10U);

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(TakeLast, ReturnsExpectedValues_CountIsGreaterThanSourceLength)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        const int expected[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        // Act.
        const auto actual = From(source).TakeLast(15U);

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(TakeLast, ReturnsSameResults)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.TakeLast(5U);
        const auto actual2 = query.TakeLast(5U);

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }

    TEST(TakeLast, SourceThrowsOnMoveNext)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        const auto query = From(source).TakeLast(5U);

        auto enumerator = query.GetEnumerator();
        while (enumerator.HasCurrent())
        {
            enumerator.MoveNext();
        }

        // Act.
        // Assert.
        EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
    }

    TEST(TakeLast, SourceThrowsOnGetCurrent)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        const auto query = From(source).TakeLast(5U);

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