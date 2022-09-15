#include <cctype>

#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace CppLinq::Exceptions;

TEST(Union, ReturnsExpectedValues_DefaultComparer)
{
    // Arrange.
    const int source1[]{ 'c', 'C', 'd', 'a', 'b', 'b', 'c', 'D', 'h', 'B' };
    const int source2[]{ 'i', 'A', 'a', 'g', 'i', 'b', 'c', 'd', 'd', 'e', 'f' };
    const int expected[]{ 'c', 'C', 'd', 'a', 'b', 'D', 'h', 'B', 'i', 'A', 'g', 'e', 'f' };

    const auto query1 = From(source1);
    const auto query2 = From(source2);

    // Act.
    const auto actual = query1.Union(query2);

    // Assert.
    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(Union, ReturnsExpectedValues_CustomComparer)
{
    // Arrange.
    const int source1[]{ 'c', 'C', 'd', 'a', 'b', 'b', 'c', 'D', 'h', 'B' };
    const int source2[]{ 'i', 'A', 'a', 'g', 'i', 'b', 'c', 'd', 'd', 'e', 'f' };
    const int expected[]{ 'c', 'd', 'a', 'b', 'h', 'i', 'g', 'e', 'f' };

    const auto query1 = From(source1);
    const auto query2 = From(source2);

    // Act.
    const auto actual = query1.Union(query2, [](const int value1, const int value2){ return tolower(value1) == tolower(value2); });

    // Assert.
    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(Union, ReturnsSameResults_DefaultComparer)
{
    // Arrange.
    const int source1[]{ 'c', 'C', 'd', 'a', 'b', 'b', 'c', 'D', 'h', 'B' };
    const int source2[]{ 'i', 'A', 'a', 'g', 'i', 'b', 'c', 'd', 'd', 'e', 'f' };

    const auto query1 = From(source1);
    const auto query2 = From(source2);

    // Act.
    const auto actual1 = query1.Union(query2);
    const auto actual2 = query1.Union(query2);

    // Assert.
    ExpectSequencesAreEquivalent(actual1, actual2);
}

TEST(Union, ReturnsSameResults_CustomComparer)
{
    // Arrange.
    const int source1[]{ 'c', 'C', 'd', 'a', 'b', 'b', 'c', 'D', 'h', 'B' };
    const int source2[]{ 'i', 'A', 'a', 'g', 'i', 'b', 'c', 'd', 'd', 'e', 'f' };

    const auto query1 = From(source1);
    const auto query2 = From(source2);

    // Act.
    const auto actual1 = query1.Union(query2, [](const int value1, const int value2){ return tolower(value1) == tolower(value2); });
    const auto actual2 = query1.Union(query2, [](const int value1, const int value2){ return tolower(value1) == tolower(value2); });

    // Assert.
    ExpectSequencesAreEquivalent(actual1, actual2);
}

TEST(Union, SourceThrowsOnMoveNext_DefaultComparer)
{
    // Arrange.
    const int source1[]{ 'c', 'C', 'd', 'a', 'b', 'b', 'c', 'D', 'h', 'B' };
    const int source2[]{ 'i', 'A', 'a', 'g', 'i', 'b', 'c', 'd', 'd', 'e', 'f' };

    const auto query = From(source1).Union(From(source2));

    auto enumerator = query.GetEnumerator();
    while (enumerator.HasCurrent())
    {
        enumerator.MoveNext();
    }

    // Act.
    // Assert.
    EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
}

TEST(Union, SourceThrowsOnGetCurrent_DefaultComparer)
{
    // Arrange.
    const int source1[]{ 'c', 'C', 'd', 'a', 'b', 'b', 'c', 'D', 'h', 'B' };
    const int source2[]{ 'i', 'A', 'a', 'g', 'i', 'b', 'c', 'd', 'd', 'e', 'f' };

    const auto query = From(source1).Union(From(source2));

    auto enumerator = query.GetEnumerator();
    while (enumerator.HasCurrent())
    {
        enumerator.MoveNext();
    }

    // Act.
    // Assert.
    EXPECT_THROW(enumerator.GetCurrent(), FinishedEnumeratorException);
}

TEST(Union, SourceThrowsOnMoveNext_CustomComparer)
{
    // Arrange.
    const int source1[]{ 'c', 'C', 'd', 'a', 'b', 'b', 'c', 'D', 'h', 'B' };
    const int source2[]{ 'i', 'A', 'a', 'g', 'i', 'b', 'c', 'd', 'd', 'e', 'f' };

    const auto query = From(source1).Union(From(source2), [](const int value1, const int value2){ return tolower(value1) == tolower(value2); });

    auto enumerator = query.GetEnumerator();
    while (enumerator.HasCurrent())
    {
        enumerator.MoveNext();
    }

    // Act.
    // Assert.
    EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
}

TEST(Union, SourceThrowsOnGetCurrent_CustomComparer)
{
    // Arrange.
    const int source1[]{ 'c', 'C', 'd', 'a', 'b', 'b', 'c', 'D', 'h', 'B' };
    const int source2[]{ 'i', 'A', 'a', 'g', 'i', 'b', 'c', 'd', 'd', 'e', 'f' };

    const auto query = From(source1).Union(From(source2), [](const int value1, const int value2){ return tolower(value1) == tolower(value2); });

    auto enumerator = query.GetEnumerator();
    while (enumerator.HasCurrent())
    {
        enumerator.MoveNext();
    }

    // Act.
    // Assert.
    EXPECT_THROW(enumerator.GetCurrent(), FinishedEnumeratorException);
}