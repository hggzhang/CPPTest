#include "ModernCppTestHeader.h"

namespace n_template{

	template <class T>
	void template_func(T t)
	{
		LOG_VAR(t);
	}

	template <class T>
	class Number
	{
	public:
		T v;
		Number(T v) : v(v)
		{
			LOG_VAR(v);
		}
	};


	template <class T>
	constexpr T pi = T(3.1415926f);

	template <int INTVAL>
	void log_template_int_value()
	{
		LOG_VAR(INTVAL);
	}


	enum class EAnim : int {
		Other = 0,
		Cat = 1,
		Dog = 2,
	};

	template<EAnim Ty>
	class Anim
	{
	public:
		void Bark() { LOG("默认：动物叫"); }
	};

	template<>
	class Anim<EAnim::Dog>
	{
	public:
		void Bark() { LOG("狗：汪汪！"); }
	};

	template<>
	class Anim<EAnim::Cat>
	{
	public:
		void Bark() { LOG("猫：喵喵！"); }
	};


	// 注意递归基
	void log_values()
	{
		LOG("展开结束");
	}

	template<class T, class... ARGS>
	void log_values(T value, ARGS... args)
	{
		LOG(value);
		log_values(args...);
	}

	template<class T>
	void func_plus(T&& a)
	{
		auto v = a;
		LOG("func_plus v = " << a);
	}

	template<class T, class... ARGS>
	void func_plus(T&& a, T&& b, ARGS... args)
	{
		func_plus(a + b, std::forward<ARGS>(args)...);
	}

	template<class T>
	void func_mul(T&& a)
	{
		auto v = a;
		LOG("func_mul v = " << a);
	}

	template<class T, class... ARGS>
	void func_mul(T&& a, T&& b, ARGS... args)
	{
		func_mul(a + b, std::forward<ARGS>(args)...);
	}

	template <class... ARGS>
	void call_func(const std::string& name, ARGS&&... args)
	{
		if (name == "plus")
			func_plus(std::forward<ARGS>(args)...);
		else if (name == "mul")
			func_mul(std::forward<ARGS>(args)...);
		else
			LOG("Unknown function name: " << name);
	}
}


template<typename T>
using Num = n_template::Number<T>;

void template_test()
{
	LOG_FUNC();

	LOG_TAG(" 函数模板 ");
	{
		n_template::template_func(1);
		n_template::template_func(1.25f);

		LOG("Lambda 函数模板");
		auto f = []<class T> (T t) { LOG_VAR(t); };
		f(1);
		f(1.25f);
	}

	LOG_TAG("类模板");
	{
		n_template::Number(1);
		n_template::Number(1.25f);
	}

	LOG_TAG("别名模板");
	{
		Num<int>(1);
		Num<float>(1.25f);
	}

	LOG_TAG("变量模板");
	{
		auto v1 = n_template::pi<int>;
		auto v2 = n_template::pi<float>;
		LOG_VAR(v1);
		LOG_VAR(v2);

		n_template::log_template_int_value<10>();
		n_template::log_template_int_value<20>();
	}

	LOG_TAG("枚举变量模板&模板特化");
	{
		n_template::Anim<n_template::EAnim::Dog>().Bark();
		n_template::Anim<n_template::EAnim::Cat>().Bark();
		LOG("EAnim::Other 没有特化使用默认模板");
		n_template::Anim<n_template::EAnim::Other>().Bark();
	}

	LOG_TAG("变长参数模板");
	{
		n_template::log_values("jack", 10, 3.14f);
	}

	LOG_TAG("变长参数模板的完美转发");
	{
		n_template::call_func("plus", 1, 2, 3, 4);
		n_template::call_func("mul", 2, 3);
	}
}