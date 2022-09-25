#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace std;

namespace CppLinq::Tests::Chunk
{
    TEST(Chunk_size_is_greater, Returns_expected_sequence_if_source_is_empty)
    {
        // Arrange.
        const vector<int> source;
        const vector<vector<int>> expected;

        // Act.
        const auto actual = From(source).Chunk(3U);

        // Assert.
        ExpectSequenceIsEmpty(actual);
    }

    TEST(Chunk_size_is_greater, Returns_expected_sequence_if_source_contains_one_element)
    {
        // Arrange.
        const int source[]{ 1 };
        const vector<int> expected[]
        {
            { 1 }
        };

        // Act.
        const auto actual = From(source).Chunk(3U);

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Chunk_size_is_greater, Returns_expected_sequence_if_source_contains_two_elements)
    {
        // Arrange.
        const int source[]{ 1, 2 };
        const vector<int> expected[]
        {
            { 1, 2 }
        };

        // Act.
        const auto actual = From(source).Chunk(3U);

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Chunk_size_is_greater, Returns_the_same_results)
    {
        // Arrange.
        const int source[]{ 1 };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.Chunk(3U);
        const auto actual2 = query.Chunk(3U);

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }
}