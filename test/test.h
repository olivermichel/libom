
#include <iostream>
#include <iomanip>

namespace test {

	static std::string current_test_name;

	static const std::string pass = " \x1b[32m[PASS]\x1b[0m";
	static const std::string fail = " \x1b[31m[FAIL]\x1b[0m";
	static const size_t desc_width = 80;

	void set_name(std::string name)
	{
		current_test_name = name;
	}

	template<typename T>
	bool expect_equal(T a, T b, std::string desc)
	{
		std::cout << std::setw(desc_width) << std::left
			<< (current_test_name + ": " + desc + " (==)");

		if(a == b) {
			std::cout << pass << std::endl;
			return true;
		} else {
			std::cout << fail << std::endl;
			return false;
		}
	}

	template<typename T>
	bool expect_not_equal(T a, T b, std::string desc)
	{
		std::cout << std::setw(desc_width) << std::left
			<< (current_test_name + ": " + desc + " (!=)");

		if(a != b) {
			std::cout << pass << std::endl;
			return true;
		} else {
			std::cout << fail << std::endl;
			return false;
		}
	}

	template<typename T>
	bool expect_true(T a, std::string desc)
	{
		std::cout << std::setw(desc_width) << std::left
			<< (current_test_name + ": " + desc + " (T)");

		if(a) {
			std::cout << pass << std::endl;
			return true;
		} else {
			std::cout << fail << std::endl;
			return false;
		}
	}

	template<typename T>
	bool expect_false(T a, std::string desc)
	{
		std::cout << std::setw(desc_width) << std::left 
			<< (current_test_name + ": " + desc + " (F)");

		if(!a) {
			std::cout << pass << std::endl;
			return true;
		} else {
			std::cout << fail << std::endl;
			return false;
		}
	}

};
