#pragma once

#include "Details/Mixins/AppendMixin.hpp"

#include "Details/Enumerators/AppendEnumerator.hpp"
#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Query.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    auto AppendMixin<TQuery>::Append(const ValueType& value) const -> Query<Enumerators::AppendEnumerator<EnumeratorType>>
    {
        return { { MixinUtilities::GetEnumerator<TQuery>(*this), value } };
    }
}