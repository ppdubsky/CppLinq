#pragma once

#include "Details/Enumerators/SelectManyEnumerator.hpp"

#include "Exceptions/FinishedEnumeratorException.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TSelector>
    SelectManyEnumerator<TEnumerator, TSelector>::SelectManyEnumerator(const TEnumerator enumerator, const TSelector selector) :
        Base(enumerator),
        selector(selector)
    {
    }

    template <typename TEnumerator, typename TSelector>
    void SelectManyEnumerator<TEnumerator, TSelector>::EnsureEnumeratorIsReady()
    {
        if (!isReady)
        {
            container.clear();
            iterator = container.cend();

            while (Base::HasCurrent())
            {
                container = selector(Base::GetCurrent());
                if (container.empty())
                {
                    Base::MoveNext();
                }
                else
                {
                    iterator = container.cbegin();
                    break;
                }
            }

            isReady = true;
        }
    }

    template <typename TEnumerator, typename TSelector>
    auto SelectManyEnumerator<TEnumerator, TSelector>::GetCurrent() -> ValueType
    {
        EnsureEnumeratorIsReady();

        if (iterator == container.cend())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        return *iterator;
    }

    template <typename TEnumerator, typename TSelector>
    auto SelectManyEnumerator<TEnumerator, TSelector>::HasCurrent() -> bool
    {
        EnsureEnumeratorIsReady();

        return Base::HasCurrent();
    }

    template <typename TEnumerator, typename TSelector>
    void SelectManyEnumerator<TEnumerator, TSelector>::MoveNext()
    {
        EnsureEnumeratorIsReady();

        if (iterator == container.cend())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        ++iterator;
        if (iterator == container.cend())
        {
            isReady = false;
            Base::MoveNext();

            EnsureEnumeratorIsReady();
        }
    }
}