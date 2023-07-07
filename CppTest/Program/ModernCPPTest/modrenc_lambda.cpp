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

	LOG_TAG("����");
	{
		auto f = [](auto a, auto b) {return a + b; };
		int v = f(1, 2);
		LOG_VAR(v);
	}

	LOG_TAG("C++14 Ĭ��ʵ��");
	{
		auto f = [](auto a, int b = 10) {return a + b; };
		auto v = f(5);
		LOG_VAR(v);
	}


	LOG_TAG("��std::function���� �������һЩ������");
	{
		function<int(int, int)> f = [](int a, int b) {return a + b; };
		auto v = f(3, 4);
		LOG_VAR(v);
	}


	LOG_TAG("�������");
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
		LOG_VAR_DESC(v1, "[=]����ȫ��");

		auto v2 = f2();
		LOG_VAR_DESC(v2, "[&]����ȫ��");

		auto v3 = f3(1);
		LOG_VAR_DESC(v3, "һ�����ã� һ������");
	}


	LOG_TAG("this���������");
	{
		function<int()> f;
		{
			n_lambda::Class1 t;
			f = t.F();
			int v = f();
			LOG_VAR_DESC(v, "t ������������{}�ڣ� ��ȷ");
		}
		int v = f();
		// ע�⣬�п���ֵ�ǶԵģ������ж������ۣ����t������������ڽ����ˣ�����δ���ڴ������գ���ô����Ȼ����ʹ��
		LOG_VAR_DESC(v, "t ������������{}�⣬ ����lambda�����thisָ�������δ������Ϊ��ֵ�п��ܳ���");
	}


	LOG_TAG("ʹ��bind�󶨶���ĳ�Ա������function����");
	{
		n_lambda::Class2 t;
		function<int(int)> f = bind(&n_lambda::Class2::F, &t, std::placeholders::_1);
		int v = f(5);
		LOG_VAR(v);
	}


	LOG_TAG(" ��C++ 20�� ģ�� lambda");
	{
		auto f = []<class T> (T t) { LOG_VAR(t); };
		f(1);
		f(1.25f);
	}
}