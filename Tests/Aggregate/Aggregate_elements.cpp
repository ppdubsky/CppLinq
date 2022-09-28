#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq::Exceptions;
using namespace std;

namespace CppLinq::Tests::Aggregate
{
    TEST(Aggregate_elements, Throws_if_source_is_empty)
    {
        // Arrange.
        const vector<int> source;

        const auto query = From(source);

        // Act.
        const auto action = [&query](){ query.Aggregate([](const int value1, const int value2){ return value1 + value2; }); };

        // Assert.
        EXPECT_THROW(action(), EmptyContainerException);
    }

    TEST(Aggregate_elements, Returns_first_element_if_source_contains_one_element)
    {
        // Arrange.
        const int source[]{ 1 };
        const auto expected = 1;

        // Act.
        const auto actual = From(source).Aggregate([](const int value1, const int value2){ return value1 + value2; });

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Aggregate_elements, Returns_aggregated_value_if_source_contains_two_elements)
    {
        // Arrange.
        const int source[]{ 1, 2 };
        const auto expected = 3;

        // Act.
        const auto actual = From(source).Aggregate([](const int value1, const int value2){ return value1 + value2; });

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Aggregate_elements, Returns_aggregated_value_if_source_contains_three_elements)
    {
        // Arrange.
        const int source[]{ 1, 2, 3 };
        const auto expected = 6;

        // Act.
        const auto actual = From(source).Aggregate([](const int value1, const int value2){ return value1 + value2; });

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Aggregate_elements, Returns_the_same_result_on_every_call)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5 };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.Aggregate([](const int value1, const int value2){ return value1 + value2; });
        const auto actual2 = query.Aggregate([](const int value1, const int value2){ return value1 + value2; });

        // Assert.
        EXPECT_EQ(actual1, actual2);
    }
}