#include <cstdint>
#include <functional>
#include <string>
#include <vector>

#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace std;

struct Customer final
{
    uint32_t id;
    string name;
};

TEST(Select, ExecutionIsDeferred)
{
    auto isActionCalled = false;

    const function<void()> source[]
    {
        [&isActionCalled]() { isActionCalled = true; }
    };

    const auto actual = From(source).Select([](const function<void()> action) { action(); return action; });

    EXPECT_FALSE(isActionCalled);
}

TEST(Select, ReturnsExpectedValues_SelectTheSameValue)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const int expected[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    const auto actual = From(source).Select([](const int value){ return value; });

    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(Select, ReturnsExpectedValues_ConvertValueToString)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const string expected[]{ "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };

    const auto actual = From(source).Select([](const int value){ return to_string(value); });

    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(Select, ReturnsExpectedValues_SelectField)
{
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

    const auto actual = From(source).Select([](const Customer& customer){ return customer.name; });

    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(Select, ReturnsExpectedValues_EmptySource)
{
    const vector<Customer> source;

    const auto actual = From(source).Select([](const Customer& customer){ return customer.name; });

    ExpectSequenceIsEmpty(actual);
}

TEST(Select, ReturnsSameResults)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source);

    const auto actual1 = query.Select([](const int value){ return value * 2; });
    const auto actual2 = query.Select([](const int value){ return value * 2; });

    ExpectSequencesAreEquivalent(actual1, actual2);
}