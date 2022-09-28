#include <cctype>
#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace std;

namespace CppLinq::Tests::Contains
{
    TEST(Determine_whether_sequence_contains_element_using_comparer, Returns_false_if_source_is_empty)
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

    TEST(Determine_whether_sequence_contains_element_using_comparer, Returns_true_if_source_contains_an_element)
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

    TEST(Determine_whether_sequence_contains_element_using_comparer, Returns_false_if_source_does_not_contain_an_element)
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

    TEST(Determine_whether_sequence_contains_element_using_comparer, Returns_the_same_result_on_every_call)
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