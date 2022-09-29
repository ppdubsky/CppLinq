#include "Assertions.hpp"
#include "CppLinq.hpp"

namespace CppLinq::Tests::Skip
{
    TEST(Bypass_number_of_elements_and_return_remaining, Returns_the_same_sequence_if_count_is_zero)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        const int expected[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        // Act.
        const auto actual = From(source).Skip(0U);

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Bypass_number_of_elements_and_return_remaining, Returns_remaining_elements_if_count_is_less_than_source)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        const int expected[]{ 6, 7, 8, 9, 10 };

        // Act.
        const auto actual = From(source).Skip(5U);

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Bypass_number_of_elements_and_return_remaining, Returns_empty_sequence_if_count_is_equal_to_source)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        // Act.
        const auto actual = From(source).Skip(10U);

        // Assert.
        ExpectSequenceIsEmpty(actual);
    }

    TEST(Bypass_number_of_elements_and_return_remaining, Returns_empty_sequence_if_count_is_greater_than_source)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        // Act.
        const auto actual = From(source).Skip(15U);

        // Assert.
        ExpectSequenceIsEmpty(actual);
    }

    TEST(Bypass_number_of_elements_and_return_remaining, Returns_the_same_result_on_every_call)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.Skip(5U);
        const auto actual2 = query.Skip(5U);

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }
}