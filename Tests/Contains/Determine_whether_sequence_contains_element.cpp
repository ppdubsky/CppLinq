#include <cctype>
#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace std;

namespace CppLinq::Tests::Contains
{
    TEST(Determine_whether_sequence_contains_element, Returns_false_if_source_is_empty)
    {
        // Arrange.
        const vector<int> source;

        // Act.
        const auto actual = From(source).Contains('c');

        // Assert.
        EXPECT_FALSE(actual);
    }

    TEST(Determine_whether_sequence_contains_element, Returns_true_if_source_contains_an_element)
    {
        // Arrange.
        const int source[]{ 'a', 'b', 'c', 'd', 'e' };

        // Act.
        const auto actual = From(source).Contains('c');

        // Assert.
        EXPECT_TRUE(actual);
    }

    TEST(Determine_whether_sequence_contains_element, Returns_false_if_source_does_not_contain_an_element)
    {
        // Arrange.
        const int source[]{ 'a', 'b', 'c', 'd', 'e' };

        // Act.
        const auto actual = From(source).Contains('f');

        // Assert.
        EXPECT_FALSE(actual);
    }

    TEST(Determine_whether_sequence_contains_element, Returns_the_same_result_on_every_call)
    {
        // Arrange.
        const int source[]{ 'a', 'b', 'c', 'd', 'e' };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.Contains('c');
        const auto actual2 = query.Contains('c');

        // Assert.
        EXPECT_EQ(actual1, actual2);
    }
}