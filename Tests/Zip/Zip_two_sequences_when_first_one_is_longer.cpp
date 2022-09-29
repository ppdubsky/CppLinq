#include <string>

#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace std;

namespace CppLinq::Tests::Zip
{
    TEST(Zip_two_sequences_when_first_one_is_longer, Returns_expected_sequence)
    {
        // Arrange.
        const double source1[]{ 1.1, 2.2, 3.3, 4.4, 5.5 };
        const int source2[]{ 'a', 'b', 'c' };
        const string expected[]{ "a1", "b2", "c3" };

        // Act.
        const auto actual = From(source1).Zip(
            From(source2),
            [](const double value1, const int value2){ return string(1U, static_cast<char>(value2)).append(1U, '0' + static_cast<char>(value1)); }
        );

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Zip_two_sequences_when_first_one_is_longer, Returns_the_same_result_on_every_call)
    {
        // Arrange.
        const double source1[]{ 1.1, 2.2, 3.3, 4.4, 5.5 };
        const int source2[]{ 'a', 'b', 'c' };

        const auto query = From(source1);

        // Act.
        const auto actual1 = query.Zip(
            From(source2),
            [](const double value1, const int value2){ return string(1U, static_cast<char>(value2)).append(1U, '0' + static_cast<char>(value1)); }
        );
        const auto actual2 = query.Zip(
            From(source2),
            [](const double value1, const int value2){ return string(1U, static_cast<char>(value2)).append(1U, '0' + static_cast<char>(value1)); }
        );

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }
}