#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq::Exceptions;

namespace CppLinq::Tests::Concatenate
{
    TEST(Concatenate, ReturnsExpectedValues_BothQueriesAreEmpty)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        const auto query = From(source);

        const auto subquery1 = query.Where([](const int /*value*/){ return false; });
        const auto subquery2 = query.Where([](const int /*value*/){ return false; });

        // Act.
        const auto actual = subquery1.Concatenate(subquery2);

        // Assert.
        ExpectSequenceIsEmpty(actual);
    }

    TEST(Concatenate, ReturnsExpectedValues_BothQueriesAreNotEmpty)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        const int expected[]{ 2, 4, 6, 8, 10, 1, 3, 5, 7, 9 };

        const auto query = From(source);

        const auto subquery1 = query.Where([](const int value){ return value % 2 == 0; });
        const auto subquery2 = query.Where([](const int value){ return value % 2 != 0; });

        // Act.
        const auto actual = subquery1.Concatenate(subquery2);

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Concatenate, ReturnsExpectedValues_OnlyFirstQueryIsEmpty)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        const int expected[]{ 1, 3, 5, 7, 9 };

        const auto query = From(source);

        const auto subquery1 = query.Where([](const int /*value*/){ return false; });
        const auto subquery2 = query.Where([](const int value){ return value % 2 != 0; });

        // Act.
        const auto actual = subquery1.Concatenate(subquery2);

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Concatenate, ReturnsExpectedValues_OnlySecondQueryIsEmpty)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        const int expected[]{ 2, 4, 6, 8, 10 };

        const auto query = From(source);

        const auto subquery1 = query.Where([](const int value){ return value % 2 == 0; });
        const auto subquery2 = query.Where([](const int /*value*/){ return false; });

        // Act.
        const auto actual = subquery1.Concatenate(subquery2);

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Concatenate, ReturnsSameResults)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        const auto query = From(source);

        const auto subquery1 = query.Where([](const int value){ return value % 2 == 0; });
        const auto subquery2 = query.Where([](const int value){ return value % 2 != 0; });

        // Act.
        const auto actual1 = subquery1.Concatenate(subquery2);
        const auto actual2 = subquery1.Concatenate(subquery2);

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }

    TEST(Concatenate, SourceThrowsOnMoveNext)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        const auto query = From(source).Concatenate(From(source));

        auto enumerator = query.GetEnumerator();
        while (enumerator.HasCurrent())
        {
            enumerator.MoveNext();
        }

        // Act.
        // Assert.
        EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
    }

    TEST(Concatenate, SourceThrowsOnGetCurrent)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        const auto query = From(source).Concatenate(From(source));

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