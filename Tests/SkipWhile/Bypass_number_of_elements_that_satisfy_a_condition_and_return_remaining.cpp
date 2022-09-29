#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq::Exceptions;

namespace CppLinq::Tests::SkipWhile
{
    TEST(Bypass_number_of_elements_that_satisfy_a_condition_and_return_remaining, Returns_empty_sequence_if_all_elements_satisfy_a_condition)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        // Act.
        const auto actual = From(source).SkipWhile([](const int /*value*/){ return true; });

        // Assert.
        ExpectSequenceIsEmpty(actual);
    }

    TEST(Bypass_number_of_elements_that_satisfy_a_condition_and_return_remaining, Returns_the_same_sequence_if_all_elements_do_not_satisfy_a_condition)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        const int expected[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        // Act.
        const auto actual = From(source).SkipWhile([](const int /*value*/){ return false; });

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Bypass_number_of_elements_that_satisfy_a_condition_and_return_remaining, Returns_remaining_elements_if_only_some_elements_satisfy_a_condition)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        const int expected[]{ 5, 6, 7, 8, 9, 10 };

        // Act.
        const auto actual = From(source).SkipWhile([](const int value){ return value < 5; });

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Bypass_number_of_elements_that_satisfy_a_condition_and_return_remaining, Returns_the_same_result_on_every_call)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.SkipWhile([](const int value){ return value < 5; });
        const auto actual2 = query.SkipWhile([](const int value){ return value < 5; });

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }
}