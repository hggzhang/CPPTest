#include "ModernCppTestHeader.h"

namespace n_auto {

	template <class T, class U>
	auto add(T t, U u) { return t + u; }

	// C++ 支持值模板
	template <auto n>
	auto f() -> std::pair<decltype(n), decltype(n)>
	{
		return { n, n };
	}

	// 完美转发必须用 decltype(auto)
	template <class F, class... Args>
	decltype(auto) pref_forward(F f, Args&&... args)
	{
		return f(std::forward<Args>(args)...);
	}
}

void auto_decltype_test()
{
	LOG_FUNC();


	LOG_TAG("auto&decltype 推导变量");
	auto a0				= 1 + 2;
	auto a1				= a0;
	decltype(auto) a2	= a0;
	decltype(auto) a3	= (a0);
	auto a4				= { 1, 2 };
	auto a5               {10}; //使用{}构造器
	auto [a6, a7]		= n_auto::f<0>(); //结构化绑定
	auto a8				= n_auto::add(1, 1.2);

	LOG_VAR_TYPE(a0);
	LOG_VAR_TYPE(a1);
	LOG_VAR_TYPE(a2);
	LOG_VAR_TYPE(a3);
	LOG_VAR_TYPE(a4);
	LOG_VAR_TYPE(a5);
	LOG_VAR(a6);
	LOG_VAR_TYPE(a6);
	LOG_VAR(a7);
	LOG_VAR_TYPE(a7);
	LOG_VAR_TYPE(a8);


	LOG_TAG("auto 用于指代lambda");
	auto b0 = [](int x) {LOG_VAR(x); };
	b0(10);


	LOG_TAG("decltype(auto) 用于完美转发");
	auto c0 = [](int x1, int x2) {return x1 + x2; };
	auto c1 = n_auto::pref_forward(c0, 1, 5);
	LOG_VAR(c1);
	
}