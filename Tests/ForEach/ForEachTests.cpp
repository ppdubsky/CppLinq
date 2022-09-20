#include <functional>

#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq::Exceptions;
using namespace std;

namespace CppLinq::Tests::ForEach
{
    TEST(ForEach, ExecutionIsDeferred)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        auto isFunctionCalled = false;

        // Act.
        const auto actual = From(source).ForEach([&isFunctionCalled](const int /*value*/) { isFunctionCalled = true; });

        // Assert.
        EXPECT_FALSE(isFunctionCalled);
    }

    TEST(ForEach, ReturnsExpectedValues)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        const int expected[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        auto sum = 0;

        // Act.
        const auto actual = From(source).ForEach([&sum](const int value){ sum += value; });

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);

        EXPECT_EQ(sum, 55);
    }

    TEST(ForEach, ReturnsSameResults)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.ForEach([](const int /*value*/){});
        const auto actual2 = query.ForEach([](const int /*value*/){});

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }

    TEST(ForEach, SourceThrowsOnMoveNext)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        const auto query = From(source).ForEach([](const int /*value*/){});

        auto enumerator = query.GetEnumerator();
        while (enumerator.HasCurrent())
        {
            enumerator.MoveNext();
        }

        // Act.
        // Assert.
        EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
    }

    TEST(ForEach, SourceThrowsOnGetCurrent)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        const auto query = From(source).ForEach([](const int /*value*/){});

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