#include <cctype>
#include <optional>
#include <string>

#include "Assertions.hpp"
#include "CppLinq.hpp"
#include "OuterJoin/Person.hpp"
#include "OuterJoin/Pet.hpp"

using namespace CppLinq::Exceptions;
using namespace std;

namespace CppLinq::Tests::OuterJoin
{
    TEST(OuterJoin, ReturnsExpectedValues_SourcesHaveMatches_DefaultComparer)
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
        const pair<optional<Person>, optional<Pet>> expected[]
        {
            { { { "James" } }, nullopt },
            { { { "Robert" } }, { { "Luna", { "Robert" } } } },
            { { { "John" } }, { { "Milo", { "John" } } } },
            { { { "John" } }, { { "Leo", { "John" } }  }},
            { { { "Michael" } }, { { "Oliver", { "Michael" } } } },
            { { { "David" } }, nullopt },
            { { { "William" } }, { { "Loki", { "William" } } } },
            { { { "William" } }, { { "Bella", { "William" } } } },
            { nullopt, { { "Willow", { "Anthony" } } } },
            { nullopt, { { "Simba", { "Thomas" } } } },
        };

        // Act.
        const auto actual = From(source1).OuterJoin(
            From(source2),
            [](const Person& person){ return person; },
            [](const Pet& pet){ return pet.owner; },
            [](const optional<Person>& person, const optional<Pet>& pet){ return make_pair(person, pet); }
        );

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(OuterJoin, ReturnsExpectedValues_SourcesHaveMatches_CustomComparer)
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
        const pair<optional<Person>, optional<Pet>> expected[]
        {
            { { { "James" } }, { { "Milo", { "John" } } } },
            { { { "James" } }, { { "Leo", { "John" } } } },
            { { { "Robert" } }, { { "Luna", { "Robert" } } } },
            { { { "John" } }, { { "Milo", { "John" } } } },
            { { { "John" } }, { { "Leo", { "John" } } } },
            { { { "Michael" } }, { { "Oliver", { "Michael" } } } },
            { { { "David" } }, nullopt },
            { { { "William" } }, { { "Loki", { "William" } } } },
            { { { "William" } }, { { "Bella", { "William" } } } },
            { nullopt, { { "Willow", { "Anthony" } } } },
            { nullopt, { { "Simba", { "Thomas" } } } }
        };

        // Act.
        const auto actual = From(source1).OuterJoin(
            From(source2),
            [](const Person& person){ return person; },
            [](const Pet& pet){ return pet.owner; },
            [](const optional<Person>& person, const optional<Pet>& pet){ return make_pair(person, pet); },
            [](const Person& person1, const Person& person2){ return tolower(person1.name.front()) == tolower(person2.name.front()); }
        );

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(OuterJoin, ReturnsExpectedValues_SourcesDoNotHaveMatches_DefaultComparer)
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
        const pair<optional<Person>, optional<Pet>> expected[]
        {
            { { { "James" } }, nullopt },
            { { { "Robert" } }, nullopt },
            { { { "John" } }, nullopt },
            { { { "Michael" } }, nullopt },
            { { { "David" } }, nullopt },
            { { { "William" } }, nullopt },
            { nullopt, { { "Luna", { "Richard" } } } },
            { nullopt, { { "Willow", { "Anthony" } } } },
            { nullopt, { { "Milo", { "Joseph" } } } },
            { nullopt, { { "Oliver", { "Joseph" } } } },
            { nullopt, { { "Leo", { "Thomas" } } } },
            { nullopt, { { "Loki", { "Richard" } } } },
            { nullopt, { { "Bella", { "Charles" } } } },
            { nullopt, { { "Simba", { "Thomas" } } } }
        };

