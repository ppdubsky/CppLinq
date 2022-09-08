#include <vector>

#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace CppLinq::Exceptions;
using namespace std;

TEST(Chunk, ReturnsExpectedChunks_SourceIsEmpty)
{
    // Arrange.
    const vector<int> source;
    const vector<vector<int>> expected;

    // Act.
    const auto actual = From(source).Chunk(3U);

    // Assert.
    ExpectSequenceIsEmpty(actual);
}

TEST(Chunk, ReturnsExpectedChunks_SourceContainsOneElement)
{
    // Arrange.
    const int source[]{ 1 };
    const vector<int> expected[]
    {
        { 1 }
    };

    // Act.
    const auto actual = From(source).Chunk(3U);

    // Assert.
    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(Chunk, ReturnsExpectedChunks_SourceContainsTwoElements)
{
    // Arrange.
    const int source[]{ 1, 2 };
    const vector<int> expected[]
    {
        { 1, 2 }
    };

    // Act.
    const auto actual = From(source).Chunk(3U);

    // Assert.
    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(Chunk, ReturnsExpectedChunks_SourceContainsThreeElements)
{
    // Arrange.
    const int source[]{ 1, 2, 3 };
    const vector<int> expected[]
    {
        { 1, 2, 3 }
    };

    // Act.
    const auto actual = From(source).Chunk(3U);

    // Assert.
    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(Chunk, ReturnsExpectedChunks_SourceContainsFourElements)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4 };
    const vector<int> expected[]
    {
        { 1, 2, 3 },
        { 4 }
    };

    // Act.
    const auto actual = From(source).Chunk(3U);

    // Assert.
    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(Chunk, ReturnsExpectedChunks_SourceContainsFiveElements)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5 };
    const vector<int> expected[]
    {
        { 1, 2, 3 },
        { 4, 5 }
    };

    // Act.
    const auto actual = From(source).Chunk(3U);

    // Assert.
    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(Chunk, ReturnsExpectedChunks_SourceContainsSixElements)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6 };
    const vector<int> expected[]
    {
        { 1, 2, 3 },
        { 4, 5, 6 }
    };

    // Act.
    const auto actual = From(source).Chunk(3U);

    // Assert.
    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(Chunk, ReturnsExpectedChunks_SourceContainsSevenElements)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7 };
    const vector<int> expected[]
    {
        { 1, 2, 3 },
        { 4, 5, 6 },
        { 7 }
    };

    // Act.
    const auto actual = From(source).Chunk(3U);

    // Assert.
    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(Chunk, ReturnsSameResults)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    const auto query = From(source);

    // Act.
    const auto actual1 = query.Chunk(3U);
    const auto actual2 = query.Chunk(3U);

    // Assert.
    ExpectSequencesAreEquivalent(actual1, actual2);
}

TEST(Chunk, ThrowsOnZeroSize)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source);

    // Act.
    // Assert.
    EXPECT_THROW(query.Chunk(0U), ArgumentOutOfRangeException);
}

TEST(Chunk, SourceThrowsOnMoveNext)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    const auto query = From(source).Chunk(3U);

    auto enumerator = query.GetEnumerator();
    while (enumerator.HasCurrent())
    {
        enumerator.MoveNext();
    }

    // Act.
    // Assert.
    EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
}

TEST(Chunk, SourceThrowsOnGetCurrent)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    const auto query = From(source).Chunk(3U);

    auto enumerator = query.GetEnumerator();
    while (enumerator.HasCurrent())
    {
        enumerator.MoveNext();
    }

    // Act.
    // Assert.
    EXPECT_THROW(enumerator.GetCurrent(), FinishedEnumeratorException);
}