#include <cctype>
#include <string>

#include "Assertions.hpp"
#include "CppLinq.hpp"
#include "Except/Customer.hpp"

using namespace CppLinq::Exceptions;
using namespace std;

namespace CppLinq::Tests::Except
{
    TEST(Except, ReturnsExpectedValues_DefaultComparer)
    {
        // Arrange.
        const int source[]{ 'a', 'b', 'c', 'd', 'e' };
        const int except[]{ 'b', 'd', 'e', 'f', 'g' };
        const int expected[]{ 'a', 'c' };

        // Act.
        const auto actual = From(source).Except(From(except));

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Except, ReturnsExpectedValues_CustomComparer)
    {
        // Arrange.
        const int source[]{ 'a', 'b', 'c', 'd', 'e' };
        const int except[]{ 'B', 'D', 'E', 'F', 'G' };
        const int expected[]{ 'a', 'c' };

        // Act.
        const auto actual = From(source).Except(From(except), [](const int value1, const int value2){ return tolower(value1) == tolower(value2); });

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Except, ReturnsSameResults_DefaultComparer)
    {
        // Arrange.
        const int source[]{ 'a', 'b', 'c', 'd', 'e' };
        const int except[]{ 'b', 'd', 'e', 'f', 'g' };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.Except(From(except));
        const auto actual2 = query.Except(From(except));

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }

    TEST(Except, ReturnsSameResults_CustomComparer)
    {
        // Arrange.
        const int source[]{ 'a', 'b', 'c', 'd', 'e' };
        const int except[]{ 'B', 'D', 'E', 'F', 'G' };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.Except(From(except), [](const int value1, const int value2){ return tolower(value1) == tolower(value2); });
        const auto actual2 = query.Except(From(except), [](const int value1, const int value2){ return tolower(value1) == tolower(value2); });

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }

    TEST(Except, SourceThrowsOnMoveNext_DefaultComparer)
    {
        // Arrange.
        const int source[]{ 'a', 'b', 'c', 'd', 'e' };
        const int except[]{ 'b', 'd', 'e', 'f', 'g' };

        const auto query = From(source).Except(From(except));

        auto enumerator = query.GetEnumerator();
        while (enumerator.HasCurrent())
        {
            enumerator.MoveNext();
        }

        // Act.
        // Assert.
        EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
    }

    TEST(Except, SourceThrowsOnGetCurrent_DefaultComparer)
    {
        // Arrange.
        const int source[]{ 'a', 'b', 'c', 'd', 'e' };
        const int except[]{ 'b', 'd', 'e', 'f', 'g' };

        const auto query = From(source).Except(From(except));

        auto enumerator = query.GetEnumerator();
        while (enumerator.HasCurrent())
        {
            enumerator.MoveNext();
        }

        // Act.
        // Assert.
        EXPECT_THROW(enumerator.GetCurrent(), FinishedEnumeratorException);
    }

    TEST(Except, SourceThrowsOnMoveNext_CustomComparer)
    {
        // Arrange.
        const int source[]{ 'a', 'b', 'c', 'd', 'e' };
        const int except[]{ 'B', 'D', 'E', 'F', 'G' };

        const auto query = From(source).Except(From(except), [](const int value1, const int value2){ return tolower(value1) == tolower(value2); });

        auto enumerator = query.GetEnumerator();
        while (enumerator.HasCurrent())
        {
            enumerator.MoveNext();
        }

        // Act.
        // Assert.
        EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
    }

    TEST(Except, SourceThrowsOnGetCurrent_CustomComparer)
    {
        // Arrange.
        const int source[]{ 'a', 'b', 'c', 'd', 'e' };
        const int except[]{ 'B', 'D', 'E', 'F', 'G' };

        const auto query = From(source).Except(From(except), [](const int value1, const int value2){ return tolower(value1) == tolower(value2); });

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