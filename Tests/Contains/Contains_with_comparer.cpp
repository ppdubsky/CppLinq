#include <cctype>
#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace std;

namespace CppLinq::Tests::Contains
{
    TEST(Contains_with_comparer, Returns_false_if_source_is_empty)
    {
        // Arrange.
        const vector<int> source;

        // Act.
        const auto actual = From(source).Contains(
            'C',
            [](const int object1, const int object2){ return tolower(object1) == tolower(object2); }
        );

        // Assert.
        EXPECT_FALSE(actual);
    }

    TEST(Contains_with_comparer, Returns_true_if_source_contains_valid_element)
    {
        // Arrange.
        const int source[]{ 'a', 'b', 'c', 'd', 'e' };

        // Act.
        const auto actual = From(source).Contains(
            'C',
            [](const int object1, const int object2){ return tolower(object1) == tolower(object2); }
        );

        // Assert.
        EXPECT_TRUE(actual);
    }

    TEST(Contains_with_comparer, Returns_false_if_source_does_not_contain_valid_element)
    {
        // Arrange.
        const int source[]{ 'a', 'b', 'c', 'd', 'e' };

        // Act.
        const auto actual = From(source).Contains(
            'F',
            [](const int object1, const int object2){ return tolower(object1) == tolower(object2); }
        );

        // Assert.
        EXPECT_FALSE(actual);
    }

    TEST(Contains_with_comparer, Returns_the_same_results)
    {
        // Arrange.
        const int source[]{ 'a', 'b', 'c', 'd', 'e' };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.Contains(
            'C',
            [](const int object1, const int object2){ return tolower(object1) == tolower(object2); }
        );
        const auto actual2 = query.Contains(
            'C',
            [](const int object1, const int object2){ return tolower(object1) == tolower(object2); }
        );

        // Assert.
        EXPECT_EQ(actual1, actual2);
    }
}