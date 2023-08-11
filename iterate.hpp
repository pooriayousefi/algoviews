
#pragma once
#include "stdh.hpp"

namespace
{
	template<std::input_or_output_iterator It, std::invocable<std::iter_value_t<It>&> F>
	constexpr auto iterate(It begin, size_t n, size_t step_size, F f) -> void
	{
		auto c = 0Ui64;
		auto it = begin;
		do
		{
			std::invoke(f, *it);			
			c++;
		} while (c < n && [&](){ it = std::next(it, step_size); return true; }());
	}
}