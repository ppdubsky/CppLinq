#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq::Exceptions;

namespace CppLinq::Tests::SkipLast
{
    TEST(SkipLast, ReturnsExpectedValues_CountIsZero)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        const int expected[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        // Act.
        const auto actual = From(source).SkipLast(0U);

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(SkipLast, ReturnsExpectedValues_CountIsLessThanSourceLength)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        const int expected[]{ 1, 2, 3, 4, 5 };

        // Act.
        const auto actual = From(source).SkipLast(5U);

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(SkipLast, ReturnsExpectedValues_CountIsEqualToSourceLength)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        // Act.
        const auto actual = From(source).SkipLast(10U);

        // Assert.
        ExpectSequenceIsEmpty(actual);
    }

    TEST(SkipLast, ReturnsExpectedValues_CountIsGreaterThanSourceLength)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        // Act.
        const auto actual = From(source).SkipLast(15U);

        // Assert.
        ExpectSequenceIsEmpty(actual);
    }

    TEST(SkipLast, ReturnsSameResults)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.SkipLast(5U);
        const auto actual2 = query.SkipLast(5U);

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }

    TEST(SkipLast, SourceThrowsOnMoveNext)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        const auto query = From(source).SkipLast(5U);

        auto enumerator = query.GetEnumerator();
        while (enumerator.HasCurrent())
        {
            enumerator.MoveNext();
        }

        // Act.
        // Assert.
        EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
    }

    TEST(SkipLast, SourceThrowsOnGetCurrent)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        const auto query = From(source).SkipLast(5U);

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