#include <optional>
#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq::Exceptions;
using namespace std;

namespace CppLinq::Tests::SingleOptional
{
    TEST(Return_single_element_that_satisfies_a_condition_or_uninitialized, Returns_uninitialized_if_source_is_empty)
    {
        // Arrange.
        const vector<int> source;
        const optional<int> expected;

        // Act.
        const auto actual = From(source).SingleOptional([](const int value){ return value % 2 == 0; });

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Return_single_element_that_satisfies_a_condition_or_uninitialized, Returns_uninitialized_if_source_contains_one_element_that_does_not_satisfy_a_condition)
    {
        // Arrange.
        const int source[]{ 1 };
        const optional<int> expected;

        // Act.
        const auto actual = From(source).SingleOptional([](const int value){ return value % 2 == 0; });

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Return_single_element_that_satisfies_a_condition_or_uninitialized, Returns_single_element_if_source_contains_one_element_that_satisfies_a_condition)
    {
        // Arrange.
        const int source[]{ 1, 2, 3 };
        const auto expected = 2;

        // Act.
        const auto actual = From(source).SingleOptional([](const int value){ return value % 2 == 0; });

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Return_single_element_that_satisfies_a_condition_or_uninitialized, Throws_if_source_contains_two_elements_that_satisfy_a_condition)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5 };

        const auto query = From(source);

        // Act.
        const auto action = [&query](){ query.SingleOptional([](const int value){ return value % 2 == 0; }); };

        // Assert.
        EXPECT_THROW(action(), MoreThanOneElementException);
    }

    TEST(Return_single_element_that_satisfies_a_condition_or_uninitialized, Returns_the_same_result_on_every_call)
    {
        // Arrange.
        const int source[]{ 1, 2, 3 };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.SingleOptional([](const int value){ return value % 2 == 0; });
        const auto actual2 = query.SingleOptional([](const int value){ return value % 2 == 0; });

        // Assert.
        EXPECT_EQ(actual1, actual2);
    }
}