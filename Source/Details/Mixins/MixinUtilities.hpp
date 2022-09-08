#pragma once

#include "Details/TypeTraits/EnumeratorTypeProvider.hpp"

namespace CppLinq::Details::Mixins
{
    struct MixinUtilities final
    {
        template <typename TQuery, typename TMixin>
        static auto GetEnumerator(const TMixin& mixin) -> typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType;
        template <typename TQuery, typename TMixin>
        static auto GetQuery(const TMixin& mixin) -> const TQuery&;
    };
}