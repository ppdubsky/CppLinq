#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq::Exceptions;
using namespace std;

namespace CppLinq::Tests::DefaultIfEmpty
{
    TEST(DefaultIfEmpty, ReturnsDefault_SourceIsEmpty)
    {
        // Arrange.
        const vector<int> source;
        const int expected[]{ 11 };

        // Act.
        const auto actual = From(source).DefaultIfEmpty(11);

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(DefaultIfEmpty, ReturnsSource_SourceIsNotEmpty)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        const int expected[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        // Act.
        const auto actual = From(source).DefaultIfEmpty(11);

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(DefaultIfEmpty, ReturnsSameResults_SourceIsEmpty)
    {
        // Arrange.
        const vector<int> source;

        const auto query = From(source);

        // Act.
        const auto actual1 = query.DefaultIfEmpty(11);
        const auto actual2 = query.DefaultIfEmpty(11);

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }

    TEST(DefaultIfEmpty, ReturnsSameResults_SourceIsNotEmpty)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.DefaultIfEmpty(11);
        const auto actual2 = query.DefaultIfEmpty(11);

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }

    TEST(DefaultIfEmpty, SourceThrowsOnMoveNext)
    {
        // Arrange.
        const vector<int> source;

        const auto query = From(source).DefaultIfEmpty(11);

        auto enumerator = query.GetEnumerator();
        while (enumerator.HasCurrent())
        {
            enumerator.MoveNext();
        }

        // Act.
        // Assert.
        EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
    }

    TEST(DefaultIfEmpty, SourceThrowsOnGetCurrent)
    {
        // Arrange.
        const vector<int> source;

        const auto query = From(source).DefaultIfEmpty(11);

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