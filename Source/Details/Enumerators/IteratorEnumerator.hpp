#pragma once

#include "Details/Enumerators/IteratorEnumerator.Forward.hpp"

#include "Details/TypeTraits/ValueTypeProvider.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TIterator>
    struct IteratorEnumerator final
    {
        using ValueType = typename TypeTraits::ValueTypeProvider<TIterator>::ValueType;

        IteratorEnumerator(const TIterator begin, const TIterator end);

        auto GetCurrent() -> const ValueType&;
        auto IsFinished() -> bool;
        void MoveNext();

    private:
        TIterator begin;
        TIterator end;
    };
}