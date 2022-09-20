#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq::Exceptions;
using namespace std;

namespace CppLinq::Tests::Reverse
{
    TEST(Reverse, ReturnsExpectedValues_SourceIsEmpty)
    {
        // Arrange.
        const vector<int> source;

        // Act.
        const auto actual = From(source).Reverse();

        // Assert.
        ExpectSequenceIsEmpty(actual);
    }

    TEST(Reverse, ReturnsExpectedValues_SourceIsNotEmpty)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        const int expected[]{ 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };

        // Act.
        const auto actual = From(source).Reverse();

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Reverse, ReturnsSameResults)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.Reverse();
        const auto actual2 = query.Reverse();

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }

    TEST(Reverse, SourceThrowsOnMoveNext)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        const auto query = From(source).Reverse();

        auto enumerator = query.GetEnumerator();
        while (enumerator.HasCurrent())
        {
            enumerator.MoveNext();
        }

        // Act.
        // Assert.
        EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
    }

    TEST(Reverse, SourceThrowsOnGetCurrent)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        const auto query = From(source).Reverse();

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