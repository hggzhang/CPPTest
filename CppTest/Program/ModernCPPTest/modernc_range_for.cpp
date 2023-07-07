#include "ModernCppTestHeader.h"
#include <vector>
#include <map>


void range_for_test()
{
	LOG_FUNC();


	LOG_TAG("�������");
	{
		int a[] = { 1,2,3 };
		for (int i : a)
		{
			LOG_VAR(i);
		}
	}


	LOG_TAG("��׼����vector����");
	{
		std::vector<int> a = { 4, 5, 6 };
		for (int i : a)
		{
			LOG_VAR(i);
		}
	}


	LOG_TAG("�ַ�������");
	{
		std::string s = "hello";
		for (char c : s)
		{
			LOG_VAR(c);
		}
	}


	LOG_TAG("map����");
	{
		std::map<std::string, int> m = {
			{"jack", 18},
			{"ben", 24},
			{"lucy", 28},
		};

		for (const auto& p : m)
		{
			LOG("p key = " << p.first << " value = " << p.second);
		}
	}
}