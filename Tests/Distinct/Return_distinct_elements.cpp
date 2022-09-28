#include "Assertions.hpp"
#include "CppLinq.hpp"

namespace CppLinq::Tests::Distinct
{
    TEST(Return_distinct_elements, Returns_expected_sequence_if_source_contains_distinct_elements)
    {
        // Arrange.
        const int source[]{ 'a', 'b', 'c', 'd', 'e' };
        const int expected[]{ 'a', 'b', 'c', 'd', 'e'  };

        // Act.
        const auto actual = From(source).Distinct();

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Return_distinct_elements, Returns_expected_sequence_if_source_contains_duplicate_elements)
    {
        // Arrange.
        const int source[]{ 'a', 'a', 'b', 'b', 'c', 'c', 'd', 'd', 'e', 'e' };
        const int expected[]{ 'a', 'b', 'c', 'd', 'e'  };

        // Act.
        const auto actual = From(source).Distinct();

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Return_distinct_elements, Returns_the_same_results)
    {
        // Arrange.
        const int source[]{ 'a', 'b', 'c', 'd', 'e' };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.Distinct();
        const auto actual2 = query.Distinct();

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }
}