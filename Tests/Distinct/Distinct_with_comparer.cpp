#include <cctype>

#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace std;

namespace CppLinq::Tests::Distinct
{
    TEST(Distinct_with_comparer, Returns_expected_sequence_if_source_contains_distinct_elements)
    {
        // Arrange.
        const int source[]{ 'a', 'b', 'c', 'd', 'e' };
        const int expected[]{ 'a', 'b', 'c', 'd', 'e'  };

        // Act.
        const auto actual = From(source).Distinct([](const int value1, const int value2){ return tolower(value1) == tolower(value2); });

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Distinct_with_comparer, Returns_expected_sequence_if_source_contains_duplicate_elements)
    {
        // Arrange.
        const int source[]{ 'a', 'A', 'b', 'B', 'c', 'C', 'd', 'D', 'e', 'E' };
        const int expected[]{ 'a', 'b', 'c', 'd', 'e'  };

        // Act.
        const auto actual = From(source).Distinct([](const int value1, const int value2){ return tolower(value1) == tolower(value2); });

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Distinct_with_comparer, Returns_the_same_results)
    {
        // Arrange.
        const int source[]{ 'a', 'A', 'b', 'B', 'c', 'C', 'd', 'D', 'e', 'E' };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.Distinct([](const int value1, const int value2){ return tolower(value1) == tolower(value2); });
        const auto actual2 = query.Distinct([](const int value1, const int value2){ return tolower(value1) == tolower(value2); });

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }
}