#pragma once

#include "Details/Query.hpp"

#include "Details/Enumerators/AppendEnumerator.hpp"
#include "Details/Enumerators/ConcatenationEnumerator.hpp"
#include "Details/Enumerators/DefaultIfEmptyEnumerator.hpp"
#include "Details/Enumerators/ForEachEnumerator.hpp"
#include "Details/Enumerators/IteratorEnumerator.hpp"
#include "Details/Enumerators/OrderEnumerator.hpp"
#include "Details/Enumerators/PrependEnumerator.hpp"
#include "Details/Enumerators/ReverseEnumerator.hpp"
#include "Details/Enumerators/SelectEnumerator.hpp"
#include "Details/Enumerators/SkipEnumerator.hpp"
#include "Details/Enumerators/SkipWhileEnumerator.hpp"
#include "Details/Enumerators/StaticCastEnumerator.hpp"
#include "Details/Enumerators/TakeEnumerator.hpp"
#include "Details/Enumerators/TakeWhileEnumerator.hpp"
#include "Details/Enumerators/WhereEnumerator.hpp"
#include "Details/Loops/LoopIterator.hpp"
#include "Details/Loops/LoopIteratorSentinel.hpp"
#include "Exceptions/EmptyCollectionException.hpp"

namespace CppLinq::Details
{
    template <typename TEnumerator>
    Query<TEnumerator>::Query(const TEnumerator enumerator) :
        enumerator(enumerator)
    {
    }

    template <typename TEnumerator>
    auto Query<TEnumerator>::begin() const -> Loops::LoopIterator<TEnumerator>
    {
        return { enumerator };
    }

    template <typename TEnumerator>
    auto Query<TEnumerator>::end() const -> Loops::LoopIteratorSentinel
    {
        return {};
    }

    template <typename TEnumerator>
    auto Query<TEnumerator>::GetEnumerator() -> TEnumerator&
    {
        return enumerator;
    }

    template <typename TEnumerator>
    template <typename TPredicate>
    auto Query<TEnumerator>::All(const TPredicate predicate) const -> bool
    {
        auto isValid = true;

        TEnumerator enumeratorCopy = enumerator;
        while (!enumeratorCopy.IsFinished())
        {
            if (!predicate(enumeratorCopy.GetCurrent()))
            {
                isValid = false;
                break;
            }

            enumeratorCopy.MoveNext();
        }

        return isValid;
    }

    template <typename TEnumerator>
    template <typename TPredicate>
    auto Query<TEnumerator>::Any(const TPredicate predicate) const -> bool
    {
        auto isValid = false;

        TEnumerator enumeratorCopy = enumerator;
        while (!enumeratorCopy.IsFinished())
        {
            if (predicate(enumeratorCopy.GetCurrent()))
            {
                isValid = true;
                break;
            }

            enumeratorCopy.MoveNext();
        }

        return isValid;
    }

    template <typename TEnumerator>
    auto Query<TEnumerator>::Append(const ValueType& value) const -> Query<Enumerators::AppendEnumerator<TEnumerator>>
    {
        return { { enumerator, value } };
    }

    template <typename TEnumerator>
    auto Query<TEnumerator>::Average() const -> ValueType
    {
        auto sum = static_cast<ValueType>(0);
        auto count = 0U;

        TEnumerator enumeratorCopy = enumerator;
        while (!enumeratorCopy.IsFinished())
        {
            sum += enumeratorCopy.GetCurrent();

            ++count;

            enumeratorCopy.MoveNext();
        }

        if (count == 0U)
        {
            throw Exceptions::EmptyCollectionException();
        }

        return sum / count;
    }

    template <typename TEnumerator>
    template <typename TNextEnumerator>
    auto Query<TEnumerator>::Concatenate(const Query<TNextEnumerator>& nextQuery) const -> Query<Enumerators::ConcatenationEnumerator<TEnumerator, TNextEnumerator>>
    {
        return { { enumerator, nextQuery } };
    }

    template <typename TEnumerator>
    auto Query<TEnumerator>::Count() const -> std::uint32_t
    {
        return Count([](const ValueType& /*value*/){ return true; });
    }

    template <typename TEnumerator>
    template <typename TPredicate>
    auto Query<TEnumerator>::Count(const TPredicate predicate) const -> std::uint32_t
    {
        auto count = 0U;

        TEnumerator enumeratorCopy = enumerator;
        while (!enumeratorCopy.IsFinished())
        {
            if (predicate(enumeratorCopy.GetCurrent()))
            {
                ++count;
            }

            enumeratorCopy.MoveNext();
        }

        return count;
    }

    template <typename TEnumerator>
    auto Query<TEnumerator>::DefaultIfEmpty() const -> Query<Enumerators::DefaultIfEmptyEnumerator<TEnumerator>>
    {
        return DefaultIfEmpty(ValueType());
    }
    template <typename TEnumerator>
    auto Query<TEnumerator>::DefaultIfEmpty(const ValueType& defaultValue) const -> Query<Enumerators::DefaultIfEmptyEnumerator<TEnumerator>>
    {
        return { { enumerator, defaultValue } };
    }

    template <typename TEnumerator>
    auto Query<TEnumerator>::First() const -> ValueType
    {
        return First([](const ValueType& /*value*/){ return true; });
    }

    template <typename TEnumerator>
    template <typename TPredicate>
    auto Query<TEnumerator>::First(const TPredicate predicate) const -> ValueType
    {
        TEnumerator enumeratorCopy = enumerator;

        while (!enumeratorCopy.IsFinished())
        {
            const ValueType current = enumeratorCopy.GetCurrent();
            if (predicate(current))
            {
                return current;
            }

            enumeratorCopy.MoveNext();
        }

        throw Exceptions::EmptyCollectionException();
    }

