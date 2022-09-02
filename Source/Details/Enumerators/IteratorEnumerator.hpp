#pragma once

#include "../TypeTraits/ValueTypeProvider.hpp"

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
            return *begin;
        }

        auto IsFinished() -> bool
        {
            return begin == end;
        }

        void MoveNext()
        {
            ++begin;
        }

    private:
        TIterator begin;
        TIterator end;
    };
}