#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace std;

namespace CppLinq::Tests::DefaultIfEmpty
{
    TEST(Return_default_if_sequence_is_empty, Returns_default_if_source_is_empty)
    {
        // Arrange.
        const vector<int> source;
        const int expected[]{ 7 };

        // Act.
        const auto actual = From(source).DefaultIfEmpty(7);

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Return_default_if_sequence_is_empty, Returns_sequence_if_source_is_not_empty)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5 };
        const int expected[]{ 1, 2, 3, 4, 5 };

        // Act.
        const auto actual = From(source).DefaultIfEmpty(7);

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Return_default_if_sequence_is_empty, Returns_the_same_result_on_every_call)
    {
        // Arrange.
        const vector<int> source;

        const auto query = From(source);

        // Act.
        const auto actual1 = query.DefaultIfEmpty(7);
        const auto actual2 = query.DefaultIfEmpty(7);

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }
}