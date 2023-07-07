#include "ModernCppTestHeader.h"
#include <memory>

#define LOG_UNIQUE_PTR_VALID(ptr) if(ptr) LOG(#ptr << " unique_ptr valid"); else LOG(#ptr << " unique_ptr invalid")
#define LOG_WEAK_PTR_IF_VALID(ptr, exp) if(auto tp = p2.lock()) exp else LOG(#ptr << " weak_ptr invalid")

namespace n_smart_pointer {
	class Obj {
	public:
		Obj(int ID) : ID(ID) { LOG("Obj addr " << this << " ID " << ID << " Create"); }
		~Obj() { LOG("Obj addr " << this << " ID " << ID << " Release"); }

		int ID;
	};

	class Item {};
}

using LocaObj = n_smart_pointer::Obj;

void smart_pointer_test()
{
	LOG_FUNC();


	LOG_TAG("std::shared_ptr ����ָ��");
	{
		{
			std::shared_ptr<LocaObj> p1 = std::make_shared<LocaObj>(1);
			{
				std::shared_ptr<LocaObj> p2 = p1;
				LOG_VAR_DESC(p1->ID, " p1->ID");
				LOG_VAR_DESC(p2->ID, " p2->ID");
				LOG("p2 �뿪������");
			}
			LOG("p1 �뿪������");
		}
	}


	LOG_TAG("std::shared_ptr ����ָ���������ʽ");
	{
		std::shared_ptr<LocaObj> p1(new LocaObj(1));
		std::shared_ptr<LocaObj> p2 = std::make_shared<LocaObj>(2);
		std::shared_ptr<LocaObj> p3(p2);
	}


	LOG_TAG("std::unique_ptr Ψһָ��");
	{
		{
			std::unique_ptr<LocaObj> p1;
			{
				std::unique_ptr<LocaObj> p2 = std::make_unique<LocaObj>(1);
				LOG_VAR_DESC(p2->ID, " p2->ID");

				LOG("Ψһָ��ת�ƿ���Ȩʹ��=�����������ʹ��std::move()");
				// std::unique_ptr<LocaObj> p1 = p2;
				p1 = std::move(p2);
				LOG_VAR_DESC(p1->ID, " p1->ID");

				LOG("���Ա�std::move��p2�Ƿ���Ч�����Կ��� ��Ч");
				LOG_UNIQUE_PTR_VALID(p2);
				LOG("p2 �뿪������, IDΪ1��Objû������");
			}

			LOG("p1 �뿪������ IDΪ1��Obj����");
		}
	}


	LOG_TAG("std::unique_ptr Ψһָ���������ʽ");
	{
		std::unique_ptr<LocaObj> p1(new LocaObj(1));
		std::unique_ptr<LocaObj> p2 = std::make_unique<LocaObj>(2);
		std::unique_ptr<LocaObj> p3(std::move(p2));
	}


	LOG_TAG("std::weak_ptr ��ָ��");
	{
		std::shared_ptr<LocaObj> p1 = std::make_shared<LocaObj>(1);
		std::weak_ptr<LocaObj> p2 = p1;

		LOG_VAR_DESC(p1->ID, " p1->ID");
		LOG_WEAK_PTR_IF_VALID(p2, LOG_VAR_DESC(tp->ID, " p2->ID"););

		LOG("p1 reset Obj�����ͷ�");
		p1.reset();

		LOG("p2 ��ָ��ʧЧ");
		LOG_WEAK_PTR_IF_VALID(p2, LOG_VAR_DESC(tp->ID, " p2->ID"););
	}
}