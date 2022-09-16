#pragma once

#include "Details/Enumerators/TakeLastWhileEnumerator.Forward.hpp"

#include <stack>

#include "Details/Enumerators/EnumeratorWrapper.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TPredicate>
    struct TakeLastWhileEnumerator final : EnumeratorWrapper<TEnumerator>
    {
        using Base = EnumeratorWrapper<TEnumerator>;
        using ContainerType = std::stack<typename Base::ValueType>;

        TakeLastWhileEnumerator(const TEnumerator enumerator, const TPredicate predicate);

        auto GetCurrent() -> Base::ValueType;
        auto HasCurrent() -> bool;
        void MoveNext();

    private:
        void EnsureEnumeratorIsReady();

        ContainerType container;
        bool isReady{ false };
        TPredicate predicate;
    };
}