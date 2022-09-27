#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq::Exceptions;

namespace CppLinq::Tests::Concatenate
{
    TEST(Concatenate_enumerator, Throws_on_move_next_if_enumerator_is_finished)
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

    TEST(Concatenate_enumerator, Throws_on_get_current_if_enumerator_is_finished)
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