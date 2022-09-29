#include <cctype>

#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq::Exceptions;
using namespace std;

namespace CppLinq::Tests::Union
{
    TEST(Enumerator_is_inaccessible_after_it_is_finished_using_comparer, Throws_on_move_next)
    {
        // Arrange.
        const int source1[]{ 'c', 'C', 'd', 'a', 'b', 'b', 'c', 'D', 'h', 'B' };
        const int source2[]{ 'i', 'A', 'a', 'g', 'i', 'b', 'c', 'd', 'd', 'e', 'f' };

        const auto query = From(source1).Union(
            From(source2),
            [](const int value1, const int value2){ return tolower(value1) == tolower(value2); }
        );

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

    TEST(Enumerator_is_inaccessible_after_it_is_finished_using_comparer, Throws_on_get_current)
    {
        // Arrange.
        const int source1[]{ 'c', 'C', 'd', 'a', 'b', 'b', 'c', 'D', 'h', 'B' };
        const int source2[]{ 'i', 'A', 'a', 'g', 'i', 'b', 'c', 'd', 'd', 'e', 'f' };

        const auto query = From(source1).Union(
            From(source2),
            [](const int value1, const int value2){ return tolower(value1) == tolower(value2); }
        );

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