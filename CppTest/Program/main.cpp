#include "ModernCPPTest/TestHeader.h"
#include <stdexcept>

void test()
{
	// auto_decltype_test();

	// lambda_test();

	rvalueref_stdmove_test();
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
