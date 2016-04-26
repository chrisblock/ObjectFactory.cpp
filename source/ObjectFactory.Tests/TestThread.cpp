#include "stdafx.h"

#include "TestThread.h"

#include <IContainer.h>
#include <IInstanceFactory.h>

class ITestInterface;

TestThread::TestThread(const std::shared_ptr<IContainer> &container, const std::shared_ptr<IInstanceFactory> &instanceFactory) :
	  _container(container)
	, _instanceFactory(instanceFactory)
	, _interfacePointer(nullptr)
{
}

TestThread::~TestThread()
{
}

void TestThread::Start()
{
	_thread = std::thread([this] () { ThreadMain(); });
}

void TestThread::Stop()
{
	if (_thread.joinable())
	{
		_thread.join();
	}
}

void *TestThread::GetReturnedInterfacePointer() const
{
	return _interfacePointer;
}

void TestThread::ThreadMain()
{
	std::string typeName = typeid (ITestInterface).name();

	std::shared_ptr<void> result = _instanceFactory->GetInstance(*_container, typeName);

	_interfacePointer = result.get();
}
