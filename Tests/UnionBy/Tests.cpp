#include <cctype>
#include <string>

#include "Assertions.hpp"
#include "CppLinq.hpp"
#include "UnionBy/Customer.hpp"

using namespace CppLinq::Exceptions;
using namespace std;

namespace CppLinq::Tests::UnionBy
{
    TEST(UnionBy, ReturnsExpectedValues_DefaultComparer)
    {
        // Arrange.
        const Customer source1[]
        {
            { 1U, "James" },
            { 2U, "Robert" },
            { 3U, "John" },
            { 4U, "John" },
            { 5U, "Michael" },
            { 6U, "David" },
            { 7U, "William" }
        };
        const Customer source2[]
        {
            { 8U, "Robert" },
            { 9U, "Richard" },
            { 10U, "Joseph" },
            { 11U, "James" },
            { 12U, "James" },
            { 13U, "Thomas" },
            { 14U, "Michael" }
        };
        const Customer expected[]
        {
            { 1U, "James" },
            { 2U, "Robert" },
            { 3U, "John" },
            { 5U, "Michael" },
            { 6U, "David" },
            { 7U, "William" },
            { 9U, "Richard" },
            { 10U, "Joseph" },
            { 13U, "Thomas" }
        };

        const auto query1 = From(source1);
        const auto query2 = From(source2);

        // Act.
        const auto actual = query1.UnionBy(query2, [](const Customer& customer){ return customer.name; });

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(UnionBy, ReturnsExpectedValues_CustomComparer)
    {
        // Arrange.
        const Customer source1[]
        {
            { 1U, "James" },
            { 2U, "Robert" },
            { 3U, "John" },
            { 4U, "John" },
            { 5U, "Michael" },
            { 6U, "David" },
            { 7U, "William" }
        };
        const Customer source2[]
        {
            { 8U, "Robert" },
            { 9U, "Richard" },
            { 10U, "Joseph" },
            { 11U, "James" },
            { 12U, "James" },
            { 13U, "Thomas" },
            { 14U, "Michael" }
        };
        const Customer expected[]
        {
            { 1U, "James" },
            { 2U, "Robert" },
            { 5U, "Michael" },
            { 6U, "David" },
            { 7U, "William" },
            { 13U, "Thomas" }
        };

        const auto query1 = From(source1);
        const auto query2 = From(source2);

        // Act.
        const auto actual = query1.UnionBy(query2, [](const Customer& customer){ return customer.name; }, [](const string& value1, const string& value2){ return tolower(value1.front()) == tolower(value2.front()); });

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(UnionBy, ReturnsSameResults_DefaultComparer)
    {
        // Arrange.
        const Customer source1[]
        {
            { 1U, "James" },
            { 2U, "Robert" },
            { 3U, "John" },
            { 4U, "John" },
            { 5U, "Michael" },
            { 6U, "David" },
            { 7U, "William" }
        };
        const Customer source2[]
        {
            { 8U, "Robert" },
            { 9U, "Richard" },
            { 10U, "Joseph" },
            { 11U, "James" },
            { 12U, "James" },
            { 13U, "Thomas" },
            { 14U, "Michael" }
        };

        const auto query1 = From(source1);
        const auto query2 = From(source2);

        // Act.
        const auto actual1 = query1.UnionBy(query2, [](const Customer& customer){ return customer.name; });
        const auto actual2 = query1.UnionBy(query2, [](const Customer& customer){ return customer.name; });

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }

    TEST(UnionBy, ReturnsSameResults_CustomComparer)
    {
        // Arrange.
        const Customer source1[]
        {
            { 1U, "James" },
            { 2U, "Robert" },
            { 3U, "John" },
            { 4U, "John" },
            { 5U, "Michael" },
            { 6U, "David" },
            { 7U, "William" }
        };
        const Customer source2[]
        {
            { 8U, "Robert" },
            { 9U, "Richard" },
            { 10U, "Joseph" },
            { 11U, "James" },
            { 12U, "James" },
            { 13U, "Thomas" },
            { 14U, "Michael" }
        };

        const auto query1 = From(source1);
        const auto query2 = From(source2);

        // Act.
        const auto actual1 = query1.UnionBy(query2, [](const Customer& customer){ return customer.name; }, [](const string& value1, const string& value2){ return tolower(value1.front()) == tolower(value2.front()); });
        const auto actual2 = query1.UnionBy(query2, [](const Customer& customer){ return customer.name; }, [](const string& value1, const string& value2){ return tolower(value1.front()) == tolower(value2.front()); });

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }

    TEST(UnionBy, SourceThrowsOnMoveNext_DefaultComparer)
    {
        // Arrange.
        const Customer source1[]
        {
            { 1U, "James" },
            { 2U, "Robert" },
            { 3U, "John" },
            { 4U, "John" },
            { 5U, "Michael" },
            { 6U, "David" },
            { 7U, "William" }
        };
        const Customer source2[]
        {
            { 8U, "Robert" },
            { 9U, "Richard" },
            { 10U, "Joseph" },
            { 11U, "James" },
            { 12U, "James" },
            { 13U, "Thomas" },
            { 14U, "Michael" }
        };

        const auto query = From(source1).UnionBy(From(source2), [](const Customer& customer){ return customer.name; });

        auto enumerator = query.GetEnumerator();
        while (enumerator.HasCurrent())
        {
            enumerator.MoveNext();
        }

        // Act.
        // Assert.
        EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
    }

    TEST(UnionBy, SourceThrowsOnGetCurrent_DefaultComparer)
    {
        // Arrange.
        const Customer source1[]
        {
            { 1U, "James" },
            { 2U, "Robert" },
            { 3U, "John" },
            { 4U, "John" },
            { 5U, "Michael" },
            { 6U, "David" },
            { 7U, "William" }
        };
        const Customer source2[]
        {
            { 8U, "Robert" },
            { 9U, "Richard" },
            { 10U, "Joseph" },
            { 11U, "James" },
            { 12U, "James" },
            { 13U, "Thomas" },
            { 14U, "Michael" }
        };

        const auto query = From(source1).UnionBy(From(source2), [](const Customer& customer){ return customer.name; });

        auto enumerator = query.GetEnumerator();
        while (enumerator.HasCurrent())
        {
            enumerator.MoveNext();
        }

        // Act.
        // Assert.
        EXPECT_THROW(enumerator.GetCurrent(), FinishedEnumeratorException);
    }

    TEST(UnionBy, SourceThrowsOnMoveNext_CustomComparer)
    {
        // Arrange.
        const Customer source1[]
        {
            { 1U, "James" },
            { 2U, "Robert" },
            { 3U, "John" },
            { 4U, "John" },
            { 5U, "Michael" },
            { 6U, "David" },
            { 7U, "William" }
        };
        const Customer source2[]
        {
            { 8U, "Robert" },
            { 9U, "Richard" },
            { 10U, "Joseph" },
            { 11U, "James" },
            { 12U, "James" },
            { 13U, "Thomas" },
            { 14U, "Michael" }
        };

        const auto query = From(source1).UnionBy(From(source2), [](const Customer& customer){ return customer.name; }, [](const string& value1, const string& value2){ return tolower(value1.front()) == tolower(value2.front()); });

        auto enumerator = query.GetEnumerator();
        while (enumerator.HasCurrent())
        {
            enumerator.MoveNext();
        }

        // Act.
        // Assert.
        EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
    }

    TEST(UnionBy, SourceThrowsOnGetCurrent_CustomComparer)
    {
        // Arrange.
        const Customer source1[]
        {
            { 1U, "James" },
            { 2U, "Robert" },
            { 3U, "John" },
            { 4U, "John" },
            { 5U, "Michael" },
            { 6U, "David" },
            { 7U, "William" }
        };
        const Customer source2[]
        {
            { 8U, "Robert" },
            { 9U, "Richard" },
            { 10U, "Joseph" },
            { 11U, "James" },
            { 12U, "James" },
            { 13U, "Thomas" },
            { 14U, "Michael" }
        };

        const auto query = From(source1).UnionBy(From(source2), [](const Customer& customer){ return customer.name; }, [](const string& value1, const string& value2){ return tolower(value1.front()) == tolower(value2.front()); });

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