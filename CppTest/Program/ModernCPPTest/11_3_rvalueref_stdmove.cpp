#include "ModernCppTestHeader.h"
#include <string>Str
using std::string;

namespace n_rvalueref {
	class Str {
	public:
		Str() {
			LOG("无参构造");
			this->str = new string();
		}

		Str(const string& str) {
			LOG("有参构造 str = " << str);
			this->str = new string(str);
		}

		Str(const Str& obj) {
			LOG("拷贝构造 obj.str = " << *obj.str);
			this->str = new string(*obj.str);
		}

		Str(Str&& obj) noexcept {
			LOG("移动构造 obj.str = " << *obj.str);
			this->str = std::move(obj.str);
			// 被移动的对象不应该再被使用了
			obj.str = nullptr;
		}

		Str& operator=(Str&& v) noexcept {
			LOG("移动语义 operator = ");

			if (this != &v) {
				this->str = std::move(v.str);
			}

			return *this;
		}

		Str operator+(const Str& v)
		{
			string s = *this->str + *v.str;
			return Str(s);
		}

		void Log()
		{
			LOG(str);
		}

		string* str;
	};
}

using n_rvalueref::Str;

// 右值引用&移动语义
void rvalueref_stdmove_test()
{
	LOG_FUNC();

	LOG_TAG("拷贝构造");
	{
		Str t1("A");
		Str t2 = t1;
		LOG_VAR(*t2.str);
	}


	LOG_TAG("移动构造, 注意被移动的对象t1不应再被使用");
	{
		// t1是左值，使用std::move强制转换成右值
		Str t1("A");
		Str t2 = std::move(t1);
		LOG_VAR(*t2.str);
	}


	LOG_TAG("移动语义的运算符重载，注意运算符重载发生赋值运算（这个例子），而不是构造运算（上个例子）");
	{
		Str t1("A");
		Str t2;
		t2 = std::move(t1);
	}


	LOG_TAG("除了上述显示使用std::move转换，常见的容易忽视的发生移动构造场合列举");
	{
		LOG("---1 连续加法产生的临时对象，c++会尝试使用移动语义进行优化");
		Str t1("A");
		Str t2("B");
		Str t3("C");
		Str t4;
		t4 = t1 + t2 + t3;

		LOG("---2 函数返回的临时对象，c++会尝试使用移动语义进行优化");
		auto f = []() {
			auto s = Str("Hi"); 
			return s; 
		};
		Str t5 = f();

		/*
		- 在容器中插入或删除元素：比如 std::vector::push_back，如果传递给它的是右值，它就会使用移动语义。
		- 在标准库算法中：许多标准库算法，比如 std::sort，std::partition 等，在进行元素交换时会使用移动语义。
		- 在 std::swap 中：std::swap 会使用移动语义来交换两个对象。
		*/
	}

}