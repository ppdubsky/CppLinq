#include "Assertions.hpp"
#include "CppLinq.hpp"

namespace CppLinq::Tests::TakeWhile
{
    TEST(Return_number_of_elements_from_start_that_satisfy_a_condition, Returns_the_same_sequence_if_all_elements_satisfy_a_condition)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        const int expected[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        // Act.
        const auto actual = From(source).TakeWhile([](const int /*value*/){ return true; });

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Return_number_of_elements_from_start_that_satisfy_a_condition, Returns_empty_sequence_if_all_elements_do_not_satisfy_a_condition)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        // Act.
        const auto actual = From(source).TakeWhile([](const int /*value*/){ return false; });

        // Assert.
        ExpectSequenceIsEmpty(actual);
    }

    TEST(Return_number_of_elements_from_start_that_satisfy_a_condition, Returns_first_elements_if_only_some_elements_satisfy_a_condition)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        const int expected[]{ 1, 2, 3, 4 };

        // Act.
        const auto actual = From(source).TakeWhile([](const int value){ return value < 5; });

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Return_number_of_elements_from_start_that_satisfy_a_condition, Returns_the_same_result_on_every_call)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.TakeWhile([](const int value){ return value < 5; });
        const auto actual2 = query.TakeWhile([](const int value){ return value < 5; });

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }
}