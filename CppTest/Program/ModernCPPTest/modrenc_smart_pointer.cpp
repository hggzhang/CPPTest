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


	LOG_TAG("std::shared_ptr 共享指针");
	{
		{
			std::shared_ptr<LocaObj> p1 = std::make_shared<LocaObj>(1);
			{
				std::shared_ptr<LocaObj> p2 = p1;
				LOG_VAR_DESC(p1->ID, " p1->ID");
				LOG_VAR_DESC(p2->ID, " p2->ID");
				LOG("p2 离开作用域");
			}
			LOG("p1 离开作用域");
		}
	}


	LOG_TAG("std::shared_ptr 共享指针的声明方式");
	{
		std::shared_ptr<LocaObj> p1(new LocaObj(1));
		std::shared_ptr<LocaObj> p2 = std::make_shared<LocaObj>(2);
		std::shared_ptr<LocaObj> p3(p2);
	}


	LOG_TAG("std::unique_ptr 唯一指针");
	{
		{
			std::unique_ptr<LocaObj> p1;
			{
				std::unique_ptr<LocaObj> p2 = std::make_unique<LocaObj>(1);
				LOG_VAR_DESC(p2->ID, " p2->ID");

				LOG("唯一指针转移控制权使用=运算符报错，须使用std::move()");
				// std::unique_ptr<LocaObj> p1 = p2;
				p1 = std::move(p2);
				LOG_VAR_DESC(p1->ID, " p1->ID");

				LOG("测试被std::move的p2是否还有效，可以看到 无效");
				LOG_UNIQUE_PTR_VALID(p2);
				LOG("p2 离开作用域, ID为1的Obj没有析构");
			}

			LOG("p1 离开作用域， ID为1的Obj析构");
		}
	}


	LOG_TAG("std::unique_ptr 唯一指针的声明方式");
	{
		std::unique_ptr<LocaObj> p1(new LocaObj(1));
		std::unique_ptr<LocaObj> p2 = std::make_unique<LocaObj>(2);
		std::unique_ptr<LocaObj> p3(std::move(p2));
	}


	LOG_TAG("std::weak_ptr 弱指针");
	{
		std::shared_ptr<LocaObj> p1 = std::make_shared<LocaObj>(1);
		std::weak_ptr<LocaObj> p2 = p1;

		LOG_VAR_DESC(p1->ID, " p1->ID");
		LOG_WEAK_PTR_IF_VALID(p2, LOG_VAR_DESC(tp->ID, " p2->ID"););

		LOG("p1 reset Obj对象被释放");
		p1.reset();

		LOG("p2 弱指针失效");
		LOG_WEAK_PTR_IF_VALID(p2, LOG_VAR_DESC(tp->ID, " p2->ID"););
	}
}