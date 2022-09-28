#include "Assertions.hpp"
#include "CppLinq.hpp"

namespace CppLinq::Tests::Except
{
    TEST(Produce_set_difference_of_two_sequences_using_comparer, Returns_expected_sequence)
    {
        // Arrange.
        const int source[]{ 'a', 'b', 'c', 'd', 'e' };
        const int except[]{ 'B', 'D', 'E', 'F', 'G' };
        const int expected[]{ 'a', 'c' };

        // Act.
        const auto actual = From(source).Except(
            From(except),
            [](const int value1, const int value2){ return tolower(value1) == tolower(value2); }
        );

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Produce_set_difference_of_two_sequences_using_comparer, Returns_the_same_result_on_every_call)
    {
        // Arrange.
        const int source[]{ 'a', 'b', 'c', 'd', 'e' };
        const int except[]{ 'B', 'D', 'E', 'F', 'G' };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.Except(
            From(except),
            [](const int value1, const int value2){ return tolower(value1) == tolower(value2); }
        );
        const auto actual2 = query.Except(
            From(except),
            [](const int value1, const int value2){ return tolower(value1) == tolower(value2); }
        );

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }
}