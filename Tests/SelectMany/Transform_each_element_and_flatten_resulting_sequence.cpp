#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"
#include "SelectMany/Stubs/Order.hpp"

using namespace CppLinq::Tests::SelectMany::Stubs;
using namespace std;

namespace CppLinq::Tests::SelectMany
{
    TEST(Transform_each_element_and_flatten_resulting_sequence, Returns_empty_sequence_if_source_is_empty)
    {
        // Arrange.
        const vector<Order> source;

        // Act.
        const auto actual = From(source).SelectMany([](const Order& order){ return order.items; });

        // Assert.
        ExpectSequenceIsEmpty(actual);
    }

    TEST(Transform_each_element_and_flatten_resulting_sequence, Returns_expected_sequence_if_source_is_not_empty)
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

    TEST(Transform_each_element_and_flatten_resulting_sequence, Returns_the_same_result_on_every_call)
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
}