    template <typename TEnumerator>
    template <typename TFunction>
    auto Query<TEnumerator>::ForEach(const TFunction function) const -> Query<Enumerators::ForEachEnumerator<TEnumerator, TFunction>>
    {
        return { { enumerator, function } };
    }

    template <typename TEnumerator>
    auto Query<TEnumerator>::GetBound(const bool isMaximum) const -> ValueType
    {
        TEnumerator enumeratorCopy = enumerator;

        if (enumeratorCopy.IsFinished())
        {
            throw Exceptions::EmptyCollectionException();
        }

        ValueType bound = enumeratorCopy.GetCurrent();

        enumeratorCopy.MoveNext();

        while (!enumeratorCopy.IsFinished())
        {
            const ValueType current = enumeratorCopy.GetCurrent();
            if (isMaximum ? current > bound : current < bound)
            {
                bound = current;
            }

            enumeratorCopy.MoveNext();
        }

        return bound;
    }

    template <typename TEnumerator>
    auto Query<TEnumerator>::Last() const -> ValueType
    {
        return Last([](const ValueType& /*value*/){ return true; });
    }

    template <typename TEnumerator>
    template <typename TPredicate>
    auto Query<TEnumerator>::Last(const TPredicate predicate) const -> ValueType
    {
        TEnumerator enumeratorCopy = enumerator;

        while (!enumeratorCopy.IsFinished())
        {
            if (predicate(enumeratorCopy.GetCurrent()))
            {
                break;
            }

            enumeratorCopy.MoveNext();
        }

        if (enumeratorCopy.IsFinished())
        {
            throw Exceptions::EmptyCollectionException();
        }

        ValueType last = enumeratorCopy.GetCurrent();

        while (!enumeratorCopy.IsFinished())
        {
            const ValueType current = enumeratorCopy.GetCurrent();
            if (predicate(current))
            {
                last = current;
            }

            enumeratorCopy.MoveNext();
        }

        return last;
    }

    template <typename TEnumerator>
    auto Query<TEnumerator>::Maximum() const -> ValueType
    {
        return GetBound(true);
    }

    template <typename TEnumerator>
    auto Query<TEnumerator>::Minimum() const -> ValueType
    {
        return GetBound(false);
    }

    template <typename TEnumerator>
    auto Query<TEnumerator>::OrderBy() const -> Query<Enumerators::OrderEnumerator<TEnumerator>>
    {
        return { { *this } };
    }

    template <typename TEnumerator>
    auto Query<TEnumerator>::Prepend(const ValueType& value) const -> Query<Enumerators::PrependEnumerator<TEnumerator>>
    {
        return { { enumerator, value } };
    }

    template <typename TEnumerator>
    auto Query<TEnumerator>::Reverse() const -> Query<Enumerators::ReverseEnumerator<TEnumerator>>
    {
        return { { *this } };
    }

    template <typename TEnumerator>
    template <typename TSelector>
    auto Query<TEnumerator>::Select(const TSelector selector) const -> Query<Enumerators::SelectEnumerator<TEnumerator, TSelector>>
    {
        return { { enumerator, selector } };
    }

    template <typename TEnumerator>
    auto Query<TEnumerator>::Skip(const std::uint32_t count) const -> Query<Enumerators::SkipEnumerator<TEnumerator>>
    {
        return { { enumerator, count } };
    }

    template <typename TEnumerator>
    template <typename TPredicate>
    auto Query<TEnumerator>::SkipWhile(const TPredicate predicate) const -> Query<Enumerators::SkipWhileEnumerator<TEnumerator, TPredicate>>
    {
        return { { enumerator, predicate } };
    }

    template <typename TEnumerator>
    template <typename TNewType>
    auto Query<TEnumerator>::StaticCast() const -> Query<Enumerators::StaticCastEnumerator<TEnumerator, TNewType>>
    {
        return { { enumerator } };
    }

    template <typename TEnumerator>
    auto Query<TEnumerator>::Sum() const -> ValueType
    {
        auto sum = static_cast<ValueType>(0);

        TEnumerator enumeratorCopy = enumerator;
        while (!enumeratorCopy.IsFinished())
        {
            sum += enumeratorCopy.GetCurrent();

            enumeratorCopy.MoveNext();
        }

        return sum;
    }

    template <typename TEnumerator>
    auto Query<TEnumerator>::Take(const std::uint32_t count) const -> Query<Enumerators::TakeEnumerator<TEnumerator>>
    {
        return { { enumerator, count } };
    }

    template <typename TEnumerator>
    template <typename TPredicate>
    auto Query<TEnumerator>::TakeWhile(const TPredicate predicate) const -> Query<Enumerators::TakeWhileEnumerator<TEnumerator, TPredicate>>
    {
        return { { enumerator, predicate } };
    }

    template <typename TEnumerator>
    auto Query<TEnumerator>::ToVector() const -> std::vector<ValueType>
    {
        std::vector<ValueType> items;

        TEnumerator enumeratorCopy = enumerator;
        while (!enumeratorCopy.IsFinished())
        {
            items.push_back(enumeratorCopy.GetCurrent());

            enumeratorCopy.MoveNext();
        }

        return items;
    }

    template <typename TEnumerator>
    template <typename TPredicate>
    auto Query<TEnumerator>::Where(const TPredicate predicate) const -> Query<Enumerators::WhereEnumerator<TEnumerator, TPredicate>>
    {
        return { { enumerator, predicate } };
    }
}