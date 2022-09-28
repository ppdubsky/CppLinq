#include <cctype>
#include <string>

#include "Assertions.hpp"
#include "CppLinq.hpp"
#include "IntersectBy/Stubs/Customer.hpp"

using namespace CppLinq::Tests::IntersectBy::Stubs;
using namespace std;

namespace CppLinq::Tests::IntersectBy
{
    TEST(Produce_set_intersection_of_two_sequences_by_key_using_comparer, Returns_expected_sequence)
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
            "thomas",
            "robert",
            "joseph",
            "david",
            "richard"
        };
        const Customer expected[]
        {
            { 1U, "James" },
            { 2U, "Robert" },
            { 3U, "John" },
            { 5U, "David" }
        };

        // Act.
        const auto actual = From(source).IntersectBy(
            From(intersect),
            [](const Customer& customer){ return customer.name; },
            [](const string& value1, const string& value2){ return tolower(value1.front()) == tolower(value2.front()); }
        );

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Produce_set_intersection_of_two_sequences_by_key_using_comparer, Returns_the_same_result_on_every_call)
    {
        // Arrange.
        const Customer source[]
        {
            { 1U, "James" },
            { 2U, "Robert" },
            { 3U, "robert" },
            { 4U, "John" },
            { 5U, "john" },
            { 6U, "Michael" },
            { 7U, "David" },
            { 8U, "david" },
            { 9U, "William" }
        };
        const string intersect[]
        {
            "thomas",
            "robert",
            "joseph",
            "david",
            "richard"
        };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.IntersectBy(
            From(intersect),
            [](const Customer& customer){ return customer.name; },
            [](const string& value1, const string& value2){ return tolower(value1.front()) == tolower(value2.front()); }
        );
        const auto actual2 = query.IntersectBy(
            From(intersect),
            [](const Customer& customer){ return customer.name; },
            [](const string& value1, const string& value2){ return tolower(value1.front()) == tolower(value2.front()); }
        );

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }
}