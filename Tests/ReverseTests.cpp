#include <vector>

#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace CppLinq::Exceptions;
using namespace std;

TEST(Reverse, ReturnsExpectedValues_SourceIsEmpty)
{
    const vector<int> source;

    const auto actual = From(source).Reverse();

    ExpectSequenceIsEmpty(actual);
}

TEST(Reverse, ReturnsExpectedValues_SourceIsNotEmpty)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const int expected[]{ 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };

    const auto actual = From(source).Reverse();

    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(Reverse, ReturnsSameResults)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source);

    const auto actual1 = query.Reverse();
    const auto actual2 = query.Reverse();

    ExpectSequencesAreEquivalent(actual1, actual2);
}

TEST(Reverse, SourceThrowsOnMoveNext)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source).Reverse();

    auto& enumerator = query.GetEnumerator();
    while (!enumerator.IsFinished())
    {
        enumerator.MoveNext();
    }

    EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
}

TEST(Reverse, SourceThrowsOnGetCurrent)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source).Reverse();

    auto& enumerator = query.GetEnumerator();
    while (!enumerator.IsFinished())
    {
        enumerator.MoveNext();
    }

    EXPECT_THROW(enumerator.GetCurrent(), FinishedEnumeratorException);
}