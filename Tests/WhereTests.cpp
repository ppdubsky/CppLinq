#include <functional>

#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace CppLinq::Exceptions;
using namespace std;

TEST(Where, ExecutionIsDeferred)
{
    // Arrange.
    auto isActionCalled = false;

    const function<void()> source[]
    {
        [&isActionCalled]() { isActionCalled = true; }
    };

    // Act.
    const auto actual = From(source).Where([](const function<void()> action) { action(); return true; });

    // Assert.
    EXPECT_FALSE(isActionCalled);
}

TEST(Where, ReturnsExpectedValues_PredicateIsTrueForAll)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const int expected[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // Act.
    const auto actual = From(source).Where([](const int /*value*/){ return true; });

    // Assert.
    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(Where, ReturnsExpectedValues_PredicateIsFalseForAll)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // Act.
    const auto actual = From(source).Where([](const int /*value*/){ return false; });

    // Assert.
    ExpectSequenceIsEmpty(actual);
}

TEST(Where, ReturnsExpectedValues_PredicateIsTrueForEven)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const int expected[]{ 2, 4, 6, 8, 10 };

    // Act.
    const auto actual = From(source).Where([](const int value){ return value % 2 == 0; });

    // Assert.
    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(Where, ReturnsSameResults)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    const auto query = From(source);

    // Act.
    const auto actual1 = query.Where([](const int value){ return value % 2 == 0; });
    const auto actual2 = query.Where([](const int value){ return value % 2 == 0; });

    // Assert.
    ExpectSequencesAreEquivalent(actual1, actual2);
}

TEST(Where, SourceThrowsOnMoveNext)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    const auto query = From(source).Where([](const int value){ return value % 2 == 0; });

    auto enumerator = query.GetEnumerator();
    while (enumerator.HasCurrent())
    {
        enumerator.MoveNext();
    }

    // Act.
    // Assert.
    EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
}

TEST(Where, SourceThrowsOnGetCurrent)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    const auto query = From(source).Where([](const int value){ return value % 2 == 0; });

    auto enumerator = query.GetEnumerator();
    while (enumerator.HasCurrent())
    {
        enumerator.MoveNext();
    }

    // Act.
    // Assert.
    EXPECT_THROW(enumerator.GetCurrent(), FinishedEnumeratorException);
}