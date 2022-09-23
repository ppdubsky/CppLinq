#pragma once

#include "Details/Enumerators/SelectManyEnumerator.hpp"

#include "Exceptions/FinishedEnumeratorException.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TResultSelector>
    SelectManyEnumerator<TEnumerator, TResultSelector>::SelectManyEnumerator(const TEnumerator enumerator, const TResultSelector resultSelector) :
        Base(enumerator),
        resultSelector(resultSelector)
    {
    }

    template <typename TEnumerator, typename TResultSelector>
    void SelectManyEnumerator<TEnumerator, TResultSelector>::EnsureEnumeratorIsReady()
    {
        if (!isReady)
        {
            container.clear();
            iterator = container.cend();

            while (Base::HasCurrent())
            {
                container = resultSelector(Base::GetCurrent());
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

    template <typename TEnumerator, typename TResultSelector>
    auto SelectManyEnumerator<TEnumerator, TResultSelector>::GetCurrent() -> ValueType
    {
        EnsureEnumeratorIsReady();

        if (iterator == container.cend())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        return *iterator;
    }

    template <typename TEnumerator, typename TResultSelector>
    auto SelectManyEnumerator<TEnumerator, TResultSelector>::HasCurrent() -> bool
    {
        EnsureEnumeratorIsReady();

        return Base::HasCurrent();
    }

    template <typename TEnumerator, typename TResultSelector>
    void SelectManyEnumerator<TEnumerator, TResultSelector>::MoveNext()
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