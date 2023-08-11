
#pragma once
#include "size_of_data.hpp"

namespace
{
	// sort view template
	template<std::input_or_output_iterator It>
	struct sort_view
	{
		// type definitions
		using T = std::iter_value_t<It>;
		using reference_type = std::reference_wrapper<T>;

		// data members
		It observable_begin_iterator, observable_end_iterator;
		std::multiset<reference_type, reference::less<reference_type>,
			std::allocator<reference_type>> configuration;

		// ctors/dtor
		sort_view()
			:observable_begin_iterator{},
			observable_end_iterator{},
			configuration{}
		{
		}
		sort_view(It begin, It end)
			:observable_begin_iterator{ begin },
			observable_end_iterator{ end },
			configuration{}
		{
			update();
		}
		virtual ~sort_view() = default;

		// observable iterators setter
		auto set_observable_iterators(It begin, It end) -> void
		{
			observable_begin_iterator = begin;
			observable_end_iterator = end;
		}

		// update method
		constexpr auto update() -> void
		{
			configuration.clear();
			std::ranges::for_each(
				observable_begin_iterator,
				observable_end_iterator,
				[this](auto& value)
				{
					configuration.emplace(std::ref(value));
				}
			);
		}

		// display method
		constexpr auto show(std::ostream& os) const-> void
		{
			std::ranges::for_each(
				configuration,
				[&os](auto& e)
				{
					os << e.get() << '\t' << reinterpret_cast<uintptr_t>(&(e.get())) << '\n';
				}
			);
		}
		constexpr auto show(std::ofstream& os) const-> void
		{
			std::ranges::for_each(
				configuration,
				[&os](auto& e)
				{
					os << e.get() << '\t' << reinterpret_cast<uintptr_t>(&(e.get())) << '\n';
				}
			);
		}
		constexpr auto show(std::wostream& os) const-> void
		{
			std::ranges::for_each(
				configuration,
				[&os](auto& e)
				{
					os << e.get() << '\t' << reinterpret_cast<uintptr_t>(&(e.get())) << '\n';
				}
			);
		}
		constexpr auto show(std::wofstream& os) const-> void
		{
			std::ranges::for_each(
				configuration,
				[&os](auto& e)
				{
					os << e.get() << '\t' << reinterpret_cast<uintptr_t>(&(e.get())) << '\n';
				}
			);
		}

		// size method
		constexpr auto size() const->size_t { return configuration.size(); }

		// size of data in bytes
		constexpr auto size_of_data_in_bytes() const->size_t { return size_of::data_in_bytes(configuration); }
	};
}