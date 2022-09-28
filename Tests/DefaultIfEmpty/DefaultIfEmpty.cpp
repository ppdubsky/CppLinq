#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace std;

namespace CppLinq::Tests::DefaultIfEmpty
{
    TEST(DefaultIfEmpty, Returns_expected_sequence_if_source_is_empty)
    {
        // Arrange.
        const vector<int> source;
        const int expected[]{ 7 };

        // Act.
        const auto actual = From(source).DefaultIfEmpty(7);

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(DefaultIfEmpty, Returns_expected_sequence_if_source_is_not_empty)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5 };
        const int expected[]{ 1, 2, 3, 4, 5 };

        // Act.
        const auto actual = From(source).DefaultIfEmpty(7);

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(DefaultIfEmpty, Returns_the_same_results)
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