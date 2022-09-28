#include <cctype>
#include <string>

#include "Assertions.hpp"
#include "CppLinq.hpp"
#include "IntersectBy/Stubs/Customer.hpp"

using namespace CppLinq::Tests::IntersectBy::Stubs;
using namespace std;

namespace CppLinq::Tests::IntersectBy
{
    TEST(Produce_set_intersection_of_two_sequences_by_key, Returns_expected_sequence)
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
        const string intersect[]
        {
            "Thomas",
            "Robert",
            "Joseph",
            "David",
            "Richard"
        };
        const Customer expected[]
        {
            { 2U, "Robert" },
            { 5U, "David" }
        };

        // Act.
        const auto actual = From(source).IntersectBy(
            From(intersect),
            [](const Customer& customer){ return customer.name; }
        );

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Produce_set_intersection_of_two_sequences_by_key, Returns_the_same_result_on_every_call)
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
        const string intersect[]
        {
            "Thomas",
            "Robert",
            "Joseph",
            "David",
            "Richard"
        };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.IntersectBy(
            From(intersect),
            [](const Customer& customer){ return customer.name; }
        );
        const auto actual2 = query.IntersectBy(
            From(intersect),
            [](const Customer& customer){ return customer.name; }
        );

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }
}