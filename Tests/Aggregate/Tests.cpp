#include <string>
#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq::Exceptions;
using namespace std;

namespace CppLinq::Tests::Aggregate
{
    TEST(Aggregate, ReturnsAggregatedValue_NoSeed_SourceContainsOneElement)
    {
        // Arrange.
        const int source[]{ 1 };
        const auto expected = 1;

        // Act.
        const auto actual = From(source).Aggregate([](const int x, const int y){ return x + y; });

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Aggregate, ReturnsAggregatedValue_NoSeed_SourceContainsTwoElements)
    {
        // Arrange.
        const int source[]{ 1, 2 };
        const auto expected = 3;

        // Act.
        const auto actual = From(source).Aggregate([](const int x, const int y){ return x + y; });

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Aggregate, ReturnsAggregatedValue_NoSeed_SourceContainsThreeElements)
    {
        // Arrange.
        const int source[]{ 1, 2, 3 };
        const auto expected = 6;

        // Act.
        const auto actual = From(source).Aggregate([](const int x, const int y){ return x + y; });

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Aggregate, ReturnsAggregatedValue_Seed_SourceIsEmpty)
    {
        // Arrange.
        const vector<int> source;
        const auto expected = "5";

        // Act.
        const auto actual = From(source).Aggregate(string("5"), [](const string& x, const int y){ return x + to_string(y); });

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Aggregate, ReturnsAggregatedValue_Seed_SourceContainsOneElement)
    {
        // Arrange.
        const int source[]{ 1 };
        const auto expected = "51";

        // Act.
        const auto actual = From(source).Aggregate(string("5"), [](const string& x, const int y){ return x + to_string(y); });

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Aggregate, ReturnsAggregatedValue_Seed_SourceContainsTwoElements)
    {
        // Arrange.
        const int source[]{ 1, 2 };
        const auto expected = "512";

        // Act.
        const auto actual = From(source).Aggregate(string("5"), [](const string& x, const int y){ return x + to_string(y); });

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Aggregate, ReturnsAggregatedValue_Seed_SourceContainsThreeElements)
    {
        // Arrange.
        const int source[]{ 1, 2, 3 };
        const auto expected = "5123";

        // Act.
        const auto actual = From(source).Aggregate(string("5"), [](const string& x, const int y){ return x + to_string(y); });

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Aggregate, ReturnsAggregatedValue_ResultSelector_SourceIsEmpty)
    {
        // Arrange.
        const vector<int> source;
        const auto expected = 10;

        // Act.
        const auto actual = From(source).Aggregate(string("5"), [](const string& x, const int y){ return x + to_string(y); }, [](const string& x){ return stoi(x) + 5; });

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Aggregate, ReturnsAggregatedValue_ResultSelector_SourceContainsOneElement)
    {
        // Arrange.
        const int source[]{ 1 };
        const auto expected = 56;

        // Act.
        const auto actual = From(source).Aggregate(string("5"), [](const string& x, const int y){ return x + to_string(y); }, [](const string& x){ return stoi(x) + 5; });

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Aggregate, ReturnsAggregatedValue_ResultSelector_SourceContainsTwoElements)
    {
        // Arrange.
        const int source[]{ 1, 2 };
        const auto expected = 517;

        // Act.
        const auto actual = From(source).Aggregate(string("5"), [](const string& x, const int y){ return x + to_string(y); }, [](const string& x){ return stoi(x) + 5; });

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Aggregate, ReturnsAggregatedValue_ResultSelector_SourceContainsThreeElements)
    {
        // Arrange.
        const int source[]{ 1, 2, 3 };
        const auto expected = 5128;

        // Act.
        const auto actual = From(source).Aggregate(string("5"), [](const string& x, const int y){ return x + to_string(y); }, [](const string& x){ return stoi(x) + 5; });

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Aggregate, ReturnsSameResults_NoSeed)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5 };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.Aggregate([](const int x, const int y){ return x + y; });
        const auto actual2 = query.Aggregate([](const int x, const int y){ return x + y; });

        // Assert.
        EXPECT_EQ(actual1, actual2);
    }

    TEST(Aggregate, ReturnsSameResults_Seed)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5 };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.Aggregate(string("5"), [](const string& x, const int y){ return x + to_string(y); });
        const auto actual2 = query.Aggregate(string("5"), [](const string& x, const int y){ return x + to_string(y); });

        // Assert.
        EXPECT_EQ(actual1, actual2);
    }

    TEST(Aggregate, ReturnsSameResults_ResultSelector)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5 };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.Aggregate(string("5"), [](const string& x, const int y){ return x + to_string(y); }, [](const string& x){ return stoi(x) + 5; });
        const auto actual2 = query.Aggregate(string("5"), [](const string& x, const int y){ return x + to_string(y); }, [](const string& x){ return stoi(x) + 5; });

        // Assert.
        EXPECT_EQ(actual1, actual2);
    }

    TEST(Aggregate, ThrowsOnMaximum_NoSeed_SourceIsEmpty)
    {
        // Arrange.
        const vector<int> source;

        const auto query = From(source);

        // Act.
        // Assert.
        EXPECT_THROW(query.Aggregate([](const int x, const int y){ return x + y; }), EmptyContainerException);
    }
}