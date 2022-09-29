#include "Assertions.hpp"
#include "CppLinq.hpp"

namespace CppLinq::Tests::StaticCast
{
    TEST(Cast_elements, Returns_expected_sequence)
    {
        // Arrange.
        const double source[]{ 1.1, 2.2, 3.3, 4.4, 5.5 };
        const int expected[]{ 1, 2, 3, 4, 5 };

        // Act.
        const auto actual = From(source).StaticCast<int>();

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Cast_elements, Returns_the_same_result_on_every_call)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.StaticCast<int>();
        const auto actual2 = query.StaticCast<int>();

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }
}