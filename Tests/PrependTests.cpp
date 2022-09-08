#include <vector>

#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace CppLinq::Exceptions;
using namespace std;

TEST(Prepend, ReturnsExpectedValues_SourceIsEmpty)
{
    // Arrange.
    const vector<int> source;
    const int expected[]{ 11 };

    // Act.
    const auto actual = From(source).Prepend(11);

    // Assert.
    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(Prepend, ReturnsExpectedValues_SourceIsNotEmpty)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const int expected[]{ 11, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // Act.
    const auto actual = From(source).Prepend(11);

    // Assert.
    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(Prepend, ReturnsSameResults)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    const auto query = From(source);

    // Act.
    const auto actual1 = query.Prepend(11);
    const auto actual2 = query.Prepend(11);

    // Assert.
    ExpectSequencesAreEquivalent(actual1, actual2);
}

TEST(Prepend, SourceThrowsOnMoveNext)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    const auto query = From(source).Prepend(11);

    auto enumerator = query.GetEnumerator();
    while (enumerator.HasCurrent())
    {
        enumerator.MoveNext();
    }

    // Act.
    // Assert.
    EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
}

TEST(Prepend, SourceThrowsOnGetCurrent)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    const auto query = From(source).Prepend(11);

    auto enumerator = query.GetEnumerator();
    while (enumerator.HasCurrent())
    {
        enumerator.MoveNext();
    }

    // Act.
    // Assert.
    EXPECT_THROW(enumerator.GetCurrent(), FinishedEnumeratorException);
}