#include <cctype>

#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace std;

namespace CppLinq::Tests::Intersect
{
    TEST(Produce_set_intersection_of_two_sequences_using_comparer, Returns_expected_sequence)
    {
        // Arrange.
        const int source[]{ 'a', 'b', 'c', 'd', 'e' };
        const int intersect[]{ 'B', 'D', 'E', 'F', 'G' };
        const int expected[]{ 'b', 'd', 'e' };

        // Act.
        const auto actual = From(source).Intersect(
            From(intersect),
            [](const int value1, const int value2){ return tolower(value1) == tolower(value2); }
        );

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Produce_set_intersection_of_two_sequences_using_comparer, Returns_the_same_result_on_every_call)
    {
        // Arrange.
        const int source[]{ 'a', 'b', 'c', 'd', 'e' };
        const int intersect[]{ 'B', 'D', 'E', 'F', 'G' };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.Intersect(
            From(intersect),
            [](const int value1, const int value2){ return tolower(value1) == tolower(value2); }
        );
        const auto actual2 = query.Intersect(
            From(intersect),
            [](const int value1, const int value2){ return tolower(value1) == tolower(value2); }
        );

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }
}