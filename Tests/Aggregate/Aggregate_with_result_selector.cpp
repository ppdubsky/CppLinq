#include <string>
#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace std;

namespace CppLinq::Tests::Aggregate
{
    TEST(Aggregate_with_result_selector, Returns_aggregated_value_if_source_is_empty)
    {
        // Arrange.
        const vector<int> source;
        const auto expected = "AB";

        // Act.
        const auto actual = From(source).Aggregate(
            string("A"),
            [](const string& value1, const int value2){ return value1 + to_string(value2); },
            [](const string& value1){ return value1 + "B"; }
        );

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Aggregate_with_result_selector, Returns_aggregated_value_if_source_contains_one_element)
    {
        // Arrange.
        const int source[]{ 1 };
        const auto expected = "A1B";

        // Act.
        const auto actual = From(source).Aggregate(
            string("A"),
            [](const string& value1, const int value2){ return value1 + to_string(value2); },
            [](const string& value1){ return value1 + "B"; }
        );

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Aggregate_with_result_selector, Returns_aggregated_value_if_source_contains_two_elements)
    {
        // Arrange.
        const int source[]{ 1, 2 };
        const auto expected = "A12B";

        // Act.
        const auto actual = From(source).Aggregate(
            string("A"),
            [](const string& value1, const int value2){ return value1 + to_string(value2); },
            [](const string& value1){ return value1 + "B"; }
        );

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Aggregate_with_result_selector, Returns_aggregated_value_if_source_contains_three_elements)
    {
        // Arrange.
        const int source[]{ 1, 2, 3 };
        const auto expected = "A123B";

        // Act.
        const auto actual = From(source).Aggregate(
            string("A"),
            [](const string& value1, const int value2){ return value1 + to_string(value2); },
            [](const string& value1){ return value1 + "B"; }
        );

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Aggregate_with_result_selector, Returns_the_same_results)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5 };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.Aggregate(
            string("A"),
            [](const string& value1, const int value2){ return value1 + to_string(value2); },
            [](const string& value1){ return value1 + "B"; }
        );
        const auto actual2 = query.Aggregate(
            string("A"),
            [](const string& value1, const int value2){ return value1 + to_string(value2); },
            [](const string& value1){ return value1 + "B"; }
        );

        // Assert.
        EXPECT_EQ(actual1, actual2);
    }
}