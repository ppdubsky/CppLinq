#pragma once

#include "Details/TypeTraits/ValueTypeProvider.hpp"
#include "Exceptions/FinishedEnumeratorException.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TIterator>
    struct IteratorEnumerator final
    {
        using ValueType = typename TypeTraits::ValueTypeProvider<TIterator>::ValueType;

        IteratorEnumerator(const TIterator begin, const TIterator end) :
            begin(begin),
            end(end)
        {
        }

        auto GetCurrent() -> const ValueType&
        {
            if (IsFinished())
            {
                throw Exceptions::FinishedEnumeratorException();
            }

            return *begin;
        }

        auto IsFinished() -> bool
        {
            return begin == end;
        }

        void MoveNext()
        {
            if (IsFinished())
            {
                throw Exceptions::FinishedEnumeratorException();
            }

            ++begin;
        }

    private:
        TIterator begin;
        TIterator end;
    };
}