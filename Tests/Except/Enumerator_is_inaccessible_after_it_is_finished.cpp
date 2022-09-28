#include <cctype>
#include <string>

#include "Assertions.hpp"
#include "CppLinq.hpp"
#include "Except/Stubs/Customer.hpp"

using namespace CppLinq::Exceptions;
using namespace CppLinq::Tests::Except::Stubs;
using namespace std;

namespace CppLinq::Tests::Except
{
    TEST(Enumerator_is_inaccessible_after_it_is_finished, Throws_on_move_next)
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
        const auto action = [&enumerator](){ enumerator.MoveNext(); };

        // Assert.
        EXPECT_THROW(action(), FinishedEnumeratorException);
    }

    TEST(Enumerator_is_inaccessible_after_it_is_finished, Throws_on_get_current)
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
        const auto action = [&enumerator](){ enumerator.GetCurrent(); };

        // Assert.
        EXPECT_THROW(action(), FinishedEnumeratorException);
    }
}