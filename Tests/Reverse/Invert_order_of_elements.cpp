#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace std;

namespace CppLinq::Tests::Reverse
{
    TEST(Invert_order_of_elements, Returns_empty_sequence_if_source_is_empty)
    {
        // Arrange.
        const vector<int> source;

        // Act.
        const auto actual = From(source).Reverse();

        // Assert.
        ExpectSequenceIsEmpty(actual);
    }

    TEST(Invert_order_of_elements, Returns_expected_sequence_if_source_is_not_empty)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        const int expected[]{ 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };

        // Act.
        const auto actual = From(source).Reverse();

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Invert_order_of_elements, Returns_the_same_result_on_every_call)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.Reverse();
        const auto actual2 = query.Reverse();

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }
}