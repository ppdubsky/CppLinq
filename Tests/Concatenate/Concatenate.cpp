#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace std;

namespace CppLinq::Tests::Concatenate
{
    TEST(Concatenate, Returns_expected_sequence_if_both_sources_are_empty)
    {
        // Arrange.
        const vector<int> source1;
        const vector<int> source2;

        // Act.
        const auto actual = From(source1).Concatenate(From(source2));

        // Assert.
        ExpectSequenceIsEmpty(actual);
    }

    TEST(Concatenate, Returns_expected_sequence_if_both_sources_are_not_empty)
    {
        // Arrange.
        const int source1[]{ 1, 2, 3, 4, 5 };
        const int source2[]{ 6, 7, 8, 9, 10 };
        const int expected[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        // Act.
        const auto actual = From(source1).Concatenate(From(source2));

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Concatenate, Returns_expected_sequence_if_only_first_source_is_empty)
    {
        // Arrange.
        const vector<int> source1;
        const int source2[]{ 6, 7, 8, 9, 10 };
        const int expected[]{ 6, 7, 8, 9, 10 };

        // Act.
        const auto actual = From(source1).Concatenate(From(source2));

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Concatenate, Returns_expected_sequence_if_only_second_source_is_empty)
    {
        // Arrange.
        const int source1[]{ 1, 2, 3, 4, 5 };
        const vector<int> source2;
        const int expected[]{ 1, 2, 3, 4, 5 };

        // Act.
        const auto actual = From(source1).Concatenate(From(source2));

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Concatenate, Returns_the_same_results)
    {
        // Arrange.
        const int source1[]{ 1, 2, 3, 4, 5 };
        const int source2[]{ 6, 7, 8, 9, 10 };

        const auto query = From(source1);

        // Act.
        const auto actual1 = query.Concatenate(From(source2));
        const auto actual2 = query.Concatenate(From(source2));

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }
}