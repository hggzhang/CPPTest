#include "ModernCppTestHeader.h"

namespace n_constexpr {
	constexpr int x1 = 5;
	constexpr int x2 = x1 * 2;


	constexpr int add(int x, int y) {
		return x + y;
	}
	constexpr int sum = add(7, 8);

	constexpr int str_len(const char* str) {
		return *str ? 1 + str_len(str + 1) : 0;
	}
	constexpr int hello_str_len = str_len("hello");

	constexpr int fibo(int n) {
		return (n <= 2) ? 1 : fibo(n - 1) + fibo(n - 2);
	}

	template <int N>
	struct Fibo
	{
		static const int value = fibo(N);
	};


	template<int N>
	struct ConstexprOrderArr {
		int arr[N];
		constexpr ConstexprOrderArr(){
			// C++14 constexpr 可以使用for循环
			for (size_t i = 0; i < N; i++)
			{
				arr[i] = i;
			}
		}
	};

}

void constexpr_test()
{
	LOG_FUNC();


	LOG_TAG("constexpr 常量");
	{
		LOG_VAR(n_constexpr::x1);
		LOG_VAR(n_constexpr::x2);
	}


	LOG_TAG("constexpr 函数");
	{
		LOG_VAR(n_constexpr::sum);
		LOG_VAR(n_constexpr::hello_str_len);
		LOG_VAR(n_constexpr::Fibo<5>::value);
	}


	LOG_TAG("constexpr 构造函数/对象");
	{
		n_constexpr::ConstexprOrderArr<5> a;
		for (auto e : a.arr)
		{
			LOG_VAR(e);
		}
	}
}