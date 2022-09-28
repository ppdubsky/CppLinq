#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace std;

namespace CppLinq::Tests::LastOrDefault
{
    TEST(Return_last_element_or_default, Returns_default_if_source_is_empty)
    {
        // Arrange.
        const vector<int> source;
        const int expected = 7;

        // Act.
        const auto actual = From(source).LastOrDefault(7);

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Return_last_element_or_default, Returns_last_element_if_source_is_not_empty)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5 };
        const auto expected = 5;

        // Act.
        const auto actual = From(source).LastOrDefault(7);

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Return_last_element_or_default, Returns_the_same_result_on_every_call)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5 };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.LastOrDefault(7);
        const auto actual2 = query.LastOrDefault(7);

        // Assert.
        EXPECT_EQ(actual1, actual2);
    }
}