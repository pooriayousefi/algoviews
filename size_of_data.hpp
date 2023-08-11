
#pragma once
#include "concepts.hpp"

namespace
{
	namespace size_of
	{
		template<not_range T>
		constexpr auto data_in_bytes(T&& value) -> size_t
		{
			return sizeof(std::forward<T>(value));
		}

		template<std::ranges::range Rng>
		constexpr auto data_in_bytes(Rng&& rng) -> size_t
		{
			auto s{ static_cast<size_t>(0) };
			std::ranges::for_each(
				std::forward<Rng>(rng),
				[&s](auto& elem)
				{
					s += data_in_bytes(elem);
				}
			);
			return s;
		}
	}
}