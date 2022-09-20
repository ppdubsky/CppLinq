#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq::Exceptions;
using namespace std;

namespace CppLinq::Tests::Append
{
    TEST(Append, ReturnsExpectedValues_SourceIsEmpty)
    {
        // Arrange.
        const vector<int> source;
        const int expected[]{ 11 };

        // Act.
        const auto actual = From(source).Append(11);

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Append, ReturnsExpectedValues_SourceIsNotEmpty)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        const int expected[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };

        // Act.
        const auto actual = From(source).Append(11);

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Append, ReturnsSameResults)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.Append(11);
        const auto actual2 = query.Append(11);

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }

    TEST(Append, SourceThrowsOnMoveNext)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        const auto query = From(source).Append(11);

        auto enumerator = query.GetEnumerator();
        while (enumerator.HasCurrent())
        {
            enumerator.MoveNext();
        }

        // Act.
        // Assert.
        EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
    }

    TEST(Append, SourceThrowsOnGetCurrent)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        const auto query = From(source).Append(11);

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