
#pragma once
#include "stdh.hpp"

namespace
{
	template<typename T>
	concept not_range = !std::ranges::range<T>;

	namespace reference
	{
		template<typename Ref>
		concept Concept = requires(Ref ref) { typename Ref::type; ref.get(); };

		template<Concept Ref>
		struct hash
		{
			constexpr auto operator()(const Ref& ref) const->size_t
			{
				std::hash<Ref::type> h{};
				return h(ref.get());
			}
		};

		template<Concept Ref>
		struct equal_to
		{
			constexpr auto operator()(const Ref& lhs, const Ref& rhs) const->bool
			{
				std::equal_to<Ref::type> e{};
				return e(lhs.get(), rhs.get());
			}
		};

		template<Concept Ref>
		struct less
		{
			constexpr auto operator()(const Ref& lhs, const Ref& rhs) const->bool
			{
				std::less<Ref::type> e{};
				return e(lhs.get(), rhs.get());
			}
		};
	}
}