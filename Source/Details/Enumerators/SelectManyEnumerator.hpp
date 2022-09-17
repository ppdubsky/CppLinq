#pragma once

#include "Details/Enumerators/SelectManyEnumerator.Forward.hpp"

#include "Details/Enumerators/EnumeratorWrapper.hpp"

template <typename T>
struct Foo;

template <typename T>
struct Foo<std::vector<T>>
{
    using Type = T;
};

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TSelector>
    struct SelectManyEnumerator final : EnumeratorWrapper<TEnumerator>
    {
        using Base = EnumeratorWrapper<TEnumerator>;
        using ContainerType = decltype(std::declval<TSelector>()(std::declval<typename Base::ValueType>()));
        using IteratorType = ContainerType::const_iterator;
        using ValueType = Foo<ContainerType>::Type;

        SelectManyEnumerator(const TEnumerator enumerator, const TSelector selector);

        auto GetCurrent() -> ValueType;
        auto HasCurrent() -> bool;
        void MoveNext();

    private:
        void EnsureEnumeratorIsReady();

        ContainerType container;
        bool isReady{ false };
        IteratorType iterator;
        TSelector selector;
    };
}