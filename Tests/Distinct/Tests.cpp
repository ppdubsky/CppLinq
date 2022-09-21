#include <cctype>

#include "Assertions.hpp"
#include "CppLinq.hpp"
#include "Distinct/Equatable.hpp"

using namespace CppLinq::Exceptions;
using namespace std;

namespace CppLinq::Tests::Distinct
{
    TEST(Distinct, ExecutionIsDeferred_DefaultComparer)
    {
        // Arrange.
        Equatable::equalityCount = 0U;

        const Equatable source[]{ 'a', 'b', 'c', 'd', 'e' };

        // Act.
        const auto actual = From(source).Distinct();

        // Assert.
        EXPECT_EQ(Equatable::equalityCount, 0U);
    }

    TEST(Distinct, ExecutionIsDeferred_CustomComparer)
    {
        // Arrange.
        Equatable::equalityCount = 0U;

        const Equatable source[]{ 'a', 'b', 'c', 'd', 'e' };

        // Act.
        const auto actual = From(source).Distinct([](const Equatable value1, const Equatable value2){ return value1.EqualTo(value2); });

        // Assert.
        EXPECT_EQ(Equatable::equalityCount, 0U);
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
}