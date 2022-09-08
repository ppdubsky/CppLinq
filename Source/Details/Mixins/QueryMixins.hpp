#pragma once

namespace CppLinq::Details::Mixins
{
    template <typename TQuery, template <typename> typename... TMixins>
    struct QueryMixins : TMixins<TQuery>...
    {
    };
}