#include <cctype>

#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace CppLinq::Exceptions;
using namespace std;

struct DistinctEquatable final
{
    auto EqualTo(const DistinctEquatable other) const -> bool
    {
        ++equalityCount;

        return value == other.value;
    }

    auto operator==(const DistinctEquatable right) const -> bool
    {
        return EqualTo(right);
    }

    static uint32_t equalityCount;

    uint32_t value;
};

uint32_t DistinctEquatable::equalityCount = 0U;

TEST(Distinct, ExecutionIsDeferred_DefaultComparer)
{
    // Arrange.
    DistinctEquatable::equalityCount = 0U;

    const DistinctEquatable source[]{ 'a', 'b', 'c', 'd', 'e' };

    // Act.
    const auto actual = From(source).Distinct();

    // Assert.
    EXPECT_EQ(DistinctEquatable::equalityCount, 0U);
}

TEST(Distinct, ExecutionIsDeferred_CustomComparer)
{
    // Arrange.
    DistinctEquatable::equalityCount = 0U;

    const DistinctEquatable source[]{ 'a', 'b', 'c', 'd', 'e' };

    // Act.
    const auto actual = From(source).Distinct([](const DistinctEquatable value1, const DistinctEquatable value2){ return value1.EqualTo(value2); });

    // Assert.
    EXPECT_EQ(DistinctEquatable::equalityCount, 0U);
}

TEST(Distinct, ReturnsExpectedValues_DefaultComparer_SourceContainsDistinctElements)
{
    // Arrange.
    const int source[]{ 'a', 'b', 'c', 'd', 'e' };
    const int expected[]{ 'a', 'b', 'c', 'd', 'e'  };

    // Act.
    const auto actual = From(source).Distinct();

    // Assert.
    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(Distinct, ReturnsExpectedValues_DefaultComparer_SourceContainsDuplicateElements)
{
    // Arrange.
    const int source[]{ 'a', 'a', 'b', 'b', 'c', 'c', 'd', 'd', 'e', 'e' };
    const int expected[]{ 'a', 'b', 'c', 'd', 'e'  };

    // Act.
    const auto actual = From(source).Distinct();

    // Assert.
    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(Distinct, ReturnsExpectedValues_CustomComparer_SourceContainsDistinctElements)
{
    // Arrange.
    const int source[]{ 'a', 'b', 'c', 'd', 'e' };
    const int expected[]{ 'a', 'b', 'c', 'd', 'e'  };

    // Act.
    const auto actual = From(source).Distinct([](const int value1, const int value2){ return tolower(value1) == tolower(value2); });

    // Assert.
    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(Distinct, ReturnsExpectedValues_CustomComparer_SourceContainsDuplicateElements)
{
    // Arrange.
    const int source[]{ 'a', 'A', 'b', 'B', 'c', 'C', 'd', 'D', 'e', 'E' };
    const int expected[]{ 'a', 'b', 'c', 'd', 'e'  };

    // Act.
    const auto actual = From(source).Distinct([](const int value1, const int value2){ return tolower(value1) == tolower(value2); });

    // Assert.
    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(Distinct, ReturnsSameResults_DefaultComparer)
{
    // Arrange.
    const int source[]{ 'a', 'b', 'c', 'd', 'e' };

    const auto query = From(source);

    // Act.
    const auto actual1 = query.Distinct();
    const auto actual2 = query.Distinct();

    // Assert.
    ExpectSequencesAreEquivalent(actual1, actual2);
}

TEST(Distinct, ReturnsSameResults_CustomComparer)
{
    // Arrange.
    const int source[]{ 'a', 'A', 'b', 'B', 'c', 'C', 'd', 'D', 'e', 'E' };

    const auto query = From(source);

    // Act.
    const auto actual1 = query.Distinct([](const int value1, const int value2){ return tolower(value1) == tolower(value2); });
    const auto actual2 = query.Distinct([](const int value1, const int value2){ return tolower(value1) == tolower(value2); });

    // Assert.
    ExpectSequencesAreEquivalent(actual1, actual2);
}

TEST(Distinct, SourceThrowsOnMoveNext_DefaultComparer)
{
    // Arrange.
    const int source[]{ 'a', 'b', 'c', 'd', 'e' };

    const auto query = From(source).Distinct();

    auto enumerator = query.GetEnumerator();
    while (enumerator.HasCurrent())
    {
        enumerator.MoveNext();
    }

    // Act.
    // Assert.
    EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
}

TEST(Distinct, SourceThrowsOnGetCurrent_DefaultComparer)
{
    // Arrange.
    const int source[]{ 'a', 'b', 'c', 'd', 'e' };

    const auto query = From(source).Distinct();

    auto enumerator = query.GetEnumerator();
    while (enumerator.HasCurrent())
    {
        enumerator.MoveNext();
    }

    // Act.
    // Assert.
    EXPECT_THROW(enumerator.GetCurrent(), FinishedEnumeratorException);
}

TEST(Distinct, SourceThrowsOnMoveNext_CustomComparer)
{
    // Arrange.
    const int source[]{ 'a', 'A', 'b', 'B', 'c', 'C', 'd', 'D', 'e', 'E' };

    const auto query = From(source).Distinct([](const int value1, const int value2){ return tolower(value1) == tolower(value2); });

    auto enumerator = query.GetEnumerator();
    while (enumerator.HasCurrent())
    {
        enumerator.MoveNext();
    }

    // Act.
    // Assert.
    EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
}

TEST(Distinct, SourceThrowsOnGetCurrent_CustomComparer)
{
    // Arrange.
    const int source[]{ 'a', 'A', 'b', 'B', 'c', 'C', 'd', 'D', 'e', 'E' };

    const auto query = From(source).Distinct([](const int value1, const int value2){ return tolower(value1) == tolower(value2); });

    auto enumerator = query.GetEnumerator();
    while (enumerator.HasCurrent())
    {
        enumerator.MoveNext();
    }

    // Act.
    // Assert.
    EXPECT_THROW(enumerator.GetCurrent(), FinishedEnumeratorException);
}