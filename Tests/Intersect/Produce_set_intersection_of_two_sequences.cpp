#include "Assertions.hpp"
#include "CppLinq.hpp"

namespace CppLinq::Tests::Intersect
{
    TEST(Produce_set_intersection_of_two_sequences, Returns_expected_sequence)
    {
        // Arrange.
        const int source[]{ 'a', 'b', 'c', 'd', 'e' };
        const int intersect[]{ 'b', 'd', 'e', 'f', 'g' };
        const int expected[]{ 'b', 'd', 'e' };

        // Act.
        const auto actual = From(source).Intersect(From(intersect));

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Produce_set_intersection_of_two_sequences, Returns_the_same_result_on_every_call)
    {
        // Arrange.
        const int source[]{ 'a', 'b', 'c', 'd', 'e' };
        const int intersect[]{ 'b', 'd', 'e', 'f', 'g' };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.Intersect(From(intersect));
        const auto actual2 = query.Intersect(From(intersect));

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }
}