#include <functional>

#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace std;

TEST(Where, ExecutionIsDeferred)
{
    auto isActionCalled = false;

    const function<void()> source[]
    {
        [&isActionCalled]() { isActionCalled = true; }
    };

    const auto actual = From(source).Where([](const function<void()> action) { action(); return true; });

    EXPECT_FALSE(isActionCalled);
}

TEST(Where, ReturnsExpectedValues_PredicateIsTrueForAll)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const int expected[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    const auto actual = From(source).Where([](const int /*value*/){ return true; });

    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(Where, ReturnsExpectedValues_PredicateIsFalseForAll)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    const auto actual = From(source).Where([](const int /*value*/){ return false; });

    ExpectSequenceIsEmpty(actual);
}

TEST(Where, ReturnsExpectedValues_PredicateIsTrueForEven)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const int expected[]{ 2, 4, 6, 8, 10 };

    const auto actual = From(source).Where([](const int value){ return value % 2 == 0; });

    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(Where, ReturnsSameResults)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source);

    const auto actual1 = query.Where([](const int value){ return value % 2 == 0; });
    const auto actual2 = query.Where([](const int value){ return value % 2 == 0; });

    ExpectSequencesAreEquivalent(actual1, actual2);
}