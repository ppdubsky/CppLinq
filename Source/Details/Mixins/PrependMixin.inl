#pragma once

#include "Details/Mixins/PrependMixin.hpp"

#include "Details/Enumerators/PrependEnumerator.hpp"
#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Query.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    auto PrependMixin<TQuery>::Prepend(const ValueType& value) const -> Query<Enumerators::PrependEnumerator<EnumeratorType>>
    {
        return { { MixinUtilities::GetEnumerator<TQuery>(*this), value } };
    }
}