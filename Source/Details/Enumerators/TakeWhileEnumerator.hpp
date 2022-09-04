#pragma once

#include "Details/Enumerators/TakeWhileEnumerator.Forward.hpp"

#include "Details/Enumerators/EnumeratorWrapper.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TPredicate>
    struct TakeWhileEnumerator final : EnumeratorWrapper<TEnumerator>
    {
        using Base = EnumeratorWrapper<TEnumerator>;

        TakeWhileEnumerator(const TEnumerator enumerator, const TPredicate predicate);

        auto GetCurrent() -> Base::ValueType;
        auto IsFinished() -> bool;
        void MoveNext();

    private:
        TPredicate predicate;
    };
}