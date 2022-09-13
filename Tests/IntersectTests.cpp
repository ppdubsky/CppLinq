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

struct IntersectEquatable final
{
    auto EqualTo(const IntersectEquatable other) const -> bool
    {
        ++equalityCount;

        return value == other.value;
    }

    auto operator==(const IntersectEquatable right) const -> bool
    {
        return EqualTo(right);
    }

    static uint32_t equalityCount;

    uint32_t value;
};

uint32_t IntersectEquatable::equalityCount = 0U;

TEST(Intersect, ExecutionIsDeferred_DefaultComparer)
{
    // Arrange.
    IntersectEquatable::equalityCount = 0U;

    const IntersectEquatable source[]{ 'a', 'b', 'c', 'd', 'e' };
    const IntersectEquatable intersect[]{ 'b', 'd', 'e', 'f', 'g' };

    // Act.
    const auto actual = From(source).Intersect(From(intersect));

    // Assert.
    EXPECT_EQ(IntersectEquatable::equalityCount, 0U);
}

TEST(Intersect, ExecutionIsDeferred_CustomComparer)
{
    // Arrange.
    IntersectEquatable::equalityCount = 0U;

    const IntersectEquatable source[]{ 'a', 'b', 'c', 'd', 'e' };
    const IntersectEquatable intersect[]{ 'b', 'd', 'e', 'f', 'g' };

    // Act.
    const auto actual = From(source).Intersect(From(intersect), [](const IntersectEquatable value1, const IntersectEquatable value2){ return value1.EqualTo(value2); });

    // Assert.
    EXPECT_EQ(IntersectEquatable::equalityCount, 0U);
}

TEST(Intersect, ReturnsExpectedValues_DefaultComparer)
{
    // Arrange.
    const int source[]{ 'a', 'b', 'c', 'd', 'e' };
    const int intersect[]{ 'b', 'd', 'e', 'f', 'g' };
    const int expected[]{ 'b', 'd', 'e' };

    // Act.
    const auto actual = From(source).Intersect(From(intersect));

    // Assert.
    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(Intersect, ReturnsExpectedValues_CustomComparer)
{
    // Arrange.
    const int source[]{ 'a', 'b', 'c', 'd', 'e' };
    const int intersect[]{ 'B', 'D', 'E', 'F', 'G' };
    const int expected[]{ 'b', 'd', 'e' };

    // Act.
    const auto actual = From(source).Intersect(From(intersect), [](const int value1, const int value2){ return tolower(value1) == tolower(value2); });

    // Assert.
    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(Intersect, ReturnsSameResults_DefaultComparer)
{
    // Arrange.
    const int source[]{ 'a', 'b', 'c', 'd', 'e' };
    const int intersect[]{ 'b', 'd', 'e', 'f', 'g' };

    const auto query = From(source);

    // Act.
    const auto actual1 = query.Intersect(From(intersect));
    const auto actual2 = query.Intersect(From(intersect));

    // Assert.
    ExpectSequencesAreEquivalent(actual1, actual2);
}

TEST(Intersect, ReturnsSameResults_CustomComparer)
{
    // Arrange.
    const int source[]{ 'a', 'b', 'c', 'd', 'e' };
    const int intersect[]{ 'B', 'D', 'E', 'F', 'G' };

    const auto query = From(source);

    // Act.
    const auto actual1 = query.Intersect(From(intersect), [](const int value1, const int value2){ return tolower(value1) == tolower(value2); });
    const auto actual2 = query.Intersect(From(intersect), [](const int value1, const int value2){ return tolower(value1) == tolower(value2); });

    // Assert.
    ExpectSequencesAreEquivalent(actual1, actual2);
}

TEST(Intersect, SourceThrowsOnMoveNext_DefaultComparer)
{
    // Arrange.
    const int source[]{ 'a', 'b', 'c', 'd', 'e' };
    const int intersect[]{ 'b', 'd', 'e', 'f', 'g' };

    const auto query = From(source).Intersect(From(intersect));

    auto enumerator = query.GetEnumerator();
    while (enumerator.HasCurrent())
    {
        enumerator.MoveNext();
    }

    // Act.
    // Assert.
    EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
}

TEST(Intersect, SourceThrowsOnGetCurrent_DefaultComparer)
{
    // Arrange.
    const int source[]{ 'a', 'b', 'c', 'd', 'e' };
    const int intersect[]{ 'b', 'd', 'e', 'f', 'g' };

    const auto query = From(source).Intersect(From(intersect));

    auto enumerator = query.GetEnumerator();
    while (enumerator.HasCurrent())
    {
        enumerator.MoveNext();
    }

    // Act.
    // Assert.
    EXPECT_THROW(enumerator.GetCurrent(), FinishedEnumeratorException);
}

TEST(Intersect, SourceThrowsOnMoveNext_CustomComparer)
{
    // Arrange.
    const int source[]{ 'a', 'b', 'c', 'd', 'e' };
    const int intersect[]{ 'B', 'D', 'E', 'F', 'G' };

    const auto query = From(source).Intersect(From(intersect), [](const int value1, const int value2){ return tolower(value1) == tolower(value2); });

    auto enumerator = query.GetEnumerator();
    while (enumerator.HasCurrent())
    {
        enumerator.MoveNext();
    }

    // Act.
    // Assert.
    EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
}

TEST(Intersect, SourceThrowsOnGetCurrent_CustomComparer)
{
    // Arrange.
    const int source[]{ 'a', 'b', 'c', 'd', 'e' };
    const int intersect[]{ 'B', 'D', 'E', 'F', 'G' };

    const auto query = From(source).Intersect(From(intersect), [](const int value1, const int value2){ return tolower(value1) == tolower(value2); });

    auto enumerator = query.GetEnumerator();
    while (enumerator.HasCurrent())
    {
        enumerator.MoveNext();
    }

    // Act.
    // Assert.
    EXPECT_THROW(enumerator.GetCurrent(), FinishedEnumeratorException);
}