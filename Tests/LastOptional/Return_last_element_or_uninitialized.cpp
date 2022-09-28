#include <optional>
#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace std;

namespace CppLinq::Tests::LastOptional
{
    TEST(Return_last_element_or_uninitialized, Returns_uninitialized_if_source_is_empty)
    {
        // Arrange.
        const vector<int> source;
        const optional<int> expected;

        // Act.
        const auto actual = From(source).LastOptional();

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Return_last_element_or_uninitialized, Returns_last_element_if_source_is_not_empty)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5 };
        const auto expected = 5;

        // Act.
        const auto actual = From(source).LastOptional();

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Return_last_element_or_uninitialized, Returns_the_same_result_on_every_call)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5 };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.LastOptional();
        const auto actual2 = query.LastOptional();

        // Assert.
        EXPECT_EQ(actual1, actual2);
    }
}