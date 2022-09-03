#pragma once

#include "Details/Enumerators/EnumeratorWrapper.hpp"
#include "Details/Enumerators/IteratorEnumerator.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TContainer>
    struct ReverseEnumerator final : EnumeratorWrapper<IteratorEnumerator<typename TContainer::const_reverse_iterator>>
    {
        using Base = EnumeratorWrapper<IteratorEnumerator<typename TContainer::const_reverse_iterator>>;

        ReverseEnumerator(const TContainer& container) ;

    private:
        TContainer container;
    };
}