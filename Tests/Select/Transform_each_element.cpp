#include <string>
#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace std;

namespace CppLinq::Tests::Select
{
    TEST(Transform_each_element, Returns_empty_sequence_if_source_is_empty)
    {
        // Arrange.
        const vector<int> source;

        // Act.
        const auto actual = From(source).Select([](const int value){ return to_string(value); });

        // Assert.
        ExpectSequenceIsEmpty(actual);
    }

    TEST(Transform_each_element, Returns_expected_sequence_if_source_is_not_empty)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        const string expected[]{ "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };

        // Act.
        const auto actual = From(source).Select([](const int value){ return to_string(value); });

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Transform_each_element, Returns_the_same_result_on_every_call)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.Select([](const int value){ return to_string(value); });
        const auto actual2 = query.Select([](const int value){ return to_string(value); });

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }
}