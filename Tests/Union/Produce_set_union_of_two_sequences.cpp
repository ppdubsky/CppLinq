#include "Assertions.hpp"
#include "CppLinq.hpp"

namespace CppLinq::Tests::Union
{
    TEST(Produce_set_union_of_two_sequences, Returns_expected_sequence)
    {
        // Arrange.
        const int source1[]{ 'c', 'C', 'd', 'a', 'b', 'b', 'c', 'D', 'h', 'B' };
        const int source2[]{ 'i', 'A', 'a', 'g', 'i', 'b', 'c', 'd', 'd', 'e', 'f' };
        const int expected[]{ 'c', 'C', 'd', 'a', 'b', 'D', 'h', 'B', 'i', 'A', 'g', 'e', 'f' };

        // Act.
        const auto actual = From(source1).Union(From(source2));

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Produce_set_union_of_two_sequences, Returns_the_same_result_on_every_call)
    {
        // Arrange.
        const int source1[]{ 'c', 'C', 'd', 'a', 'b', 'b', 'c', 'D', 'h', 'B' };
        const int source2[]{ 'i', 'A', 'a', 'g', 'i', 'b', 'c', 'd', 'd', 'e', 'f' };

        const auto query = From(source1);

        // Act.
        const auto actual1 = query.Union(From(source2));
        const auto actual2 = query.Union(From(source2));

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }
}