#pragma once

#include "Details/Enumerators/SelectManyEnumerator.Forward.hpp"

#include "Details/Enumerators/EnumeratorWrapper.hpp"
#include "Details/TypeTraits/ElementTypeProvider.hpp"
#include "Details/TypeTraits/FunctionReturnTypeProvider.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TResultSelector>
    struct SelectManyEnumerator final : EnumeratorWrapper<TEnumerator>
    {
        using Base = EnumeratorWrapper<TEnumerator>;
        using ContainerType = TypeTraits::FunctionReturnTypeProvider<TResultSelector, typename Base::ValueType>::ReturnType;
        using IteratorType = ContainerType::const_iterator;
        using ValueType = TypeTraits::ElementTypeProvider<ContainerType>::ElementType;

        SelectManyEnumerator(const TEnumerator enumerator, const TResultSelector resultSelector);

        auto GetCurrent() -> ValueType;
        auto HasCurrent() -> bool;
        void MoveNext();

    private:
        void EnsureEnumeratorIsReady();

        ContainerType container;
        bool isReady{ false };
        IteratorType iterator;
        TResultSelector resultSelector;
    };
}