#include <string>

#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq::Exceptions;
using namespace std;

namespace CppLinq::Tests::Zip
{
    TEST(Enumerator_is_inaccessible_after_it_is_finished, Throws_on_move_next)
    {
        // Arrange.
        const double source1[]{ 1.1, 2.2, 3.3, 4.4, 5.5 };
        const int source2[]{ 'a', 'b', 'c', 'd', 'e' };

        const auto query = From(source1).Zip(
            From(source2),
            [](const double value1, const int value2){ return string(1U, static_cast<char>(value2)).append(1U, '0' + static_cast<char>(value1)); }
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

    TEST(Enumerator_is_inaccessible_after_it_is_finished, Throws_on_get_current)
    {
        // Arrange.
        const double source1[]{ 1.1, 2.2, 3.3, 4.4, 5.5 };
        const int source2[]{ 'a', 'b', 'c', 'd', 'e' };

        const auto query = From(source1).Zip(
            From(source2),
            [](const double value1, const int value2){ return string(1U, static_cast<char>(value2)).append(1U, '0' + static_cast<char>(value1)); }
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