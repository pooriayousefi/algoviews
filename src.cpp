
#include "sort_view.hpp"
#include "search_view.hpp"
#include "matrix_view.hpp"

auto main()->int
{
	auto size_of_data_in_bytes_test = []()
	{
		std::string s{ "Peter Jackson" };
		std::wstring ws{ L"Hoyte Van Hoytema" };
		std::cout
			<< "\n\n " << s << "\t\"Peter Jackson\" native narrow encoded string size (stack size): " << sizeof(s)
			<< " (bytes)\t\"Peter Jackson\" const char* size (data size - heap size): "
			<< size_of::data_in_bytes(s) << " (bytes)\n\n";
		std::wcout
			<< L"\n\n " << ws << L"\t\"Hoyte Van Hoytema\" native wide encoded string size (stack size): " << sizeof(ws)
			<< L" (bytes)\t\"Hoyte Van Hoytema\" const wchar_t* size (data size - heap size): "
			<< size_of::data_in_bytes(ws) << L" (bytes)\n\n";
	};
	auto sorted_and_O1_searchable_views_test = []()
	{
		std::vector<std::string> data{
		"James Cameron",
		"Stanley Kubrick",
		"Christopher Nolan",
		"Coen Brothers",
		"The Wachowskis",
		"Stanley Kubrick",
		"Giuseppe Tornatore",
		"Masud Kimiay",
		"Abbas Kiarostami",
		"Mel Gibson",
		"Mel Gibson",
		"Stanley Kubrick",
		"Stanley Kubrick",
		"James Cameron",
		"The Wachowskis"
		};

		std::cout
			<< "\n\ndata stack size: " << sizeof(data) << " (bytes)\tdata heap size: " << size_of::data_in_bytes(data) << " (bytes)\n\n";

		sort_view sorted_data(data.begin(), data.end());
		O1::seacrh_view O1_searchable_data(data.begin(), data.end());

		std::cout << "\n\ndata:\n\n"; [&data]()
		{
			std::ranges::for_each(
				data,
				[](auto& e)
				{
					std::cout << e << '\t' << reinterpret_cast<uintptr_t>(&e) << '\n';
				}
			);
			return "\n";
		}();
		std::cout << "\n\nsorted view:\n\n"; sorted_data.show(std::cout);
		std::cout << "\n\nsearch view:\n\n"; O1_searchable_data.show(std::cout);

		std::string 
			query1{ "Coen Brothers" }, 
			query2{ "Peter Jackson" },
			query3{ "Asghar Farhadi" },
			query4{ "The Wachowskis" };
		std::cout
			<< "\n\n" << query1 << [&]()
		{
			std::string result{};
			if (O1_searchable_data.find(query1) == O1_searchable_data.configuration.end())
				result = std::string{ " is not in data.\n" };
			else
				result = std::string{ " is in data.\n" };
			return result;
		}()
			<< "\n\n" << query2 << [&]()
		{
			std::string result{};
			if (O1_searchable_data.find(std::ref(query2)) == O1_searchable_data.configuration.end())
				result = std::string{ " is not in data.\n" };
			else
				result = std::string{ " is in data.\n" };
			return result;
		}()
			<< "\n\n" << query3 << [&]()
		{
			std::string result{};
			if (O1_searchable_data.find(std::ref(query3)) == O1_searchable_data.configuration.end())
				result = std::string{ " is not in data.\n" };
			else
				result = std::string{ " is in data.\n" };
			return result;
		}()
			<< "\n\n" << "The Wachowskis" << [&]()
		{
			std::string result{};
			auto x = []() { return std::string{ "The Wachowskis" }; }();
			if (O1_searchable_data.find(std::ref(x)) == O1_searchable_data.configuration.end())
				result = std::string{ " is not in data.\n" };
			else
				result = std::string{ " is in data.\n" };
			return result;
		}()
			<< "\n\n" << "Akira Kurosawa" << [&]()
		{
			std::string result{};
			if (O1_searchable_data.find([]() { return std::string{ "Akira Kurosawa" }; }()) == O1_searchable_data.configuration.end())
				result = std::string{ " is not in data.\n" };
			else
				result = std::string{ " is in data.\n" };
			return result;
		}()
			<< "\n\ndata size in bytes: " << size_of::data_in_bytes(data) << " (bytes)"
			<< "\n\nsorted data size in bytes: " << sorted_data.size_of_data_in_bytes() << " (bytes)"
			<< "\n\nsorted data size in bytes: " << O1_searchable_data.size_of_data_in_bytes() << " (bytes)"
			<< std::endl;
	};
	auto matrix_view_test = []() 
	{
		std::vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9 }; 
		std::cout << "\n\noriginal vector v:\n\n";
		iterate(v.begin(), v.size(), 1Ui64, [](int& e) 
			{ std::cout << e << ':' << reinterpret_cast<uintptr_t>(&e) << '\n'; });

		matrix_view mv(2, 4, v.begin());
		std::cout << "\n\nmatrix view v:" << mv;

		std::cout << "\n\nv row 0: ";
		auto r0 = mv.row(0);
		iterate(r0.begin(), r0.size(), 1Ui64, [](std::reference_wrapper<int>& e)
			{ std::cout << e.get() << ':' << reinterpret_cast<uintptr_t>(&e.get()) << '\t'; });

		auto r1 = mv.row(1);
		std::cout << "\n\nv row 1: ";
		iterate(r1.begin(), r1.size(), 1Ui64, [](std::reference_wrapper<int>& e)
			{ std::cout << e.get() << ':' << reinterpret_cast<uintptr_t>(&e.get()) << '\t'; });

		auto c0 = mv.column(0);
		std::cout << "\n\nv column 0: ";
		iterate(c0.begin(), c0.size(), 1Ui64, [](std::reference_wrapper<int>& e)
			{ std::cout << e.get() << ':' << reinterpret_cast<uintptr_t>(&e.get()) << '\t'; });

		auto c1 = mv.column(1);
		std::cout << "\n\nv column 1: ";
		iterate(c1.begin(), c1.size(), 1Ui64, [](std::reference_wrapper<int>& e)
			{ std::cout << e.get() << ':' << reinterpret_cast<uintptr_t>(&e.get()) << '\t'; });

		auto c2 = mv.column(2);
		std::cout << "\n\nv column 2: ";
		iterate(c2.begin(), c2.size(), 1Ui64, [](std::reference_wrapper<int>& e)
			{ std::cout << e.get() << ':' << reinterpret_cast<uintptr_t>(&e.get()) << '\t'; });

		auto c3 = mv.column(3);
		std::cout << "\n\nv column 3: ";
		iterate(c3.begin(), c3.size(), 1Ui64, [](std::reference_wrapper<int>& e)
			{ std::cout << e.get() << ':' << reinterpret_cast<uintptr_t>(&e.get()) << '\t'; });

		std::cout
			<< "\n\nmatrix view v elements:"
			<< "\n\nelement[0][0] = " << mv(0, 0) << ':' << reinterpret_cast<uintptr_t>(&mv(0, 0))
			<< "\n\nelement[0][1] = " << mv(0, 1) << ':' << reinterpret_cast<uintptr_t>(&mv(0, 1))
			<< "\n\nelement[0][2] = " << mv(0, 2) << ':' << reinterpret_cast<uintptr_t>(&mv(0, 2))
			<< "\n\nelement[0][3] = " << mv(0, 3) << ':' << reinterpret_cast<uintptr_t>(&mv(0, 3))
			<< "\n\nelement[1][0] = " << mv(1, 0) << ':' << reinterpret_cast<uintptr_t>(&mv(1, 0))
			<< "\n\nelement[1][1] = " << mv(1, 1) << ':' << reinterpret_cast<uintptr_t>(&mv(1, 1))
			<< "\n\nelement[1][2] = " << mv(1, 2) << ':' << reinterpret_cast<uintptr_t>(&mv(1, 2))
			<< "\n\nelement[1][3] = " << mv(1, 3) << ':' << reinterpret_cast<uintptr_t>(&mv(1, 3))
			<< std::endl;

		std::vector<double> w{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 };
		std::cout << "\n\noriginal vector w:\n\n";
		iterate(w.begin(), w.size(), 1Ui64, [](double& e)
			{ std::cout << e << ':' << reinterpret_cast<uintptr_t>(&e) << '\n'; });

		matrix_view mw(4, 3, w.begin());
		std::cout << "\n\nmatrix view w:" << mw;

		auto [nr, nc, mvw] = blocking::synchronous::multiplies(mv, mw);
		matrix_view mvwv(nr, nc, mvw.begin());
		std::cout << "\n\nmatrix view v x w:" << mvwv;
	};
	
	try
	{
		size_of_data_in_bytes_test();
		sorted_and_O1_searchable_views_test();
		matrix_view_test();
		
		return EXIT_SUCCESS;
	}
	catch (const std::exception& xxx)
	{
		std::cerr << xxx.what() << std::endl;
		return EXIT_FAILURE;
	}
}