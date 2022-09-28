#include "Assertions.hpp"
#include "CppLinq.hpp"
#include "DistinctBy/Stubs/Customer.hpp"

using namespace CppLinq::Tests::DistinctBy::Stubs;

namespace CppLinq::Tests::DistinctBy
{
    TEST(Return_distinct_elements_by_key, Returns_expected_sequence_if_source_contains_distinct_elements)
    {
        // Arrange.
        const Customer source[]
        {
            { 1U, "James" },
            { 2U, "Robert" },
            { 3U, "John" },
            { 4U, "Michael" },
            { 5U, "David" },
            { 6U, "William" }
        };
        const Customer expected[]
        {
            { 1U, "James" },
            { 2U, "Robert" },
            { 3U, "John" },
            { 4U, "Michael" },
            { 5U, "David" },
            { 6U, "William" }
        };

        // Act.
        const auto actual = From(source).DistinctBy([](const Customer& customer){ return customer.name; });

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Return_distinct_elements_by_key, Returns_expected_sequence_if_source_contains_duplicate_elements)
    {
        // Arrange.
        const Customer source[]
        {
            { 1U, "James" },
            { 2U, "Robert" },
            { 3U, "Robert" },
            { 4U, "John" },
            { 5U, "John" },
            { 6U, "Michael" },
            { 7U, "David" },
            { 8U, "David" },
            { 9U, "William" }
        };
        const Customer expected[]
        {
            { 1U, "James" },
            { 2U, "Robert" },
            { 4U, "John" },
            { 6U, "Michael" },
            { 7U, "David" },
            { 9U, "William" }
        };

        // Act.
        const auto actual = From(source).DistinctBy([](const Customer& customer){ return customer.name; });

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Return_distinct_elements_by_key, Returns_the_same_result_on_every_call)
    {
        // Arrange.
        const Customer source[]
        {
            { 1U, "James" },
            { 2U, "Robert" },
            { 3U, "John" },
            { 4U, "Michael" },
            { 5U, "David" },
            { 6U, "William" }
        };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.DistinctBy([](const Customer& customer){ return customer.name; });
        const auto actual2 = query.DistinctBy([](const Customer& customer){ return customer.name; });

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }
}