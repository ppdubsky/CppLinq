#pragma once

#include <type_traits>

#include "Details/Query.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator>
    struct OrderEnumerator final
    {
        using ContainerType = decltype(std::declval<Query<TEnumerator>>().ToVector());
        using IteratorType = typename ContainerType::const_iterator;
        using ValueType = typename Query<TEnumerator>::ValueType;

        OrderEnumerator(const Query<TEnumerator>& query);

        auto GetCurrent() -> const ValueType&;
        auto IsFinished() -> bool;
        void MoveNext();

    private:
        void EnsureEnumeratorIsReady();

        IteratorType begin;
        ContainerType container;
        IteratorType end;
        bool isReady{ false };
        Query<TEnumerator> query;
    };
}