#pragma once

#include <memory>
#include <thread>

class IContainer;
class IInstanceFactory;

class TestThread
{
public:
	TestThread() = delete;
	TestThread(const std::shared_ptr<IContainer> &container, const std::shared_ptr<IInstanceFactory> &instanceFactory);
	TestThread(const TestThread &other) = delete;
	TestThread(TestThread &&other) = delete;
	~TestThread();

	void Start();
	void Stop();

	void *GetReturnedInterfacePointer() const;

private:
	void ThreadMain();

	std::shared_ptr<IContainer> _container;
	std::shared_ptr<IInstanceFactory> _instanceFactory;
	void *_interfacePointer;
	std::thread _thread;
};
