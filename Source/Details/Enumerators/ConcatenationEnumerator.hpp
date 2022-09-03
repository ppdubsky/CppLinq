#pragma once

#include "Details/Enumerators/EnumeratorWrapper.hpp"
#include "Details/Query.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TNextEnumerator>
    struct ConcatenationEnumerator final : EnumeratorWrapper<TEnumerator>
    {
        using Base = EnumeratorWrapper<TEnumerator>;

        ConcatenationEnumerator(const TEnumerator enumerator, const Query<TNextEnumerator>& nextQuery);

        auto GetCurrent() -> Base::ValueType;
        auto IsFinished() -> bool;
        void MoveNext();

    private:
        Query<TNextEnumerator> nextQuery;
    };
}