#include <vector>

#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace CppLinq::Exceptions;
using namespace std;

TEST(OrderBy, ReturnsExpectedValues_SourceIsEmpty)
{
    const vector<int> source;

    const auto actual = From(source).OrderBy();

    ExpectSequenceIsEmpty(actual);
}

TEST(OrderBy, ReturnsExpectedValues_SourceIsNotEmpty)
{
    const int source[]{ 1, 3, 5, 7, 9, 10, 8, 6, 4, 2 };
    const int expected[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    const auto actual = From(source).OrderBy();

    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(OrderBy, ReturnsSameResults)
{
    const int source[]{ 1, 3, 5, 7, 9, 10, 8, 6, 4, 2 };

    auto query = From(source);

    const auto actual1 = query.OrderBy();
    const auto actual2 = query.OrderBy();

    ExpectSequencesAreEquivalent(actual1, actual2);
}

TEST(OrderBy, SourceThrowsOnMoveNext)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source).OrderBy();

    auto& enumerator = query.GetEnumerator();
    while (!enumerator.IsFinished())
    {
        enumerator.MoveNext();
    }

    EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
}

TEST(OrderBy, SourceThrowsOnGetCurrent)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source).OrderBy();

    auto& enumerator = query.GetEnumerator();
    while (!enumerator.IsFinished())
    {
        enumerator.MoveNext();
    }

    EXPECT_THROW(enumerator.GetCurrent(), FinishedEnumeratorException);
}