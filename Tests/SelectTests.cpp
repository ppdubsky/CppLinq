#include <cstdint>
#include <functional>
#include <string>
#include <vector>

#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace CppLinq::Exceptions;
using namespace std;

struct Customer final
{
    uint32_t id;
    string name;
};

TEST(Select, ExecutionIsDeferred)
{
    // Arrange.
    auto isActionCalled = false;

    const function<void()> source[]
    {
        [&isActionCalled]() { isActionCalled = true; }
    };

    // Act.
    const auto actual = From(source).Select([](const function<void()> action) { action(); return action; });

    // Assert.
    EXPECT_FALSE(isActionCalled);
}

TEST(Select, ReturnsExpectedValues_SelectTheSameValue)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const int expected[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // Act.
    const auto actual = From(source).Select([](const int value){ return value; });

    // Assert.
    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(Select, ReturnsExpectedValues_ConvertValueToString)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const string expected[]{ "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };

    // Act.
    const auto actual = From(source).Select([](const int value){ return to_string(value); });

    // Assert.
    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(Select, ReturnsExpectedValues_SelectField)
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
    const string expected[]
    {
        "James",
        "Robert",
        "John",
        "Michael",
        "David",
        "William"
    };

    // Act.
    const auto actual = From(source).Select([](const Customer& customer){ return customer.name; });

    // Assert.
    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(Select, ReturnsExpectedValues_EmptySource)
{
    // Arrange.
    const vector<Customer> source;

    // Act.
    const auto actual = From(source).Select([](const Customer& customer){ return customer.name; });

    // Assert.
    ExpectSequenceIsEmpty(actual);
}

TEST(Select, ReturnsSameResults)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    const auto query = From(source);

    // Act.
    const auto actual1 = query.Select([](const int value){ return value * 2; });
    const auto actual2 = query.Select([](const int value){ return value * 2; });

    // Assert.
    ExpectSequencesAreEquivalent(actual1, actual2);
}

TEST(Select, SourceThrowsOnMoveNext)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    const auto query = From(source).Select([](const int value){ return value % 2 == 0; });

    auto enumerator = query.GetEnumerator();
    while (enumerator.HasCurrent())
    {
        enumerator.MoveNext();
    }

    // Act.
    // Assert.
    EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
}

TEST(Select, SourceThrowsOnGetCurrent)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    const auto query = From(source).Select([](const int value){ return value % 2 == 0; });

    auto enumerator = query.GetEnumerator();
    while (enumerator.HasCurrent())
    {
        enumerator.MoveNext();
    }

    // Act.
    // Assert.
    EXPECT_THROW(enumerator.GetCurrent(), FinishedEnumeratorException);
}