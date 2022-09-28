#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace std;

namespace CppLinq::Tests::ElementAtOrDefault
{
    TEST(Return_element_at_index_or_default, Returns_default_if_source_is_empty)
    {
        // Arrange.
        const vector<int> source;
        const int expected = 7;

        // Act.
        const auto actual = From(source).ElementAtOrDefault(0U, 7);

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Return_element_at_index_or_default, Returns_element_if_index_is_valid)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5 };
        const auto expected = 4;

        // Act.
        const auto actual = From(source).ElementAtOrDefault(3U, 7);

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Return_element_at_index_or_default, Returns_default_if_index_is_valid)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5 };
        const int expected = 7;

        // Act.
        const auto actual = From(source).ElementAtOrDefault(10U, 7);

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Return_element_at_index_or_default, Returns_the_same_result_on_every_call)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5 };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.ElementAtOrDefault(3U, 7);
        const auto actual2 = query.ElementAtOrDefault(3U, 7);

        // Assert.
        EXPECT_EQ(actual1, actual2);
    }
}