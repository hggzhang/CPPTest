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
		std::cerr << "²¶»ñµ½Òì³£: " << e.what() << std::endl;
	}

	return 0;
}
