#include "Assertions.hpp"
#include "CppLinq.hpp"

namespace CppLinq::Tests::SkipLast
{
    TEST(Omit_number_of_elements_from_the_end, Returns_the_same_sequence_if_count_is_zero)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        const int expected[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        // Act.
        const auto actual = From(source).SkipLast(0U);

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Omit_number_of_elements_from_the_end, Returns_remaining_elements_if_count_is_less_than_source)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        const int expected[]{ 1, 2, 3, 4, 5 };

        // Act.
        const auto actual = From(source).SkipLast(5U);

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Omit_number_of_elements_from_the_end, Returns_empty_sequence_if_count_is_equal_to_source)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        // Act.
        const auto actual = From(source).SkipLast(10U);

        // Assert.
        ExpectSequenceIsEmpty(actual);
    }

    TEST(Omit_number_of_elements_from_the_end, Returns_empty_sequence_if_count_is_greater_than_source)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        // Act.
        const auto actual = From(source).SkipLast(15U);

        // Assert.
        ExpectSequenceIsEmpty(actual);
    }

    TEST(Omit_number_of_elements_from_the_end, Returns_the_same_result_on_every_call)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.SkipLast(5U);
        const auto actual2 = query.SkipLast(5U);

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }
}