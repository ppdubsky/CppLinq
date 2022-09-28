#include <optional>
#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace std;

namespace CppLinq::Tests::ElementAtOptional
{
    TEST(Return_element_at_index_or_uninitialized, Returns_uninitialized_if_source_is_empty)
    {
        // Arrange.
        const vector<int> source;
        const optional<int> expected;

        // Act.
        const auto actual = From(source).ElementAtOptional(0U);

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Return_element_at_index_or_uninitialized, Returns_element_if_index_is_valid)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5 };
        const auto expected = 4;

        // Act.
        const auto actual = From(source).ElementAtOptional(3U);

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Return_element_at_index_or_uninitialized, Returns_uninitialized_if_index_is_valid)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5 };
        const optional<int> expected;

        // Act.
        const auto actual = From(source).ElementAtOptional(10U);

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Return_element_at_index_or_uninitialized, Returns_the_same_result_on_every_call)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5 };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.ElementAtOptional(3U);
        const auto actual2 = query.ElementAtOptional(3U);

        // Assert.
        EXPECT_EQ(actual1, actual2);
    }
}