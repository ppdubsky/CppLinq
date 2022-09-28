#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq::Exceptions;

namespace CppLinq::Tests::StaticCast
{
    TEST(StaticCast, ReturnsExpectedValues_DoubleToInt)
    {
        // Arrange.
        const double source[]{ 1.1, 2.2, 3.3, 4.4, 5.5 };
        const int expected[]{ 1, 2, 3, 4, 5 };

        // Act.
        const auto actual = From(source).StaticCast<int>();

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(StaticCast, ReturnsSameResults)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.StaticCast<int>();
        const auto actual2 = query.StaticCast<int>();

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }

    TEST(StaticCast, SourceThrowsOnMoveNext)
    {
        // Arrange.
        const double source[]{ 1.1, 2.2, 3.3, 4.4, 5.5 };

        const auto query = From(source).StaticCast<int>();

        auto enumerator = query.GetEnumerator();
        while (enumerator.HasCurrent())
        {
            enumerator.MoveNext();
        }

        // Act.
        // Assert.
        EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
    }

    TEST(StaticCast, SourceThrowsOnGetCurrent)
    {
        // Arrange.
        const double source[]{ 1.1, 2.2, 3.3, 4.4, 5.5 };

        const auto query = From(source).StaticCast<int>();

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