#include <cctype>

#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq::Exceptions;
using namespace std;

namespace CppLinq::Tests::Distinct
{
    TEST(Distinct_enumerator_with_comparer, Throws_on_move_next_if_enumerator_is_finished)
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
        const auto action = [&enumerator](){ enumerator.MoveNext(); };

        // Assert.
        EXPECT_THROW(action(), FinishedEnumeratorException);
    }

    TEST(Distinct_enumerator_with_comparer, Throws_on_get_current_if_enumerator_is_finished)
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
        const auto action = [&enumerator](){ enumerator.GetCurrent(); };

        // Assert.
        EXPECT_THROW(action(), FinishedEnumeratorException);
    }
}