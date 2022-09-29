#include "Assertions.hpp"
#include "CppLinq.hpp"
#include "SelectMany/Stubs/Order.hpp"

using namespace CppLinq::Exceptions;
using namespace CppLinq::Tests::SelectMany::Stubs;

namespace CppLinq::Tests::SelectMany
{
    TEST(Enumerator_is_inaccessible_after_it_is_finished, Throws_on_move_next)
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
        const auto action = [&enumerator](){ enumerator.MoveNext(); };

        // Assert.
        EXPECT_THROW(action(), FinishedEnumeratorException);
    }

    TEST(Enumerator_is_inaccessible_after_it_is_finished, Throws_on_get_current)
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
        const auto action = [&enumerator](){ enumerator.GetCurrent(); };

        // Assert.
        EXPECT_THROW(action(), FinishedEnumeratorException);
    }
}