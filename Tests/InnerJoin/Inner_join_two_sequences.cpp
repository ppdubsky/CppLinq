#include <utility>

#include "Assertions.hpp"
#include "CppLinq.hpp"
#include "InnerJoin/Stubs/Person.hpp"
#include "InnerJoin/Stubs/Pet.hpp"

using namespace CppLinq::Tests::InnerJoin::Stubs;
using namespace std;

namespace CppLinq::Tests::InnerJoin
{
    TEST(Inner_join_two_sequences, Returns_expected_sequence_if_sources_have_matching_keys)
    {
        // Arrange.
        const Person source1[]
        {
            { "James" },
            { "Robert" },
            { "John" },
            { "Michael" },
            { "David" },
            { "William" }
        };
        const Pet source2[]
        {
            { "Luna", { "Robert" } },
            { "Milo", { "John" } },
            { "Oliver", { "Michael" } },
            { "Leo", { "John" } },
            { "Loki", { "William" } },
            { "Bella", { "William" } }
        };
        const pair<Person, Pet> expected[]
        {
            { { "Robert" }, { "Luna", { "Robert" } } },
            { { "John" }, { "Milo", { "John" } } },
            { { "John" }, { "Leo", { "John" } } },
            { { "Michael" }, { "Oliver", { "Michael" } } },
            { { "William" }, { "Loki", { "William" } } },
            { { "William" }, { "Bella", { "William" } } }
        };

        // Act.
        const auto actual = From(source1).InnerJoin(
            From(source2),
            [](const Person& person){ return person; },
            [](const Pet& pet){ return pet.owner; },
            [](const Person& person, const Pet& pet){ return make_pair(person, pet); }
        );

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Inner_join_two_sequences, Returns_empty_sequence_if_sources_do_not_have_matching_keys)
    {
        // Arrange.
        const Person source1[]
        {
            { "James" },
            { "Robert" },
            { "John" },
            { "Michael" },
            { "David" },
            { "William" }
        };
        const Pet source2[]
        {
            { "Luna", { "Richard" } },
            { "Milo", { "Joseph" } },
            { "Oliver", { "Joseph" } },
            { "Leo", { "Thomas" } },
            { "Loki", { "Richard" } },
            { "Bella", { "Charles" } }
        };

        // Act.
        const auto actual = From(source1).InnerJoin(
            From(source2),
            [](const Person& person){ return person; },
            [](const Pet& pet){ return pet.owner; },
            [](const Person& person, const Pet& pet){ return make_pair(person, pet); }
        );

        // Assert.
        ExpectSequenceIsEmpty(actual);
    }

    TEST(Inner_join_two_sequences, Returns_the_same_result_on_every_call)
    {
        // Arrange.
        const Person source1[]
        {
            { "James" },
            { "Robert" },
            { "John" },
            { "Michael" },
            { "David" },
            { "William" }
        };
        const Pet source2[]
        {
            { "Luna", { "Robert" } },
            { "Milo", { "John" } },
            { "Oliver", { "Michael" } },
            { "Leo", { "John" } },
            { "Loki", { "William" } },
            { "Bella", { "William" } }
        };

        const auto query = From(source1);

        // Act.
        const auto actual1 = query.InnerJoin(
            From(source2),
            [](const Person& person){ return person; },
            [](const Pet& pet){ return pet.owner; },
            [](const Person& person, const Pet& pet){ return make_pair(person, pet); }
        );
        const auto actual2 = query.InnerJoin(
            From(source2),
            [](const Person& person){ return person; },
            [](const Pet& pet){ return pet.owner; },
            [](const Person& person, const Pet& pet){ return make_pair(person, pet); }
        );

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }
}