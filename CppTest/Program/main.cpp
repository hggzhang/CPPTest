#include "Header.h"
#include <stdexcept>

void test()
{
	modern_cpp_test_main();
}

int main()
{
	try {
		test();
	}
	catch (const std::invalid_argument& e) {
		std::cerr << "�����쳣: " << e.what() << std::endl;
	}

	return 0;
}
