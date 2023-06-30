#pragma once
#include <iostream>
#include <utility>
#include <string>
#include <typeinfo>

#define LOG(any) cout << any << endl

#define LOG_VAR(var) LOG(#var << " = " << var)
#define LOG_VAR_DESC(var, desc) LOG(#var << " = " << var << "  £¨" << desc << ")")

#define LOG_VAR_TYPE(var) LOG(#var << " is " << typeid(var).name())
#define LOG_VAR_IS_TYPE(var, ty) \\
	if (std::is_same_v<decltype(var), ty>) \\
		LOG("yes"); \\
	else \\
		LOG("no"); \\
	LOG_VAR_TYPE(var)

#define LOG_TAG(tag) LOG("------------------------------------------------------------------------------------------------------------------- ");LOG("--------- "  << tag); LOG("------------------------------------------------------------------------------------------------------------------- ")

#define LOG_FUNC() TestFuncLogger __log(__FUNCTION__)


using std::cout;
using std::cin;
using std::endl;



//					Tools
class TestFuncLogger
{
public:
	TestFuncLogger(std::string name)
	{
		this->name = name;
		cout << " ==== ¡¾" << name << "¡¿ Start " << " ==== " << endl;
	}

	~TestFuncLogger()
	{
		cout << " ==== ¡¾" << name << "¡¿  End  " << " ==== " << endl;
	}

private:
	std::string name;
};


//					CPP 11

void auto_decltype_test();

void lambda_test();

void rvalueref_stdmove_test();

