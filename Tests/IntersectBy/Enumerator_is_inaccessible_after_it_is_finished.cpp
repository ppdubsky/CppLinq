#include <string>

#include "Assertions.hpp"
#include "CppLinq.hpp"
#include "IntersectBy/Stubs/Customer.hpp"

using namespace CppLinq::Exceptions;
using namespace CppLinq::Tests::IntersectBy::Stubs;
using namespace std;

namespace CppLinq::Tests::IntersectBy
{
    TEST(Enumerator_is_inaccessible_after_it_is_finished, Throws_on_move_next)
    {
        // Arrange.
        const Customer source[]
        {
            { 1U, "James" },
            { 2U, "Robert" },
            { 3U, "John" },
            { 4U, "Michael" },
            { 5U, "David" },
            { 6U, "William" }
        };
        const string intersect[]
        {
            "Thomas",
            "Robert",
            "Joseph",
            "David",
            "Richard"
        };

        const auto query = From(source).IntersectBy(
            From(intersect),
            [](const Customer& customer){ return customer.name; }
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
        const Customer source[]
        {
            { 1U, "James" },
            { 2U, "Robert" },
            { 3U, "John" },
            { 4U, "Michael" },
            { 5U, "David" },
            { 6U, "William" }
        };
        const string intersect[]
        {
            "Thomas",
            "Robert",
            "Joseph",
            "David",
            "Richard"
        };

        const auto query = From(source).IntersectBy(
            From(intersect),
            [](const Customer& customer){ return customer.name; }
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