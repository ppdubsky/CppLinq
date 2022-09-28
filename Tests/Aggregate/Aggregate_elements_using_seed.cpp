#include <string>
#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace std;

namespace CppLinq::Tests::Aggregate
{
    TEST(Aggregate_elements_using_seed, Returns_seed_if_source_is_empty)
    {
        // Arrange.
        const vector<int> source;
        const auto expected = "A";

        // Act.
        const auto actual = From(source).Aggregate(
            string("A"),
            [](const string& value1, const int value2){ return value1 + to_string(value2); }
        );

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Aggregate_elements_using_seed, Returns_aggregated_value_if_source_contains_one_element)
    {
        // Arrange.
        const int source[]{ 1 };
        const auto expected = "A1";

        // Act.
        const auto actual = From(source).Aggregate(
            string("A"),
            [](const string& value1, const int value2){ return value1 + to_string(value2); }
        );

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Aggregate_elements_using_seed, Returns_aggregated_value_if_source_contains_two_elements)
    {
        // Arrange.
        const int source[]{ 1, 2 };
        const auto expected = "A12";

        // Act.
        const auto actual = From(source).Aggregate(
            string("A"),
            [](const string& value1, const int value2){ return value1 + to_string(value2); }
        );

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Aggregate_elements_using_seed, Returns_aggregated_value_if_source_contains_three_elements)
    {
        // Arrange.
        const int source[]{ 1, 2, 3 };
        const auto expected = "A123";

        // Act.
        const auto actual = From(source).Aggregate(
            string("A"),
            [](const string& value1, const int value2){ return value1 + to_string(value2); }
        );

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Aggregate_elements_using_seed, Returns_the_same_result_on_every_call)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5 };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.Aggregate(
            string("A"),
            [](const string& value1, const int value2){ return value1 + to_string(value2); }
        );
        const auto actual2 = query.Aggregate(
            string("A"),
            [](const string& value1, const int value2){ return value1 + to_string(value2); }
        );

        // Assert.
        EXPECT_EQ(actual1, actual2);
    }
}