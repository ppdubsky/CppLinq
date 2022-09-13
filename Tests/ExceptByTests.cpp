#include <cctype>
#include <string>

#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace CppLinq::Exceptions;
using namespace std;

struct Customer final
{
    auto operator==(const Customer& right) const -> bool
    {
        return id == right.id && name == right.name;
    }

    uint32_t id;
    string name;
};

struct ExceptByEquatable final
{
    auto EqualTo(const ExceptByEquatable other) const -> bool
    {
        ++equalityCount;

        return value == other.value;
    }

    auto operator==(const ExceptByEquatable right) const -> bool
    {
        return EqualTo(right);
    }

    static uint32_t equalityCount;

    uint32_t value;
};

uint32_t ExceptByEquatable::equalityCount = 0U;

TEST(ExceptBy, ExecutionIsDeferred_DefaultComparer)
{
    // Arrange.
    ExceptByEquatable::equalityCount = 0U;

    const ExceptByEquatable source[]{ 'a', 'b', 'c', 'd', 'e' };
    const ExceptByEquatable except[]{ 'b', 'd', 'e', 'f', 'g' };

    // Act.
    const auto actual = From(source).ExceptBy(From(except), [](const ExceptByEquatable value){ return value; });

    // Assert.
    EXPECT_EQ(ExceptByEquatable::equalityCount, 0U);
}

TEST(ExceptBy, ExecutionIsDeferred_CustomComparer)
{
    // Arrange.
    ExceptByEquatable::equalityCount = 0U;

    const ExceptByEquatable source[]{ 'a', 'b', 'c', 'd', 'e' };
    const ExceptByEquatable except[]{ 'b', 'd', 'e', 'f', 'g' };

    // Act.
    const auto actual = From(source).ExceptBy(From(except), [](const ExceptByEquatable value){ return value; }, [](const ExceptByEquatable value1, const ExceptByEquatable value2){ return value1.EqualTo(value2); });

    // Assert.
    EXPECT_EQ(ExceptByEquatable::equalityCount, 0U);
}

TEST(ExceptBy, ReturnsExpectedValues_DefaultComparer)
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
    const string except[]
    {
        "Thomas",
        "Robert",
        "Joseph",
        "David",
        "Richard"
    };
    const Customer expected[]
    {
        { 1U, "James" },
        { 3U, "John" },
        { 4U, "Michael" },
        { 6U, "William" }
    };

    // Act.
    const auto actual = From(source).ExceptBy(From(except), [](const Customer& customer){ return customer.name; });

    // Assert.
    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(ExceptBy, ReturnsExpectedValues_CustomComparer)
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
    const string except[]
    {
        "thomas",
        "robert",
        "joseph",
        "david",
        "richard"
    };
    const Customer expected[]
    {
        { 4U, "Michael" },
        { 6U, "William" }
    };

    // Act.
    const auto actual = From(source).ExceptBy(From(except), [](const Customer& customer){ return customer.name; }, [](const string& value1, const string& value2){ return tolower(value1.front()) == tolower(value2.front()); });

    // Assert.
    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(ExceptBy, ReturnsSameResults_DefaultComparer)
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
    const string except[]
    {
        "Thomas",
        "Robert",
        "Joseph",
        "David",
        "Richard"
    };

    const auto query = From(source);

    // Act.
    const auto actual1 = query.ExceptBy(From(except), [](const Customer& customer){ return customer.name; });
    const auto actual2 = query.ExceptBy(From(except), [](const Customer& customer){ return customer.name; });

    // Assert.
    ExpectSequencesAreEquivalent(actual1, actual2);
}

TEST(ExceptBy, ReturnsSameResults_CustomComparer)
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
    const string except[]
    {
        "thomas",
        "robert",
        "joseph",
        "david",
        "richard"
    };

    const auto query = From(source);

    // Act.
    const auto actual1 = query.ExceptBy(From(except), [](const Customer& customer){ return customer.name; }, [](const string& value1, const string& value2){ return tolower(value1.front()) == tolower(value2.front()); });
    const auto actual2 = query.ExceptBy(From(except), [](const Customer& customer){ return customer.name; }, [](const string& value1, const string& value2){ return tolower(value1.front()) == tolower(value2.front()); });

    // Assert.
    ExpectSequencesAreEquivalent(actual1, actual2);
}

TEST(ExceptBy, SourceThrowsOnMoveNext_DefaultComparer)
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
    const string except[]
    {
        "Thomas",
        "Robert",
        "Joseph",
        "David",
        "Richard"
    };

    const auto query = From(source).ExceptBy(From(except), [](const Customer& customer){ return customer.name; });

    auto enumerator = query.GetEnumerator();
    while (enumerator.HasCurrent())
    {
        enumerator.MoveNext();
    }

    // Act.
    // Assert.
    EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
}

TEST(ExceptBy, SourceThrowsOnGetCurrent_DefaultComparer)
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
    const string except[]
    {
        "Thomas",
        "Robert",
        "Joseph",
        "David",
        "Richard"
    };

    const auto query = From(source).ExceptBy(From(except), [](const Customer& customer){ return customer.name; });

    auto enumerator = query.GetEnumerator();
    while (enumerator.HasCurrent())
    {
        enumerator.MoveNext();
    }

    // Act.
    // Assert.
    EXPECT_THROW(enumerator.GetCurrent(), FinishedEnumeratorException);
}

TEST(ExceptBy, SourceThrowsOnMoveNext_CustomComparer)
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
    const string except[]
    {
        "thomas",
        "robert",
        "joseph",
        "david",
        "richard"
    };

    const auto query = From(source).ExceptBy(From(except), [](const Customer& customer){ return customer.name; }, [](const string& value1, const string& value2){ return tolower(value1.front()) == tolower(value2.front()); });

    auto enumerator = query.GetEnumerator();
    while (enumerator.HasCurrent())
    {
        enumerator.MoveNext();
    }

    // Act.
    // Assert.
    EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
}

TEST(ExceptBy, SourceThrowsOnGetCurrent_CustomComparer)
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
    const string except[]
    {
        "thomas",
        "robert",
        "joseph",
        "david",
        "richard"
    };

    const auto query = From(source).ExceptBy(From(except), [](const Customer& customer){ return customer.name; }, [](const string& value1, const string& value2){ return tolower(value1.front()) == tolower(value2.front()); });

    auto enumerator = query.GetEnumerator();
    while (enumerator.HasCurrent())
    {
        enumerator.MoveNext();
    }

    // Act.
    // Assert.
    EXPECT_THROW(enumerator.GetCurrent(), FinishedEnumeratorException);
}