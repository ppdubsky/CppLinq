#include "Assertions.hpp"
#include "CppLinq.hpp"

namespace CppLinq::Tests::Except
{
    TEST(Produce_set_difference_of_two_sequences, Returns_expected_sequence)
    {
        // Arrange.
        const int source[]{ 'a', 'b', 'c', 'd', 'e' };
        const int except[]{ 'b', 'd', 'e', 'f', 'g' };
        const int expected[]{ 'a', 'c' };

        // Act.
        const auto actual = From(source).Except(From(except));

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Produce_set_difference_of_two_sequences, Returns_the_same_result_on_every_call)
    {
        // Arrange.
        const int source[]{ 'a', 'b', 'c', 'd', 'e' };
        const int except[]{ 'b', 'd', 'e', 'f', 'g' };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.Except(From(except));
        const auto actual2 = query.Except(From(except));

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }
}