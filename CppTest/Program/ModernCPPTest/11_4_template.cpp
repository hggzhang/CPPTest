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
		void Bark() { LOG("Ĭ�ϣ������"); }
	};

	template<>
	class Anim<EAnim::Dog>
	{
	public:
		void Bark() { LOG("����������"); }
	};

	template<>
	class Anim<EAnim::Cat>
	{
	public:
		void Bark() { LOG("è��������"); }
	};


	// ע��ݹ��
	void log_values()
	{
		LOG("չ������");
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

	LOG_TAG(" ����ģ�� ");
	{
		n_template::template_func(1);
		n_template::template_func(1.25f);

		LOG("Lambda ����ģ��");
		auto f = []<class T> (T t) { LOG_VAR(t); };
		f(1);
		f(1.25f);
	}

	LOG_TAG("��ģ��");
	{
		n_template::Number(1);
		n_template::Number(1.25f);
	}

	LOG_TAG("����ģ��");
	{
		Num<int>(1);
		Num<float>(1.25f);
	}

	LOG_TAG("����ģ��");
	{
		auto v1 = n_template::pi<int>;
		auto v2 = n_template::pi<float>;
		LOG_VAR(v1);
		LOG_VAR(v2);

		n_template::log_template_int_value<10>();
		n_template::log_template_int_value<20>();
	}

	LOG_TAG("ö�ٱ���ģ��&ģ���ػ�");
	{
		n_template::Anim<n_template::EAnim::Dog>().Bark();
		n_template::Anim<n_template::EAnim::Cat>().Bark();
		LOG("EAnim::Other û���ػ�ʹ��Ĭ��ģ��");
		n_template::Anim<n_template::EAnim::Other>().Bark();
	}

	LOG_TAG("�䳤����ģ��");
	{
		n_template::log_values("jack", 10, 3.14f);
	}

	LOG_TAG("�䳤����ģ�������ת��");
	{
		n_template::call_func("plus", 1, 2, 3, 4);
		n_template::call_func("mul", 2, 3);
	}
}