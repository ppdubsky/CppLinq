#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq::Exceptions;

namespace CppLinq::Tests::Distinct
{
    TEST(Enumerator_is_inaccessible_after_it_is_finished, Throws_on_move_next)
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
        const auto action = [&enumerator](){ enumerator.MoveNext(); };

        // Assert.
        EXPECT_THROW(action(), FinishedEnumeratorException);
    }

    TEST(Enumerator_is_inaccessible_after_it_is_finished, Throws_on_get_current)
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
        const auto action = [&enumerator](){ enumerator.GetCurrent(); };

        // Assert.
        EXPECT_THROW(action(), FinishedEnumeratorException);
    }
}