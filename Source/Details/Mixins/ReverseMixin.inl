#pragma once

#include "Details/Mixins/ReverseMixin.hpp"

#include "Details/Enumerators/ReverseEnumerator.hpp"
#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Query.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    auto ReverseMixin<TQuery>::Reverse() const -> Query<Enumerators::ReverseEnumerator<EnumeratorType>>
    {
        return { { MixinUtilities::GetEnumerator<TQuery>(*this) } };
    }
}