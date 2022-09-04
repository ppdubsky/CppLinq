#pragma once

#include "Details/Enumerators/SkipWhileEnumerator.Forward.hpp"

#include "Details/Enumerators/EnumeratorWrapper.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TPredicate>
    struct SkipWhileEnumerator final : EnumeratorWrapper<TEnumerator>
    {
        using Base = EnumeratorWrapper<TEnumerator>;

        SkipWhileEnumerator(const TEnumerator enumerator, const TPredicate predicate);

        auto GetCurrent() -> Base::ValueType;
        auto IsFinished() -> bool;
        void MoveNext();

    private:
        void EnsureEnumeratorIsReady();

        bool isReady{ false };
        TPredicate predicate;
    };
}