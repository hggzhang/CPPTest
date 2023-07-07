#include "ModernCppTestHeader.h"
#include <vector>
#include <map>


void range_for_test()
{
	LOG_FUNC();


	LOG_TAG("数组遍历");
	{
		int a[] = { 1,2,3 };
		for (int i : a)
		{
			LOG_VAR(i);
		}
	}


	LOG_TAG("标准容器vector遍历");
	{
		std::vector<int> a = { 4, 5, 6 };
		for (int i : a)
		{
			LOG_VAR(i);
		}
	}


	LOG_TAG("字符串遍历");
	{
		std::string s = "hello";
		for (char c : s)
		{
			LOG_VAR(c);
		}
	}


	LOG_TAG("map遍历");
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