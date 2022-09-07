#pragma once

#include "Details/Enumerators/WhereEnumerator.Forward.hpp"

#include "Details/Enumerators/EnumeratorWrapper.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TPredicate>
    struct WhereEnumerator final : EnumeratorWrapper<TEnumerator>
    {
        using Base = EnumeratorWrapper<TEnumerator>;

        WhereEnumerator(const TEnumerator enumerator, const TPredicate predicate);

        auto GetCurrent() -> Base::ValueType;
        auto HasCurrent() -> bool;
        void MoveNext();

    private:
        void EnsureEnumeratorIsReady();

        bool isReady{ false };
        TPredicate predicate;
    };
}