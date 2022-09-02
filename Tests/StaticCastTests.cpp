#include <cstdint>
#include <functional>

#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace CppLinq::Exceptions;
using namespace std;

struct ConvertibleToInt final
{
    explicit operator int() const
    {
        ++castCount;

        return 0;
    }

    static uint32_t castCount;
};

uint32_t ConvertibleToInt::castCount = 0U;

TEST(StaticCast, ExecutionIsDeferred)
{
    ConvertibleToInt::castCount = 0U;

    const ConvertibleToInt source[] { {} };

    const auto actual = From(source).StaticCast<int>();

    EXPECT_EQ(ConvertibleToInt::castCount, 0U);
}

TEST(StaticCast, ReturnsExpectedValues_DoubleToInt)
{
    const double source[]{ 1.1, 2.2, 3.3, 4.4, 5.5 };
    const int expected[]{ 1, 2, 3, 4, 5 };

    const auto actual = From(source).StaticCast<int>();

    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(StaticCast, SourceThrowsOnMoveNext)
{
    const double source[]{ 1.1, 2.2, 3.3, 4.4, 5.5 };

    auto query = From(source).StaticCast<int>();

    auto& enumerator = query.GetEnumerator();
    while (!enumerator.IsFinished())
    {
        enumerator.MoveNext();
    }

    EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
}

TEST(StaticCast, SourceThrowsOnGetCurrent)
{
    const double source[]{ 1.1, 2.2, 3.3, 4.4, 5.5 };

    auto query = From(source).StaticCast<int>();

    auto& enumerator = query.GetEnumerator();
    while (!enumerator.IsFinished())
    {
        enumerator.MoveNext();
    }

    EXPECT_THROW(enumerator.GetCurrent(), FinishedEnumeratorException);
}