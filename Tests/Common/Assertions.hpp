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
    ExpectSequencesAreEquivalent(begin(actual), end(actual), expectedBegin, expectedEnd);
}

template <typename TActualQuery, typename TExpectedQuery>
void ExpectSequencesAreEquivalent(const TActualQuery& actual, const TExpectedQuery expected)
{
    ExpectSequencesAreEquivalent(begin(actual), end(actual), begin(expected), end(expected));
}

template <typename TActualQuery, typename T, std::uint32_t TLength>
void ExpectSequencesAreEquivalent(const TActualQuery& actual, const T (&expected)[TLength])
{
    ExpectSequencesAreEquivalent(actual, std::cbegin(expected), std::cend(expected));
}

template <typename TActualQuery, typename T>
void ExpectSequencesAreEquivalent(const TActualQuery& actual, const std::vector<T>& expected)
{
    ExpectSequencesAreEquivalent(actual, std::cbegin(expected), std::cend(expected));
}

template <typename TActualQuery, typename T = decltype(*begin(std::declval<TActualQuery>()))>
void ExpectSequenceIsEmpty(const TActualQuery& actual)
{
    ExpectSequencesAreEquivalent(actual, std::vector<T>());
}