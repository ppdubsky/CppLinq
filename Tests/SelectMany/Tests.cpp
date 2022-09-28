#include <cstdint>
#include <string>
#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"
#include "SelectMany/Order.hpp"

using namespace CppLinq::Exceptions;
using namespace std;

namespace CppLinq::Tests::SelectMany
{
    TEST(SelectMany, ReturnsExpectedValues_SourceIsNotEmpty)
    {
        // Arrange.
        const Order source[]
        {
            { 1U, { 1, 2, 3 } },
            { 2U, { 4, 5 } },
            { 3U, { 6, 7, 8, 9 } },
            { 4U, { } },
            { 5U, { 10 } }
        };
        const int expected[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        // Act.
        const auto actual = From(source).SelectMany([](const Order& order){ return order.items; });

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(SelectMany, ReturnsExpectedValues_SourceIsEmpty)
    {
        // Arrange.
        const vector<Order> source;

        // Act.
        const auto actual = From(source).SelectMany([](const Order& order){ return order.items; });

        // Assert.
        ExpectSequenceIsEmpty(actual);
    }

    TEST(SelectMany, ReturnsSameResults)
    {
        // Arrange.
        const Order source[]
        {
            { 1U, { 1, 2, 3 } },
            { 2U, { 4, 5 } },
            { 3U, { 6, 7, 8, 9 } },
            { 4U, { } },
            { 5U, { 10 } }
        };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.SelectMany([](const Order& order){ return order.items; });
        const auto actual2 = query.SelectMany([](const Order& order){ return order.items; });

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }

    TEST(SelectMany, SourceThrowsOnMoveNext)
    {
        // Arrange.
        const Order source[]
        {
            { 1U, { 1, 2, 3 } },
            { 2U, { 4, 5 } },
            { 3U, { 6, 7, 8, 9 } },
            { 4U, { } },
            { 5U, { 10 } }
        };

        const auto query = From(source).SelectMany([](const Order& order){ return order.items; });

        auto enumerator = query.GetEnumerator();
        while (enumerator.HasCurrent())
        {
            enumerator.MoveNext();
        }

        // Act.
        // Assert.
        EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
    }

    TEST(SelectMany, SourceThrowsOnGetCurrent)
    {
        // Arrange.
        const Order source[]
        {
            { 1U, { 1, 2, 3 } },
            { 2U, { 4, 5 } },
            { 3U, { 6, 7, 8, 9 } },
            { 4U, { } },
            { 5U, { 10 } }
        };

        const auto query = From(source).SelectMany([](const Order& order){ return order.items; });

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