
#pragma once
#include "iterate.hpp"

namespace
{
	// matrix view class template
	template<std::input_or_output_iterator It>
	struct matrix_view
	{
		// type definitions
		using value_type = std::iter_value_t<It>;
		using reference_type = std::reference_wrapper<value_type>;
		using const_reference_type = const std::reference_wrapper<value_type>;

		// field members
		size_t number_of_rows, number_of_columns;
		It begin;

		// ctors/dtor
		matrix_view()
			:number_of_rows{ 0Ui64 },
			number_of_columns{ 0Ui64 },
			begin{}
		{
		}
		matrix_view(size_t nr, size_t nc, It beg)
			:number_of_rows{ nr },
			number_of_columns{ nc },
			begin{ beg }
		{
		}
		virtual ~matrix_view() = default;

		// operator overloadings
		friend constexpr auto operator<<(std::ostream& os, const matrix_view<It>& m) -> std::ostream&
		{
			os << "\n(" << m.number_of_rows << " x " << m.number_of_columns << ")\n";
			for (auto i{ 0Ui64 }; i < m.number_of_rows; ++i)
			{
				iterate(
					std::next(m.begin, i * m.number_of_columns),
					m.number_of_columns,
					1Ui64,
					[&os](auto& value)
					{
						os << value << ':' << reinterpret_cast<uintptr_t>(&value) << '\t';
					}
				);
				os << '\n';
			}
			return os;
		}
		friend constexpr auto operator<<(std::ofstream& os, const matrix_view<It>& m) -> std::ofstream&
		{
			os << "\n(" << m.number_of_rows << " x " << m.number_of_columns << ")\n";
			for (auto i{ 0Ui64 }; i < m.number_of_rows; ++i)
			{
				iterate(
					std::next(m.begin, i * m.number_of_columns),
					m.number_of_columns,
					1Ui64,
					[&os](auto& value)
					{
						os << value << ':' << reinterpret_cast<uintptr_t>(&value) << '\t';
					}
				);
				os << '\n';
			}
			return os;
		}
		friend constexpr auto operator<<(std::wostream& os, const matrix_view<It>& m) -> std::wostream&
		{
			os << L"\n(" << m.number_of_rows << L" x " << m.number_of_columns << L")\n";
			for (auto i{ 0Ui64 }; i < m.number_of_rows; ++i)
			{
				iterate(
					std::next(m.begin, i * m.number_of_columns),
					m.number_of_columns,
					1Ui64,
					[&os](auto& value)
					{
						os << value << L':' << reinterpret_cast<uintptr_t>(&value) << L'\t';
					}
				);
				os << L'\n';
			}
		}
		friend constexpr auto operator<<(std::wofstream& os, const matrix_view<It>& m) -> std::wofstream&
		{
			os << L"\n(" << m.number_of_rows << L" x " << m.number_of_columns << L")\n";
			for (auto i{ 0Ui64 }; i < m.number_of_rows; ++i)
			{
				iterate(
					std::next(m.begin, i * m.number_of_columns),
					m.number_of_columns,
					1Ui64,
					[&os](auto& value)
					{
						os << value << L':' << reinterpret_cast<uintptr_t>(&value) << L'\t';
					}
				);
				os << L'\n';
			}
		}
		constexpr auto operator()(size_t i, size_t j) -> value_type& 
		{
			return *std::next(begin, i * number_of_columns + j);
		}
		constexpr auto operator()(size_t i, size_t j) const-> value_type
		{
			return *std::next(begin, i * number_of_columns + j);
		}

		// methods
		constexpr auto size() const->size_t { return number_of_columns * number_of_rows; }
		constexpr auto row(size_t i) ->std::vector<reference_type>
		{
			std::vector<reference_type> rowi{};
			rowi.reserve(number_of_columns);
			iterate(
				std::next(begin, i * number_of_columns),
				number_of_columns, 
				1Ui64, 
				[&rowi](auto& value)
				{
					rowi.emplace_back(std::ref(value));
				}
			);
			return rowi;
		}
		constexpr auto row(size_t i) const->std::vector<const_reference_type>
		{
			std::vector<const_reference_type> rowi{};
			rowi.reserve(number_of_columns);
			iterate(
				std::next(begin, i * number_of_columns),
				number_of_columns,
				1Ui64,
				[&rowi](auto& value)
				{
					rowi.emplace_back(std::cref(value));
				}
			);
			return rowi;
		}
		constexpr auto column(size_t j) ->std::vector<reference_type>
		{
			std::vector<reference_type> colj{};
			colj.reserve(number_of_rows);
			iterate(
				std::next(begin, j),
				number_of_rows,
				number_of_columns,
				[&colj](auto& value)
				{
					colj.emplace_back(std::ref(value));
				}
			);
			return colj;
		}		
		constexpr auto column(size_t j) const->std::vector<const_reference_type>
		{
			std::vector<const_reference_type> colj{};
			colj.reserve(number_of_rows);
			iterate(
				std::next(begin, j),
				number_of_rows,
				number_of_columns,
				[&colj](auto& value)
				{
					colj.emplace_back(std::cref(value));
				}
			);
			return colj;
		}
	};

	// blocking operations space
	namespace blocking
	{
		// blocking synchronous operations space
		namespace synchronous
		{
			// blocking synchronous eager matrix multiplication
			template<std::input_or_output_iterator LhsIt,
				std::input_or_output_iterator RhsIt,
				typename Res = std::common_type_t<std::iter_value_t<LhsIt>, std::iter_value_t<RhsIt>>
			> auto multiplies(matrix_view<LhsIt> lhs, matrix_view<RhsIt> rhs)
				-> std::tuple<size_t, size_t, std::vector<Res>>
			{
				auto result{ std::make_tuple(0Ui64, 0Ui64, std::vector<Res>{}) };

				if (lhs.number_of_columns == rhs.number_of_rows)
				{
					std::get<0Ui64>(result) = lhs.number_of_rows;
					std::get<1Ui64>(result) = rhs.number_of_columns;
					std::get<2Ui64>(result).resize(lhs.number_of_rows * rhs.number_of_columns, Res{});

					for (auto i = 0Ui64; i < lhs.number_of_rows; ++i)
					{
						auto lhs_row_i{ lhs.row(i) };
						for (auto j = 0Ui64; j < rhs.number_of_columns; ++j)
						{
							auto rhs_col_j{ rhs.column(j) };
							std::get<2Ui64>(result).data()[i * rhs.number_of_columns + j] =
								std::transform_reduce(
									std::execution::seq,
									lhs_row_i.begin(),
									lhs_row_i.end(),
									rhs_col_j.begin(),
									(Res)0,
									std::plus<Res>{},
									[](auto& l, auto& r)
									{
										return l.get() * r.get();
									}
							);
						}
					}
				}

				return result;
			}
		}

		// blocking asynchronous operations space
		// (futures - CPU mode:kernel mode - interruptible OS threads)
		namespace asynchronous {}
	}
	
	// non-blocking operations space
	namespace non_blocking
	{
		// non-blocking asynchronous operations space
		// (coroutines - CPU mode:user mode - uninterruptible lightweight non-OS threads)
		namespace asynchronous {}
	}
}