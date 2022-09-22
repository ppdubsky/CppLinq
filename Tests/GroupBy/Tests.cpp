#include <cstdint>
#include <string>
#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"
#include "GroupBy/Human.hpp"

using namespace CppLinq::Exceptions;
using namespace std;

namespace CppLinq::Tests::GroupBy
{
    auto Join(const vector<string>& elements) -> string
    {
        string joinedString;

        for (const string& element : elements)
        {
            joinedString.append(element);
        }

        return joinedString;
    }

    TEST(GroupBy, ReturnsExpectedValues_SourcesHaveMatches_DefaultComparer)
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

    TEST(GroupBy, ReturnsExpectedValues_SourcesHaveMatches_CustomComparer)
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
            "45 JohnMichaelWilliamRichard",
            "50 Joseph"
        };

        // Act.
        const auto actual = From(source).GroupBy(
            [](const Human& human){ return human.age; },
            [](const Human& human){ return human.name; },
            [](const uint32_t age, const vector<string>& elements){ return to_string(age) + " " + Join(elements); },
            [](const uint32_t value1, const uint32_t value2){ return value1 / 10U == value2 / 10U; }
        );

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(GroupBy, ReturnsSameResults_DefaultComparer)
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

    TEST(GroupBy, ReturnsSameResults_CustomComparer)
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
            [](const uint32_t age, const vector<string>& elements){ return to_string(age) + " " + Join(elements); },
            [](const uint32_t value1, const uint32_t value2){ return value1 / 10U == value2 / 10U; }
        );
        const auto actual2 = From(source).GroupBy(
            [](const Human& human){ return human.age; },
            [](const Human& human){ return human.name; },
            [](const uint32_t age, const vector<string>& elements){ return to_string(age) + " " + Join(elements); },
            [](const uint32_t value1, const uint32_t value2){ return value1 / 10U == value2 / 10U; }
        );

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }

    TEST(GroupBy, SourceThrowsOnMoveNext_DefaultComparer)
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

        const auto query = From(source).GroupBy(
            [](const Human& human){ return human.age; },
            [](const Human& human){ return human.name; },
            [](const uint32_t age, const vector<string>& elements){ return to_string(age) + " " + Join(elements); }
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

    TEST(GroupBy, SourceThrowsOnGetCurrent_DefaultComparer)
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

        const auto query = From(source).GroupBy(
            [](const Human& human){ return human.age; },
            [](const Human& human){ return human.name; },
            [](const uint32_t age, const vector<string>& elements){ return to_string(age) + " " + Join(elements); }
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

    TEST(GroupBy, SourceThrowsOnMoveNext_CustomComparer)
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

        const auto query = From(source).GroupBy(
            [](const Human& human){ return human.age; },
            [](const Human& human){ return human.name; },
            [](const uint32_t age, const vector<string>& elements){ return to_string(age) + " " + Join(elements); },
            [](const uint32_t value1, const uint32_t value2){ return value1 / 10U == value2 / 10U; }
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

    TEST(GroupBy, SourceThrowsOnGetCurrent_CustomComparer)
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

        const auto query = From(source).GroupBy(
            [](const Human& human){ return human.age; },
            [](const Human& human){ return human.name; },
            [](const uint32_t age, const vector<string>& elements){ return to_string(age) + " " + Join(elements); },
            [](const uint32_t value1, const uint32_t value2){ return value1 / 10U == value2 / 10U; }
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