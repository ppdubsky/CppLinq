#pragma once

#include "Details/Enumerators/ChunkEnumerator.hpp"

#include "Exceptions/ArgumentOutOfRangeException.hpp"
#include "Exceptions/FinishedEnumeratorException.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator>
    ChunkEnumerator<TEnumerator>::ChunkEnumerator(const TEnumerator enumerator, const std::uint32_t size) :
        Base(enumerator),
        size(size)
    {
        if (size < 1U)
        {
            throw Exceptions::ArgumentOutOfRangeException();
        }
    }

    template <typename TEnumerator>
    void ChunkEnumerator<TEnumerator>::EnsureEnumeratorIsReady()
    {
        if (!isReady)
        {
            container.clear();

            auto index = 0U;

            while (Base::HasCurrent())
            {
                container.push_back(Base::GetCurrent());

                Base::MoveNext();

                ++index;

                if (index >= size)
                {
                    break;
                }
            }

            isReady = true;
        }
    }

    template <typename TEnumerator>
    auto ChunkEnumerator<TEnumerator>::GetCurrent() -> const ValueType&
    {
        if (isBaseFinished)
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        EnsureEnumeratorIsReady();

        return container;
    }

    template <typename TEnumerator>
    auto ChunkEnumerator<TEnumerator>::HasCurrent() -> bool
    {
        EnsureEnumeratorIsReady();

        return !container.empty();
    }

    template <typename TEnumerator>
    void ChunkEnumerator<TEnumerator>::MoveNext()
    {
        if (isBaseFinished)
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        isBaseFinished = !Base::HasCurrent();
        isReady = false;
    }
}