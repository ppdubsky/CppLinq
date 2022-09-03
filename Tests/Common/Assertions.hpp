#pragma once

#include <cstdint>
#include <format>
#include <type_traits>
#include <vector>

#include <gtest/gtest.h>

template <typename TActualIteratorBegin, typename TActualIteratorEnd, typename TExpectedIteratorBegin, typename TExpectedIteratorEnd>
void ExpectSequencesAreEquivalent(const TActualIteratorBegin actualBegin, const TActualIteratorEnd actualEnd, const TExpectedIteratorBegin expectedBegin, const TExpectedIteratorEnd expectedEnd)
{
    TActualIteratorBegin actualSequenceCurrent = actualBegin;
    TExpectedIteratorBegin expectedSequenceCurrent = expectedBegin;

    std::uint32_t index = 0U;

    while (actualSequenceCurrent != actualEnd && expectedSequenceCurrent != expectedEnd)
    {
        const auto actual = *actualSequenceCurrent;
        const auto expected = *expectedSequenceCurrent;

        EXPECT_EQ(actual, expected) << std::format("Elements are not equal at index {}.", index);

        ++actualSequenceCurrent;
        ++expectedSequenceCurrent;

        ++index;
    }

    const bool isActualSequenceFinished = actualSequenceCurrent == actualEnd;
    EXPECT_TRUE(isActualSequenceFinished) << "Actual sequence is longer than the expected one.";

    const bool isExpectedSequenceFinished = expectedSequenceCurrent == expectedEnd;
    EXPECT_TRUE(isExpectedSequenceFinished) << "Expected sequence is longer than the actual one.";
}

template <typename TActualQuery, typename TExpectedIteratorBegin, typename TExpectedIteratorEnd>
void ExpectSequencesAreEquivalent(const TActualQuery& actual, const TExpectedIteratorBegin expectedBegin, const TExpectedIteratorEnd expectedEnd)
{
    ExpectSequencesAreEquivalent(actual.begin(), actual.end(), expectedBegin, expectedEnd);
}

template <typename TActualQuery, typename TExpectedQuery>
void ExpectSequencesAreEquivalent(const TActualQuery& actual, const TExpectedQuery expected)
{
    ExpectSequencesAreEquivalent(actual.begin(), actual.end(), expected.begin(), expected.end());
}

template <typename TActualQuery, typename T, std::uint32_t TLength>
void ExpectSequencesAreEquivalent(const TActualQuery& actual, const T (&expected)[TLength])
{
    ExpectSequencesAreEquivalent(actual, reinterpret_cast<const T*>(&expected), reinterpret_cast<const T*>(&expected) + TLength);
}

template <typename TActualQuery, typename T>
void ExpectSequencesAreEquivalent(const TActualQuery& actual, const std::vector<T>& expected)
{
    ExpectSequencesAreEquivalent(actual, expected.cbegin(), expected.cend());
}

template <typename TActualQuery, typename T = decltype(std::declval<TActualQuery>().begin().operator*())>
void ExpectSequenceIsEmpty(const TActualQuery& actual)
{
    ExpectSequencesAreEquivalent(actual, std::vector<T>());
}