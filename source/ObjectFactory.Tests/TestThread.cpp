#include "stdafx.h"

#include "TestThread.h"

#include <IContainer.h>
#include <IInstanceFactory.h>

class ITestInterface;
//#include "ITestInterface.h"

TestThread::TestThread(const shared_ptr<IContainer> &container, const shared_ptr<IInstanceFactory> &instanceFactory) :
	  _interfacePointer(__nullptr)
	, _container(container)
	, _instanceFactory(instanceFactory)
{
}

TestThread::~TestThread()
{
}

void TestThread::Start()
{
	_thread = std::thread([this]() { ThreadMain(); });
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

	shared_ptr<void> result = _instanceFactory->GetInstance(*_container, typeName.c_str());

	_interfacePointer = result.get();
}

