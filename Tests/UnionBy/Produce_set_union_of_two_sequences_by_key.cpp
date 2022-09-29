#include "Assertions.hpp"
#include "CppLinq.hpp"
#include "UnionBy/Stubs/Customer.hpp"

using namespace CppLinq::Tests::UnionBy::Stubs;

namespace CppLinq::Tests::UnionBy
{
    TEST(Produce_set_union_of_two_sequences_by_key, Returns_expected_sequence)
    {
        // Arrange.
        const Customer source1[]
        {
            { 1U, "James" },
            { 2U, "Robert" },
            { 3U, "John" },
            { 4U, "John" },
            { 5U, "Michael" },
            { 6U, "David" },
            { 7U, "William" }
        };
        const Customer source2[]
        {
            { 8U, "Robert" },
            { 9U, "Richard" },
            { 10U, "Joseph" },
            { 11U, "James" },
            { 12U, "James" },
            { 13U, "Thomas" },
            { 14U, "Michael" }
        };
        const Customer expected[]
        {
            { 1U, "James" },
            { 2U, "Robert" },
            { 3U, "John" },
            { 5U, "Michael" },
            { 6U, "David" },
            { 7U, "William" },
            { 9U, "Richard" },
            { 10U, "Joseph" },
            { 13U, "Thomas" }
        };

        // Act.
        const auto actual = From(source1).UnionBy(
            From(source2),
            [](const Customer& customer){ return customer.name; }
        );

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Produce_set_union_of_two_sequences_by_key, Returns_the_same_result_on_every_call)
    {
        // Arrange.
        const Customer source1[]
        {
            { 1U, "James" },
            { 2U, "Robert" },
            { 3U, "John" },
            { 4U, "John" },
            { 5U, "Michael" },
            { 6U, "David" },
            { 7U, "William" }
        };
        const Customer source2[]
        {
            { 8U, "Robert" },
            { 9U, "Richard" },
            { 10U, "Joseph" },
            { 11U, "James" },
            { 12U, "James" },
            { 13U, "Thomas" },
            { 14U, "Michael" }
        };

        const auto query = From(source1);

        // Act.
        const auto actual1 = query.UnionBy(
            From(source2),
            [](const Customer& customer){ return customer.name; }
        );
        const auto actual2 = query.UnionBy(
            From(source2),
            [](const Customer& customer){ return customer.name; }
        );

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }
}