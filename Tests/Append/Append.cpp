#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace std;

namespace CppLinq::Tests::Append
{
    TEST(Append, Returns_expected_sequence_if_source_is_empty)
    {
        // Arrange.
        const vector<int> source;
        const int expected[]{ 7 };

        // Act.
        const auto actual = From(source).Append(7);

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Append, Returns_expected_sequence_if_source_contains_one_element)
    {
        // Arrange.
        const int source[]{ 1 };
        const int expected[]{ 1, 7 };

        // Act.
        const auto actual = From(source).Append(7);

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Append, Returns_expected_sequence_if_source_contains_two_elements)
    {
        // Arrange.
        const int source[]{ 1, 2 };
        const int expected[]{ 1, 2, 7 };

        // Act.
        const auto actual = From(source).Append(7);

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Append, Returns_expected_sequence_if_source_contains_three_elements)
    {
        // Arrange.
        const int source[]{ 1, 2, 3 };
        const int expected[]{ 1, 2, 3, 7 };

        // Act.
        const auto actual = From(source).Append(7);

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Append, Returns_the_same_results)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5 };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.Append(7);
        const auto actual2 = query.Append(7);

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }
}