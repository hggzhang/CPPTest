#include "ModernCppTestHeader.h"
#include <string>Str
using std::string;

namespace n_rvalueref {
	class Str {
	public:
		Str() {
			LOG("�޲ι���");
			this->str = new string();
		}

		Str(const string& str) {
			LOG("�вι��� str = " << str);
			this->str = new string(str);
		}

		Str(const Str& obj) {
			LOG("�������� obj.str = " << *obj.str);
			this->str = new string(*obj.str);
		}

		Str(Str&& obj) noexcept {
			LOG("�ƶ����� obj.str = " << *obj.str);
			this->str = std::move(obj.str);
			// ���ƶ��Ķ���Ӧ���ٱ�ʹ����
			obj.str = nullptr;
		}

		Str& operator=(Str&& v) noexcept {
			LOG("�ƶ����� operator = ");

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

// ��ֵ����&�ƶ�����
void rvalueref_stdmove_test()
{
	LOG_FUNC();

	LOG_TAG("��������");
	{
		Str t1("A");
		Str t2 = t1;
		LOG_VAR(*t2.str);
	}


	LOG_TAG("�ƶ�����, ע�ⱻ�ƶ��Ķ���t1��Ӧ�ٱ�ʹ��");
	{
		// t1����ֵ��ʹ��std::moveǿ��ת������ֵ
		Str t1("A");
		Str t2 = std::move(t1);
		LOG_VAR(*t2.str);
	}


	LOG_TAG("�ƶ��������������أ�ע����������ط�����ֵ���㣨������ӣ��������ǹ������㣨�ϸ����ӣ�");
	{
		Str t1("A");
		Str t2;
		t2 = std::move(t1);
	}


	LOG_TAG("����������ʾʹ��std::moveת�������������׺��ӵķ����ƶ����쳡���о�");
	{
		LOG("---1 �����ӷ���������ʱ����c++�᳢��ʹ���ƶ���������Ż�");
		Str t1("A");
		Str t2("B");
		Str t3("C");
		Str t4;
		t4 = t1 + t2 + t3;

		LOG("---2 �������ص���ʱ����c++�᳢��ʹ���ƶ���������Ż�");
		auto f = []() {
			auto s = Str("Hi"); 
			return s; 
		};
		Str t5 = f();

		/*
		- �������в����ɾ��Ԫ�أ����� std::vector::push_back��������ݸ���������ֵ�����ͻ�ʹ���ƶ����塣
		- �ڱ�׼���㷨�У�����׼���㷨������ std::sort��std::partition �ȣ��ڽ���Ԫ�ؽ���ʱ��ʹ���ƶ����塣
		- �� std::swap �У�std::swap ��ʹ���ƶ�������������������
		*/
	}

}