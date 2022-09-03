#include <functional>

#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace CppLinq::Exceptions;
using namespace std;

TEST(ForEach, ExecutionIsDeferred)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto isFunctionCalled = false;

    const auto actual = From(source).ForEach([&isFunctionCalled](const int /*value*/) { isFunctionCalled = true; });

    EXPECT_FALSE(isFunctionCalled);
}

TEST(ForEach, ReturnsExpectedValues)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const int expected[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    int sum = 0;

    const auto actual = From(source).ForEach([&sum](const int value){ sum += value; });

    ExpectSequencesAreEquivalent(actual, expected);

    EXPECT_EQ(sum, 55);
}

TEST(ForEach, ReturnsSameResults)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source);

    const auto actual1 = query.ForEach([](const int /*value*/){});
    const auto actual2 = query.ForEach([](const int /*value*/){});

    ExpectSequencesAreEquivalent(actual1, actual2);
}

TEST(ForEach, SourceThrowsOnMoveNext)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source).ForEach([](const int /*value*/){});

    auto& enumerator = query.GetEnumerator();
    while (!enumerator.IsFinished())
    {
        enumerator.MoveNext();
    }

    EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
}

TEST(ForEach, SourceThrowsOnGetCurrent)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source).ForEach([](const int /*value*/){});

    auto& enumerator = query.GetEnumerator();
    while (!enumerator.IsFinished())
    {
        enumerator.MoveNext();
    }

    EXPECT_THROW(enumerator.GetCurrent(), FinishedEnumeratorException);
}