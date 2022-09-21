#include <cctype>
#include <string>

#include "Assertions.hpp"
#include "CppLinq.hpp"
#include "IntersectBy/Customer.hpp"
#include "IntersectBy/Equatable.hpp"

using namespace CppLinq::Exceptions;
using namespace std;

namespace CppLinq::Tests::IntersectBy
{
    TEST(IntersectBy, ExecutionIsDeferred_DefaultComparer)
    {
        // Arrange.
        Equatable::equalityCount = 0U;

        const Equatable source[]{ 'a', 'b', 'c', 'd', 'e' };
        const Equatable intersect[]{ 'b', 'd', 'e', 'f', 'g' };

        // Act.
        const auto actual = From(source).IntersectBy(From(intersect), [](const Equatable value){ return value; });

        // Assert.
        EXPECT_EQ(Equatable::equalityCount, 0U);
    }

    TEST(IntersectBy, ExecutionIsDeferred_CustomComparer)
    {
        // Arrange.
        Equatable::equalityCount = 0U;

        const Equatable source[]{ 'a', 'b', 'c', 'd', 'e' };
        const Equatable intersect[]{ 'b', 'd', 'e', 'f', 'g' };

        // Act.
        const auto actual = From(source).IntersectBy(From(intersect), [](const Equatable value){ return value; }, [](const Equatable value1, const Equatable value2){ return value1.EqualTo(value2); });

        // Assert.
        EXPECT_EQ(Equatable::equalityCount, 0U);
    }

    TEST(IntersectBy, ReturnsExpectedValues_DefaultComparer)
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
        const auto actual = From(source).IntersectBy(From(intersect), [](const Customer& customer){ return customer.name; });

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(IntersectBy, ReturnsExpectedValues_CustomComparer)
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
        const auto actual = From(source).IntersectBy(From(intersect), [](const Customer& customer){ return customer.name; }, [](const string& value1, const string& value2){ return tolower(value1.front()) == tolower(value2.front()); });

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(IntersectBy, ReturnsSameResults_DefaultComparer)
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
        const auto actual1 = query.IntersectBy(From(intersect), [](const Customer& customer){ return customer.name; });
        const auto actual2 = query.IntersectBy(From(intersect), [](const Customer& customer){ return customer.name; });

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }

    TEST(IntersectBy, ReturnsSameResults_CustomComparer)
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
        const auto actual1 = query.IntersectBy(From(intersect), [](const Customer& customer){ return customer.name; }, [](const string& value1, const string& value2){ return tolower(value1.front()) == tolower(value2.front()); });
        const auto actual2 = query.IntersectBy(From(intersect), [](const Customer& customer){ return customer.name; }, [](const string& value1, const string& value2){ return tolower(value1.front()) == tolower(value2.front()); });

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }

    TEST(IntersectBy, SourceThrowsOnMoveNext_DefaultComparer)
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

        const auto query = From(source).IntersectBy(From(intersect), [](const Customer& customer){ return customer.name; });

        auto enumerator = query.GetEnumerator();
        while (enumerator.HasCurrent())
        {
            enumerator.MoveNext();
        }

        // Act.
        // Assert.
        EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
    }

    TEST(IntersectBy, SourceThrowsOnGetCurrent_DefaultComparer)
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

        const auto query = From(source).IntersectBy(From(intersect), [](const Customer& customer){ return customer.name; });

        auto enumerator = query.GetEnumerator();
        while (enumerator.HasCurrent())
        {
            enumerator.MoveNext();
        }

        // Act.
        // Assert.
        EXPECT_THROW(enumerator.GetCurrent(), FinishedEnumeratorException);
    }

    TEST(IntersectBy, SourceThrowsOnMoveNext_CustomComparer)
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

        const auto query = From(source).IntersectBy(From(intersect), [](const Customer& customer){ return customer.name; }, [](const string& value1, const string& value2){ return tolower(value1.front()) == tolower(value2.front()); });

        auto enumerator = query.GetEnumerator();
        while (enumerator.HasCurrent())
        {
            enumerator.MoveNext();
        }

        // Act.
        // Assert.
        EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
    }

    TEST(IntersectBy, SourceThrowsOnGetCurrent_CustomComparer)
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

        const auto query = From(source).IntersectBy(From(intersect), [](const Customer& customer){ return customer.name; }, [](const string& value1, const string& value2){ return tolower(value1.front()) == tolower(value2.front()); });

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