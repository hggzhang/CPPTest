#include "ModernCppTestHeader.h"
#include <functional>

using std::function;
using std::bind;

namespace n_lambda {
	class Class1
	{
	public:
		auto F() 
		{ 
			return [this]() {return val; };
		};

		int val = 123;
	};

	class Class2
	{
	public:

		int F(int x) { return a + x; };
	private:
		int a = 10;
	};
}

void lambda_test()
{
	LOG_FUNC();

	LOG_TAG("常用");
	{
		auto f = [](auto a, auto b) {return a + b; };
		int v = f(1, 2);
		LOG_VAR(v);
	}

	LOG_TAG("C++14 默认实参");
	{
		auto f = [](auto a, int b = 10) {return a + b; };
		auto v = f(5);
		LOG_VAR(v);
	}


	LOG_TAG("被std::function捕获 （会带来一些开销）");
	{
		function<int(int, int)> f = [](int a, int b) {return a + b; };
		auto v = f(3, 4);
		LOG_VAR(v);
	}


	LOG_TAG("捕获参数");
	{
		int a = 1;
		int b = 2;
		int c = 3;

		auto f1 = [=]() {return a + b; };
		auto f2 = [&]() {return a + b; };
		auto f3 = [&b, c](int x) {return x + b + c; };

		b = 12;
		c = 13;

		auto v1 = f1();
		LOG_VAR_DESC(v1, "[=]拷贝全部");

		auto v2 = f2();
		LOG_VAR_DESC(v2, "[&]引用全部");

		auto v3 = f3(1);
		LOG_VAR_DESC(v3, "一个引用， 一个拷贝");
	}


	LOG_TAG("this作用域测试");
	{
		function<int()> f;
		{
			n_lambda::Class1 t;
			f = t.F();
			int v = f();
			LOG_VAR_DESC(v, "t 对象在作用域{}内， 正确");
		}
		int v = f();
		// 注意，有可能值是对的，根据切豆腐理论，如果t对象的生命周期结束了，但是未被内存管理回收，那么它依然可以使用
		LOG_VAR_DESC(v, "t 对象在作用域{}外， 导致lambda捕获的this指针空悬，未定义行为，值有可能出错");
	}


	LOG_TAG("使用bind绑定对象的成员函数到function对象");
	{
		n_lambda::Class2 t;
		function<int(int)> f = bind(&n_lambda::Class2::F, &t, std::placeholders::_1);
		int v = f(5);
		LOG_VAR(v);
	}


	LOG_TAG(" 【C++ 20】 模板 lambda");
	{
		auto f = []<class T> (T t) { LOG_VAR(t); };
		f(1);
		f(1.25f);
	}
}