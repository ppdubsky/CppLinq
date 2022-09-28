#include <optional>
#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace std;

namespace CppLinq::Tests::LastOptional
{
    TEST(Return_last_element_that_satisfies_a_condition_or_uninitialized, Returns_uninitialized_if_source_is_empty)
    {
        // Arrange.
        const vector<int> source;
        const optional<int> expected;

        // Act.
        const auto actual = From(source).LastOptional([](const int value){ return value % 2 == 0; });

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Return_last_element_that_satisfies_a_condition_or_uninitialized, Returns_last_element_if_source_contains_only_elements_that_satisfy_a_condition)
    {
        // Arrange.
        const int source[]{ 2, 4, 6, 8, 10 };
        const auto expected = 10;

        // Act.
        const auto actual = From(source).LastOptional([](const int value){ return value % 2 == 0; });

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Return_last_element_that_satisfies_a_condition_or_uninitialized, Returns_uninitialized_if_source_contains_only_elements_that_do_not_satisfy_a_condition)
    {
        // Arrange.
        const int source[]{ 1, 3, 5, 7, 9 };
        const optional<int> expected;

        // Act.
        const auto actual = From(source).LastOptional([](const int value){ return value % 2 == 0; });

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Return_last_element_that_satisfies_a_condition_or_uninitialized, Returns_last_element_if_source_contains_both_elements_that_satisfy_a_condition_and_the_ones_that_do_not)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        const auto expected = 10;

        // Act.
        const auto actual = From(source).LastOptional([](const int value){ return value % 2 == 0; });

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Return_last_element_that_satisfies_a_condition_or_uninitialized, Returns_the_same_result_on_every_call)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5 };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.LastOptional([](const int value){ return value % 2 == 0; });
        const auto actual2 = query.LastOptional([](const int value){ return value % 2 == 0; });

        // Assert.
        EXPECT_EQ(actual1, actual2);
    }
}