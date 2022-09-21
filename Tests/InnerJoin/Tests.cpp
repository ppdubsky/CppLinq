#include <cctype>
#include <string>

#include "Assertions.hpp"
#include "CppLinq.hpp"
#include "InnerJoin/Person.hpp"
#include "InnerJoin/Pet.hpp"

using namespace CppLinq::Exceptions;
using namespace std;

namespace CppLinq::Tests::InnerJoin
{
    TEST(InnerJoin, ReturnsExpectedValues_SourcesHaveMatches_DefaultComparer)
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

    TEST(InnerJoin, ReturnsExpectedValues_SourcesHaveMatches_CustomComparer)
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
            { { "James" }, { "Milo", { "John" } } },
            { { "James" }, { "Leo", { "John" } } },
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
            [](const Person& person, const Pet& pet){ return make_pair(person, pet); },
            [](const Person& person1, const Person& person2){ return tolower(person1.name.front()) == tolower(person2.name.front()); }
        );

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(InnerJoin, ReturnsExpectedValues_SourcesDoNotHaveMatches_DefaultComparer)
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

    TEST(InnerJoin, ReturnsExpectedValues_SourcesDoNotHaveMatches_CustomComparer)
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
            { "Leo", { "Thomas" } },
            { "Bella", { "Charles" } }
        };

        // Act.
        const auto actual = From(source1).InnerJoin(
            From(source2),
            [](const Person& person){ return person; },
            [](const Pet& pet){ return pet.owner; },
            [](const Person& person, const Pet& pet){ return make_pair(person, pet); },
            [](const Person& person1, const Person& person2){ return tolower(person1.name.front()) == tolower(person2.name.front()); }
        );

        // Assert.
        ExpectSequenceIsEmpty(actual);
    }

    TEST(InnerJoin, ReturnsSameResults_DefaultComparer)
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

    TEST(InnerJoin, ReturnsSameResults_CustomComparer)
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
            [](const Person& person, const Pet& pet){ return make_pair(person, pet); },
            [](const Person& person1, const Person& person2){ return tolower(person1.name.front()) == tolower(person2.name.front()); }
        );
        const auto actual2 = query.InnerJoin(
            From(source2),
            [](const Person& person){ return person; },
            [](const Pet& pet){ return pet.owner; },
            [](const Person& person, const Pet& pet){ return make_pair(person, pet); },
            [](const Person& person1, const Person& person2){ return tolower(person1.name.front()) == tolower(person2.name.front()); }
        );

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }

    TEST(InnerJoin, SourceThrowsOnMoveNext_DefaultComparer)
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

        const auto query = From(source1).InnerJoin(
            From(source2),
            [](const Person& person){ return person; },
            [](const Pet& pet){ return pet.owner; },
            [](const Person& person, const Pet& pet){ return make_pair(person, pet); }
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

    TEST(InnerJoin, SourceThrowsOnGetCurrent_DefaultComparer)
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

        const auto query = From(source1).InnerJoin(
            From(source2),
            [](const Person& person){ return person; },
            [](const Pet& pet){ return pet.owner; },
            [](const Person& person, const Pet& pet){ return make_pair(person, pet); }
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

    TEST(InnerJoin, SourceThrowsOnMoveNext_CustomComparer)
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

        const auto query = From(source1).InnerJoin(
            From(source2),
            [](const Person& person){ return person; },
            [](const Pet& pet){ return pet.owner; },
            [](const Person& person, const Pet& pet){ return make_pair(person, pet); },
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

    TEST(InnerJoin, SourceThrowsOnGetCurrent_CustomComparer)
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

        const auto query = From(source1).InnerJoin(
            From(source2),
            [](const Person& person){ return person; },
            [](const Pet& pet){ return pet.owner; },
            [](const Person& person, const Pet& pet){ return make_pair(person, pet); },
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