        // Act.
        const auto actual = From(source1).OuterJoin(
            From(source2),
            [](const Person& person){ return person; },
            [](const Pet& pet){ return pet.owner; },
            [](const optional<Person>& person, const optional<Pet>& pet){ return make_pair(person, pet); }
        );

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(OuterJoin, ReturnsExpectedValues_SourcesDoNotHaveMatches_CustomComparer)
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
            { "Willow", { "Anthony" } },
            { "Simba", { "Thomas" } }
        };
        const pair<optional<Person>, optional<Pet>> expected[]
        {
            { { { "James" } }, nullopt },
            { { { "Robert" } }, nullopt },
            { { { "John" } }, nullopt },
            { { { "Michael" } }, nullopt },
            { { { "David" } }, nullopt },
            { { { "William" } }, nullopt },
            { nullopt, { { "Willow", { "Anthony" } } } },
            { nullopt, { { "Simba", { "Thomas" } } } }
        };

        // Act.
        const auto actual = From(source1).OuterJoin(
            From(source2),
            [](const Person& person){ return person; },
            [](const Pet& pet){ return pet.owner; },
            [](const optional<Person>& person, const optional<Pet>& pet){ return make_pair(person, pet); },
            [](const Person& person1, const Person& person2){ return tolower(person1.name.front()) == tolower(person2.name.front()); }
        );

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(OuterJoin, ReturnsSameResults_DefaultComparer)
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
        const auto actual1 = query.OuterJoin(
            From(source2),
            [](const Person& person){ return person; },
            [](const Pet& pet){ return pet.owner; },
            [](const optional<Person>& person, const optional<Pet>& pet){ return make_pair(person, pet); }
        );
        const auto actual2 = query.OuterJoin(
            From(source2),
            [](const Person& person){ return person; },
            [](const Pet& pet){ return pet.owner; },
            [](const optional<Person>& person, const optional<Pet>& pet){ return make_pair(person, pet); }
        );

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }

    TEST(OuterJoin, ReturnsSameResults_CustomComparer)
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
        const auto actual1 = query.OuterJoin(
            From(source2),
            [](const Person& person){ return person; },
            [](const Pet& pet){ return pet.owner; },
            [](const optional<Person>& person, const optional<Pet>& pet){ return make_pair(person, pet); },
            [](const Person& person1, const Person& person2){ return tolower(person1.name.front()) == tolower(person2.name.front()); }
        );
        const auto actual2 = query.OuterJoin(
            From(source2),
            [](const Person& person){ return person; },
            [](const Pet& pet){ return pet.owner; },
            [](const optional<Person>& person, const optional<Pet>& pet){ return make_pair(person, pet); },
            [](const Person& person1, const Person& person2){ return tolower(person1.name.front()) == tolower(person2.name.front()); }
        );

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }

    TEST(OuterJoin, SourceThrowsOnMoveNext_DefaultComparer)
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

        const auto query = From(source1).OuterJoin(
            From(source2),
            [](const Person& person){ return person; },
            [](const Pet& pet){ return pet.owner; },
            [](const optional<Person>& person, const optional<Pet>& pet){ return make_pair(person, pet); }
        );

        auto enumerator = query.GetEnumerator();
        while (enumerator.HasCurrent())
        {
            enumerator.MoveNext();
        }

        // Act.
        // Assert.
        EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
    }

    TEST(OuterJoin, SourceThrowsOnGetCurrent_DefaultComparer)
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

        const auto query = From(source1).OuterJoin(
            From(source2),
            [](const Person& person){ return person; },
            [](const Pet& pet){ return pet.owner; },
            [](const optional<Person>& person, const optional<Pet>& pet){ return make_pair(person, pet); }
        );

        auto enumerator = query.GetEnumerator();
        while (enumerator.HasCurrent())
        {
            enumerator.MoveNext();
        }

        // Act.
        // Assert.
        EXPECT_THROW(enumerator.GetCurrent(), FinishedEnumeratorException);
    }

    TEST(OuterJoin, SourceThrowsOnMoveNext_CustomComparer)
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

        const auto query = From(source1).OuterJoin(
            From(source2),
            [](const Person& person){ return person; },
            [](const Pet& pet){ return pet.owner; },
            [](const optional<Person>& person, const optional<Pet>& pet){ return make_pair(person, pet); },
            [](const Person& person1, const Person& person2){ return tolower(person1.name.front()) == tolower(person2.name.front()); }
        );

        auto enumerator = query.GetEnumerator();
        while (enumerator.HasCurrent())
        {
            enumerator.MoveNext();
        }

        // Act.
        // Assert.
        EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
    }

    TEST(OuterJoin, SourceThrowsOnGetCurrent_CustomComparer)
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

        const auto query = From(source1).OuterJoin(
            From(source2),
            [](const Person& person){ return person; },
            [](const Pet& pet){ return pet.owner; },
            [](const optional<Person>& person, const optional<Pet>& pet){ return make_pair(person, pet); },
            [](const Person& person1, const Person& person2){ return tolower(person1.name.front()) == tolower(person2.name.front()); }
        );

        auto enumerator = query.GetEnumerator();
        while (enumerator.HasCurrent())
        {
            enumerator.MoveNext();
        }

        // Act.
        // Assert.
        EXPECT_THROW(enumerator.GetCurrent(), FinishedEnumeratorException);
    }
}