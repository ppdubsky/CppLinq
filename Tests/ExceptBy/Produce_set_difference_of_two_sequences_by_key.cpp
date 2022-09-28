#include <string>

#include "Assertions.hpp"
#include "CppLinq.hpp"
#include "ExceptBy/Stubs/Customer.hpp"

using namespace CppLinq::Tests::ExceptBy::Stubs;
using namespace std;

namespace CppLinq::Tests::ExceptBy
{
    TEST(Produce_set_difference_of_two_sequences_by_key, Returns_expected_sequence)
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
        const string except[]
        {
            "Thomas",
            "Robert",
            "Joseph",
            "David",
            "Richard"
        };
        const Customer expected[]
        {
            { 1U, "James" },
            { 3U, "John" },
            { 4U, "Michael" },
            { 6U, "William" }
        };

        // Act.
        const auto actual = From(source).ExceptBy(
            From(except),
            [](const Customer& customer){ return customer.name; }
        );

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Produce_set_difference_of_two_sequences_by_key, Returns_the_same_result_on_every_call)
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
        const string except[]
        {
            "Thomas",
            "Robert",
            "Joseph",
            "David",
            "Richard"
        };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.ExceptBy(
            From(except),
            [](const Customer& customer){ return customer.name; }
        );
        const auto actual2 = query.ExceptBy(
            From(except),
            [](const Customer& customer){ return customer.name; }
        );

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }
}