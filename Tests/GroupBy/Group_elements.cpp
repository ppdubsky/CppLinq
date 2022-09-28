#include <cstdint>
#include <string>
#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"
#include "GroupBy/Stubs/Human.hpp"
#include "GroupBy/Stubs/Join.hpp"

using namespace CppLinq::Tests::GroupBy::Stubs;
using namespace std;

namespace CppLinq::Tests::GroupBy
{
    TEST(Group_elements, Returns_expected_sequence)
    {
        // Arrange.
        const Human source[]
        {
            { 16U, "James" },
            { 24U, "Robert" },
            { 45U, "John" },
            { 43U, "Michael" },
            { 16U, "David" },
            { 45U, "William" },
            { 45U, "Richard" },
            { 50U, "Joseph" }
        };
        const string expected[]
        {
            "16 JamesDavid",
            "24 Robert",
            "45 JohnWilliamRichard",
            "43 Michael",
            "50 Joseph"
        };

        // Act.
        const auto actual = From(source).GroupBy(
            [](const Human& human){ return human.age; },
            [](const Human& human){ return human.name; },
            [](const uint32_t age, const vector<string>& elements){ return to_string(age) + " " + Join(elements); }
        );

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Group_elements, Returns_the_same_result_on_every_call)
    {
        // Arrange.
        const Human source[]
        {
            { 16U, "James" },
            { 24U, "Robert" },
            { 45U, "John" },
            { 43U, "Michael" },
            { 16U, "David" },
            { 45U, "William" },
            { 45U, "Richard" },
            { 50U, "Joseph" }
        };

        const auto query = From(source);

        // Act.
        const auto actual1 = From(source).GroupBy(
            [](const Human& human){ return human.age; },
            [](const Human& human){ return human.name; },
            [](const uint32_t age, const vector<string>& elements){ return to_string(age) + " " + Join(elements); }
        );
        const auto actual2 = From(source).GroupBy(
            [](const Human& human){ return human.age; },
            [](const Human& human){ return human.name; },
            [](const uint32_t age, const vector<string>& elements){ return to_string(age) + " " + Join(elements); }
        );

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }
}