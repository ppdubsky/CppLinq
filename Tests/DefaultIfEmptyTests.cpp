#include <vector>

#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace CppLinq::Exceptions;
using namespace std;

TEST(DefaultIfEmpty, ReturnsDefault_SourceIsEmpty)
{
    vector<int> source;
    const int expected[]{ 11 };

    const auto actual = From(source).DefaultIfEmpty(11);

    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(DefaultIfEmpty, ReturnsSource_SourceIsNotEmpty)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const int expected[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    const auto actual = From(source).DefaultIfEmpty(11);

    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(DefaultIfEmpty, ReturnsSameResults_SourceIsEmpty)
{
    vector<int> source;

    auto query = From(source);

    const auto actual1 = query.DefaultIfEmpty(11);
    const auto actual2 = query.DefaultIfEmpty(11);

    ExpectSequencesAreEquivalent(actual1, actual2);
}

TEST(DefaultIfEmpty, ReturnsSameResults_SourceIsNotEmpty)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source);

    const auto actual1 = query.DefaultIfEmpty(11);
    const auto actual2 = query.DefaultIfEmpty(11);

    ExpectSequencesAreEquivalent(actual1, actual2);
}

TEST(DefaultIfEmpty, SourceThrowsOnMoveNext)
{
    vector<int> source;

    auto query = From(source).DefaultIfEmpty(11);

    auto& enumerator = query.GetEnumerator();
    while (!enumerator.IsFinished())
    {
        enumerator.MoveNext();
    }

    EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
}

TEST(DefaultIfEmpty, SourceThrowsOnGetCurrent)
{
    vector<int> source;

    auto query = From(source).DefaultIfEmpty(11);

    auto& enumerator = query.GetEnumerator();
    while (!enumerator.IsFinished())
    {
        enumerator.MoveNext();
    }

    EXPECT_THROW(enumerator.GetCurrent(), FinishedEnumeratorException);
}