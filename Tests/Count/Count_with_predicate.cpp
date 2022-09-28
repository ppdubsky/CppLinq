#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq::Exceptions;
using namespace std;

namespace CppLinq::Tests::Count
{
    TEST(Count_with_predicate, Returns_count_if_source_is_empty)
    {
        // Arrange.
        const vector<int> source;
        const auto expected = 0U;

        // Act.
        const auto actual = From(source).Count([](const int value){ return value % 2 == 0; });

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Count_with_predicate, Returns_count_if_source_contains_valid_element)
    {
        // Arrange.
        const int source[]{ 2, 4, 6, 8, 10 };
        const auto expected = 5U;

        // Act.
        const auto actual = From(source).Count([](const int value){ return value % 2 == 0; });

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Count_with_predicate, Returns_count_if_source_does_not_contain_valid_element)
    {
        // Arrange.
        const int source[]{ 1, 3, 5, 7, 9 };
        const auto expected = 0U;

        // Act.
        const auto actual = From(source).Count([](const int value){ return value % 2 == 0; });

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Count_with_predicate, Returns_count_if_source_contains_valid_and_invalid_elements)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        const auto expected = 5U;

        // Act.
        const auto actual = From(source).Count([](const int value){ return value % 2 == 0; });

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Count_with_predicate, Returns_the_same_results)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5 };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.Count([](const int value){ return value % 2 == 0; });
        const auto actual2 = query.Count([](const int value){ return value % 2 == 0; });

        // Assert.
        EXPECT_EQ(actual1, actual2);
    }
}