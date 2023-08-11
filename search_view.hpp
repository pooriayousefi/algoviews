
#pragma once
#include "concepts.hpp"

namespace
{
	namespace O1
	{
		// seacrh view template
		template<std::input_or_output_iterator It>
		struct seacrh_view
		{
			// type definitions
			using T = std::iter_value_t<It>;
			using reference_type = std::reference_wrapper<T>;

			// data members
			It observable_begin_iterator, observable_end_iterator;
			std::unordered_multiset<reference_type, reference::hash<reference_type>,
				reference::equal_to<reference_type>, std::allocator<reference_type>> configuration;

			// ctors/dtor
			seacrh_view()
				:observable_begin_iterator{},
				observable_end_iterator{},
				configuration{}
			{
			}
			seacrh_view(It begin, It end)
				:observable_begin_iterator{ begin },
				observable_end_iterator{ end },
				configuration{}
			{
				update();
			}
			virtual ~seacrh_view() = default;

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
			auto show(std::ostream& os) -> void
			{
				std::ranges::for_each(
					configuration,
					[&os](auto& e)
					{
						os << e.get() << '\t' << reinterpret_cast<uintptr_t>(&(e.get())) << '\n';
					}
				);
			}
			auto show(std::ofstream& os) -> void
			{
				std::ranges::for_each(
					configuration,
					[&os](auto& e)
					{
						os << e.get() << '\t' << reinterpret_cast<uintptr_t>(&(e.get())) << '\n';
					}
				);
			}
			auto show(std::wostream& os) -> void
			{
				std::ranges::for_each(
					configuration,
					[&os](auto& e)
					{
						os << e.get() << '\t' << reinterpret_cast<uintptr_t>(&(e.get())) << '\n';
					}
				);
			}
			auto show(std::wofstream& os) -> void
			{
				std::ranges::for_each(
					configuration,
					[&os](auto& e)
					{
						os << e.get() << '\t' << reinterpret_cast<uintptr_t>(&(e.get())) << '\n';
					}
				);
			}

			// find methods
			constexpr decltype(auto) find(std::iter_value_t<It> value)
			{
				return configuration.find(std::ref(value));
			}
			constexpr decltype(auto) find(reference_type value_ref)
			{
				return configuration.find(value_ref);
			}

			// size method
			constexpr auto size() const->size_t { return configuration.size(); }

			// size of data in bytes
			constexpr auto size_of_data_in_bytes() const->size_t { return size_of::data_in_bytes(configuration); }
		};
	}
}