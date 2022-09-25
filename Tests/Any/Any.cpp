#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq::Exceptions;
using namespace std;

namespace CppLinq::Tests::Any
{
    TEST(Any, Returns_false_if_source_is_empty)
    {
        // Arrange.
        const vector<int> source;

        // Act.
        const auto actual = From(source).Any([](const int value){ return value % 2 == 0; });

        // Assert.
        EXPECT_FALSE(actual);
    }

    TEST(Any, Returns_true_if_source_contains_only_valid_elements)
    {
        // Arrange.
        const int source[]{ 2, 4, 6, 8, 10 };

        // Act.
        const auto actual = From(source).Any([](const int value){ return value % 2 == 0; });

        // Assert.
        EXPECT_TRUE(actual);
    }

    TEST(Any, Returns_false_if_source_contains_only_invalid_elements)
    {
        // Arrange.
        const int source[]{ 1, 3, 5, 7, 9 };

        // Act.
        const auto actual = From(source).Any([](const int value){ return value % 2 == 0; });

        // Assert.
        EXPECT_FALSE(actual);
    }

    TEST(Any, Returns_true_if_source_contains_valid_and_invalid_elements)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        // Act.
        const auto actual = From(source).Any([](const int value){ return value % 2 == 0; });

        // Assert.
        EXPECT_TRUE(actual);
    }

    TEST(Any, Returns_the_same_results)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.Any([](const int value){ return value % 2 == 0; });
        const auto actual2 = query.Any([](const int value){ return value % 2 == 0; });

        // Assert.
        EXPECT_EQ(actual1, actual2);
    }
}