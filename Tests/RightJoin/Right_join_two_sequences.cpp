#include <optional>
#include <utility>

#include "Assertions.hpp"
#include "CppLinq.hpp"
#include "RightJoin/Stubs/Person.hpp"
#include "RightJoin/Stubs/Pet.hpp"

using namespace CppLinq::Tests::RightJoin::Stubs;
using namespace std;

namespace CppLinq::Tests::RightJoin
{
    TEST(Right_join_two_sequences, Returns_expected_sequence_if_sources_have_matching_keys)
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
            { "Willow", { "Anthony" } },
            { "Milo", { "John" } },
            { "Oliver", { "Michael" } },
            { "Leo", { "John" } },
            { "Loki", { "William" } },
            { "Bella", { "William" } },
            { "Simba", { "Thomas" } },
        };
        const pair<optional<Person>, Pet> expected[]
        {
            { { { "Robert" } }, { "Luna", { "Robert" } } },
            { { { "John" } }, { "Milo", { "John" } } },
            { { { "John" } }, { "Leo", { "John" } } },
            { { { "Michael" } }, { "Oliver", { "Michael" } } },
            { { { "William" } }, { "Loki", { "William" } } },
            { { { "William" } }, { "Bella", { "William" } } },
            { nullopt, { "Willow", { "Anthony" } } },
            { nullopt, { "Simba", { "Thomas" } } },
        };

        // Act.
        const auto actual = From(source1).RightJoin(
            From(source2),
            [](const Person& person){ return person; },
            [](const Pet& pet){ return pet.owner; },
            [](const optional<Person>& person, const Pet& pet){ return make_pair(person, pet); }
        );

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Right_join_two_sequences, Returns_expected_sequence_if_sources_do_not_have_matching_keys)
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
            { "Willow", { "Anthony" } },
            { "Milo", { "Joseph" } },
            { "Oliver", { "Joseph" } },
            { "Leo", { "Thomas" } },
            { "Loki", { "Richard" } },
            { "Bella", { "Charles" } },
            { "Simba", { "Thomas" } },
        };
        const pair<optional<Person>, Pet> expected[]
        {
            { nullopt, { "Luna", { "Richard" } } },
            { nullopt, { "Willow", { "Anthony" } } },
            { nullopt, { "Milo", { "Joseph" } } },
            { nullopt, { "Oliver", { "Joseph" } } },
            { nullopt, { "Leo", { "Thomas" } } },
            { nullopt, { "Loki", { "Richard" } } },
            { nullopt, { "Bella", { "Charles" } } },
            { nullopt, { "Simba", { "Thomas" } } }
        };

        // Act.
        const auto actual = From(source1).RightJoin(
            From(source2),
            [](const Person& person){ return person; },
            [](const Pet& pet){ return pet.owner; },
            [](const optional<Person>& person, const Pet& pet){ return make_pair(person, pet); }
        );

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Right_join_two_sequences, Returns_the_same_result_on_every_call)
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
            { "Willow", { "Anthony" } },
            { "Milo", { "John" } },
            { "Oliver", { "Michael" } },
            { "Leo", { "John" } },
            { "Loki", { "William" } },
            { "Bella", { "William" } },
            { "Simba", { "Thomas" } },
        };

        const auto query = From(source1);

        // Act.
        const auto actual1 = query.RightJoin(
            From(source2),
            [](const Person& person){ return person; },
            [](const Pet& pet){ return pet.owner; },
            [](const optional<Person>& person, const Pet& pet){ return make_pair(person, pet); }
        );
        const auto actual2 = query.RightJoin(
            From(source2),
            [](const Person& person){ return person; },
            [](const Pet& pet){ return pet.owner; },
            [](const optional<Person>& person, const Pet& pet){ return make_pair(person, pet); }
        );

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }
}