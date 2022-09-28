#include "Assertions.hpp"
#include "CppLinq.hpp"

namespace CppLinq::Tests::OrderBy
{
    TEST(Sort_elements, Returns_expected_sequence)
    {
        // Arrange.
        const int source[]{ 1, 3, 5, 7, 9, 10, 8, 6, 4, 2 };
        const int expected[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        // Act.
        const auto actual = From(source).OrderBy();

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Sort_elements, Returns_the_same_result_on_every_call)
    {
        // Arrange.
        const int source[]{ 1, 3, 5, 7, 9, 10, 8, 6, 4, 2 };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.OrderBy();
        const auto actual2 = query.OrderBy();

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }
}