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

struct DistinctByEquatable final
{
    auto EqualTo(const DistinctByEquatable other) const -> bool
    {
        ++equalityCount;

        return value == other.value;
    }

    auto operator==(const DistinctByEquatable right) const -> bool
    {
        return EqualTo(right);
    }

    static uint32_t equalityCount;

    uint32_t value;
};

uint32_t DistinctByEquatable::equalityCount = 0U;

TEST(DistinctBy, ExecutionIsDeferred_DefaultComparer)
{
    // Arrange.
    DistinctByEquatable::equalityCount = 0U;

    const DistinctByEquatable source[]{ 'a', 'b', 'c', 'd', 'e' };

    // Act.
    const auto actual = From(source).DistinctBy([](const DistinctByEquatable value){ return value; });

    // Assert.
    EXPECT_EQ(DistinctByEquatable::equalityCount, 0U);
}

TEST(DistinctBy, ExecutionIsDeferred_CustomComparer)
{
    // Arrange.
    DistinctByEquatable::equalityCount = 0U;

    const DistinctByEquatable source[]{ 'a', 'b', 'c', 'd', 'e' };

    // Act.
    const auto actual = From(source).DistinctBy([](const DistinctByEquatable value){ return value; }, [](const DistinctByEquatable value1, const DistinctByEquatable value2){ return value1.EqualTo(value2); });

    // Assert.
    EXPECT_EQ(DistinctByEquatable::equalityCount, 0U);
}

TEST(DistinctBy, ReturnsExpectedValues_DefaultComparer_SourceContainsDistinctElements)
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
    const Customer expected[]
    {
        { 1U, "James" },
        { 2U, "Robert" },
        { 3U, "John" },
        { 4U, "Michael" },
        { 5U, "David" },
        { 6U, "William" }
    };

    // Act.
    const auto actual = From(source).DistinctBy([](const Customer& customer){ return customer.name; });

    // Assert.
    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(DistinctBy, ReturnsExpectedValues_DefaultComparer_SourceContainsDuplicateElements)
{
    // Arrange.
    const Customer source[]
    {
        { 1U, "James" },
        { 2U, "Robert" },
        { 3U, "Robert" },
        { 4U, "John" },
        { 5U, "John" },
        { 6U, "Michael" },
        { 7U, "David" },
        { 8U, "David" },
        { 9U, "William" }
    };
    const Customer expected[]
    {
        { 1U, "James" },
        { 2U, "Robert" },
        { 4U, "John" },
        { 6U, "Michael" },
        { 7U, "David" },
        { 9U, "William" }
    };

    // Act.
    const auto actual = From(source).DistinctBy([](const Customer& customer){ return customer.name; });

    // Assert.
    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(DistinctBy, ReturnsExpectedValues_CustomComparer_SourceContainsDistinctElements)
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
    const Customer expected[]
    {
        { 1U, "James" },
        { 2U, "Robert" },
        { 4U, "Michael" },
        { 5U, "David" },
        { 6U, "William" }
    };

    // Act.
    const auto actual = From(source).DistinctBy([](const Customer& customer){ return customer.name; }, [](const string& value1, const string& value2){ return tolower(value1.front()) == tolower(value2.front()); });

    // Assert.
    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(DistinctBy, ReturnsExpectedValues_CustomComparer_SourceContainsDuplicateElements)
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
    const Customer expected[]
    {
        { 1U, "James" },
        { 2U, "Robert" },
        { 6U, "Michael" },
        { 7U, "David" },
        { 9U, "William" }
    };

    // Act.
    const auto actual = From(source).DistinctBy([](const Customer& customer){ return customer.name; }, [](const string& value1, const string& value2){ return tolower(value1.front()) == tolower(value2.front()); });

    // Assert.
    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(DistinctBy, ReturnsSameResults_DefaultComparer)
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

    const auto query = From(source);

    // Act.
    const auto actual1 = query.DistinctBy([](const Customer& customer){ return customer.name; });
    const auto actual2 = query.DistinctBy([](const Customer& customer){ return customer.name; });

    // Assert.
    ExpectSequencesAreEquivalent(actual1, actual2);
}

TEST(DistinctBy, ReturnsSameResults_CustomComparer)
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

    const auto query = From(source);

    // Act.
    const auto actual1 = query.DistinctBy([](const Customer& customer){ return customer.name; }, [](const string& value1, const string& value2){ return tolower(value1.front()) == tolower(value2.front()); });
    const auto actual2 = query.DistinctBy([](const Customer& customer){ return customer.name; }, [](const string& value1, const string& value2){ return tolower(value1.front()) == tolower(value2.front()); });

    // Assert.
    ExpectSequencesAreEquivalent(actual1, actual2);
}

TEST(DistinctBy, SourceThrowsOnMoveNext_DefaultComparer)
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

    const auto query = From(source).DistinctBy([](const Customer& customer){ return customer.name; });

    auto enumerator = query.GetEnumerator();
    while (enumerator.HasCurrent())
    {
        enumerator.MoveNext();
    }

    // Act.
    // Assert.
    EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
}

TEST(DistinctBy, SourceThrowsOnGetCurrent_DefaultComparer)
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

    const auto query = From(source).DistinctBy([](const Customer& customer){ return customer.name; });

    auto enumerator = query.GetEnumerator();
    while (enumerator.HasCurrent())
    {
        enumerator.MoveNext();
    }

    // Act.
    // Assert.
    EXPECT_THROW(enumerator.GetCurrent(), FinishedEnumeratorException);
}

TEST(DistinctBy, SourceThrowsOnMoveNext_CustomComparer)
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

    const auto query = From(source).DistinctBy([](const Customer& customer){ return customer.name; }, [](const string& value1, const string& value2){ return tolower(value1.front()) == tolower(value2.front()); });

    auto enumerator = query.GetEnumerator();
    while (enumerator.HasCurrent())
    {
        enumerator.MoveNext();
    }

    // Act.
    // Assert.
    EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
}

TEST(DistinctBy, SourceThrowsOnGetCurrent_CustomComparer)
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

    const auto query = From(source).DistinctBy([](const Customer& customer){ return customer.name; }, [](const string& value1, const string& value2){ return tolower(value1.front()) == tolower(value2.front()); });

    auto enumerator = query.GetEnumerator();
    while (enumerator.HasCurrent())
    {
        enumerator.MoveNext();
    }

    // Act.
    // Assert.
    EXPECT_THROW(enumerator.GetCurrent(), FinishedEnumeratorException);
}