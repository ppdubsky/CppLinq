#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace CppLinq::Exceptions;

TEST(Concatenate, ReturnsExpectedValues_BothQueriesAreEmpty)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source);

    auto subquery1 = query.Where([](const int /*value*/){ return false; });
    auto subquery2 = query.Where([](const int /*value*/){ return false; });

    const auto actual = subquery1.Concatenate(subquery2);

    ExpectSequenceIsEmpty(actual);
}

TEST(Concatenate, ReturnsExpectedValues_BothQueriesAreNotEmpty)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const int expected[]{ 2, 4, 6, 8, 10, 1, 3, 5, 7, 9 };

    auto query = From(source);

    auto subquery1 = query.Where([](const int value){ return value % 2 == 0; });
    auto subquery2 = query.Where([](const int value){ return value % 2 != 0; });

    const auto actual = subquery1.Concatenate(subquery2);

    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(Concatenate, ReturnsExpectedValues_OnlyFirstQueryIsEmpty)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const int expected[]{ 1, 3, 5, 7, 9 };

    auto query = From(source);

    auto subquery1 = query.Where([](const int /*value*/){ return false; });
    auto subquery2 = query.Where([](const int value){ return value % 2 != 0; });

    const auto actual = subquery1.Concatenate(subquery2);

    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(Concatenate, ReturnsExpectedValues_OnlySecondQueryIsEmpty)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const int expected[]{ 2, 4, 6, 8, 10 };

    auto query = From(source);

    auto subquery1 = query.Where([](const int value){ return value % 2 == 0; });
    auto subquery2 = query.Where([](const int /*value*/){ return false; });

    const auto actual = subquery1.Concatenate(subquery2);

    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(Concatenate, SourceThrowsOnMoveNext)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source).Concatenate(From(source));

    auto& enumerator = query.GetEnumerator();
    while (!enumerator.IsFinished())
    {
        enumerator.MoveNext();
    }

    EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
}

TEST(Concatenate, SourceThrowsOnGetCurrent)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source).Concatenate(From(source));

    auto& enumerator = query.GetEnumerator();
    while (!enumerator.IsFinished())
    {
        enumerator.MoveNext();
    }

    EXPECT_THROW(enumerator.GetCurrent(), FinishedEnumeratorException);
}