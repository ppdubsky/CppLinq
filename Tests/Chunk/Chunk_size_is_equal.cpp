#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace std;

namespace CppLinq::Tests::Chunk
{
    TEST(Chunk_size_is_equal, Returns_expected_sequence_if_source_contains_three_elements)
    {
        // Arrange.
        const int source[]{ 1, 2, 3 };
        const vector<int> expected[]
        {
            { 1, 2, 3 }
        };

        // Act.
        const auto actual = From(source).Chunk(3U);

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Chunk_size_is_equal, Returns_the_same_results)
    {
        // Arrange.
        const int source[]{ 1, 2, 3 };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.Chunk(3U);
        const auto actual2 = query.Chunk(3U);

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }
}