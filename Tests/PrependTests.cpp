#include <vector>

#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace CppLinq::Exceptions;
using namespace std;

TEST(Prepend, ReturnsExpectedValues_SourceIsEmpty)
{
    vector<int> source;
    const int expected[]{ 11 };

    const auto actual = From(source).Prepend(11);

    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(Prepend, ReturnsExpectedValues_SourceIsNotEmpty)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const int expected[]{ 11, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    const auto actual = From(source).Prepend(11);

    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(Prepend, ReturnsSameResults)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source);

    const auto actual1 = query.Prepend(11);
    const auto actual2 = query.Prepend(11);

    ExpectSequencesAreEquivalent(actual1, actual2);
}

TEST(Prepend, SourceThrowsOnMoveNext)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source).Prepend(11);

    auto& enumerator = query.GetEnumerator();
    while (!enumerator.IsFinished())
    {
        enumerator.MoveNext();
    }

    EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
}

TEST(Prepend, SourceThrowsOnGetCurrent)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source).Prepend(11);

    auto& enumerator = query.GetEnumerator();
    while (!enumerator.IsFinished())
    {
        enumerator.MoveNext();
    }

    EXPECT_THROW(enumerator.GetCurrent(), FinishedEnumeratorException);
}