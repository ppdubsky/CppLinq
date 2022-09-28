#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq::Exceptions;

namespace CppLinq::Tests::Concatenate
{
    TEST(Enumerator_is_inaccessible_after_it_is_finished, Throws_on_move_next)
    {
        // Arrange.
        const int source1[]{ 1, 2, 3, 4, 5 };
        const int source2[]{ 6, 7, 8, 9, 10 };

        const auto query = From(source1).Concatenate(From(source2));

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
        const int source1[]{ 1, 2, 3, 4, 5 };
        const int source2[]{ 6, 7, 8, 9, 10 };

        const auto query = From(source1).Concatenate(From(source2));

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