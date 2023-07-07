#include "ModernCppTestHeader.h"
#include <thread>
#include <future>
#include <mutex>


namespace n_thread {
	void increment(int n)
	{
		int i = 0;
		while (++i < n)
		{
			LOG_VAR(i);
		}
	}

	int accumulate(int n)
	{
		int r = 0;
		for (size_t i = 0; i <= n; i++)
		{
			r += i;
		}

		LOG_VAR(r);
		return r;
	}

	void accumulate_p(int n, std::promise<int> p)
	{
		int r = accumulate(n);
		p.set_value(r);
	}

	std::mutex mtx;
	void print_block_sync(int n, char c)
	{
		std::lock_guard<std::mutex> guard(mtx);

		for (int i = 0; i < n; ++i) {
			std::cout << c;
		}
		std::cout << '\n';
	}

	void print_block_async(int n, char c)
	{
		for (int i = 0; i < n; ++i) {
			std::cout << c;
		}
		std::cout << '\n';
	}

	class Number
	{
	public:
		Number(int v) :v(v) {}
		int v;
	};

	

	void counter_async(Number* num, int n)
	{
		for (int i = 0; i < n; ++i) {
			num->v++;
		}
	}

	void counter_sync(std::atomic<int>* v, int n)
	{
		for (int i = 0; i < n; ++i) {
			++(*v);
		}
	}
}

void thread_test()
{
	LOG_FUNC();


	LOG_TAG("�̴߳���");
	{
		std::thread t(n_thread::increment, 3);
		t.join();
		LOG("main thread goes on");
	}


	LOG_TAG("�첽���� ʹ�� future&async");
	{
		std::future<int> f = std::async(n_thread::accumulate, 3);

		LOG("�ȴ��첽����");
		int sum = f.get();
		LOG_VAR(sum);
	}


	LOG_TAG("�첽���� ʹ�� future&promise");
	{
		std::promise<int> p;
		std::future<int> f = p.get_future();
		std::thread t(n_thread::accumulate_p, 3, std::move(p));
		LOG("�ȴ��첽����");
		int sum = f.get();
		LOG_VAR(sum);
		t.join();
	}


	LOG_TAG("����ͬ��");
	{
		{
			LOG("��ͬ��");
			std::thread t1(n_thread::print_block_async, 50, '#');
			std::thread t2(n_thread::print_block_async, 50, '$');
			t1.join();
			t2.join();
		}

		{
			LOG("ͬ��");
			std::thread t1(n_thread::print_block_sync, 50, '#');
			std::thread t2(n_thread::print_block_sync, 50, '$');
			t1.join();
			t2.join();
		}
	}

	LOG_TAG("����ͬ��");
	{
		{
			LOG("��ͬ��, �п�������ȷ���㣬���ǲ��ȶ�");
			n_thread::Number n(0);
			std::thread t1(n_thread::counter_async, &n, 100000);
			std::thread t2(n_thread::counter_async, &n, 100000);
			t1.join();
			t2.join();
			LOG_VAR(n.v);
		}

		{
			LOG("ͬ��");
			std::atomic<int> v(0);
			std::thread t1(n_thread::counter_sync, &v, 100000);
			std::thread t2(n_thread::counter_sync, &v, 100000);
			t1.join();
			t2.join();
			LOG_VAR(v);
		}
	}

}