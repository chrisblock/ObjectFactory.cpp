#include "stdafx.h"

#include <IContainer.h>
#include <Container.h>
#include <Exception.h>
#include <Registry.h>
#include <IInstanceFactory.h>
#include <SingletonInstanceFactory.h>

#include "ITestInterface.h"
#include "TestImplementation.h"

class SingletonInstanceFactoryTests : public testing::Test
{
protected:
	shared_ptr<IContainer> _container;
	shared_ptr<IInstanceFactory> _instanceFactory;

	virtual void SetUp()
	{
		_container = make_shared<Container>();

		_instanceFactory = make_shared<SingletonInstanceFactory>();
	};

	virtual void TearDown()
	{
		_container.reset();
		_instanceFactory.reset();
	};
};

TEST_F(SingletonInstanceFactoryTests, GetInstance_CreationStrategyNotSet_ThrowsException)
{
	auto typeName = ::ConvertToTString(typeid (ITestInterface).name());

	EXPECT_THROW(_instanceFactory->GetInstance(*_container, typeName.c_str()), Exception*);
}

TEST_F(SingletonInstanceFactoryTests, GetInstance_CreationStrategySet_ReturnsReferenceToSameInstance)
{
	auto typeName = ::ConvertToTString(typeid (ITestInterface).name());

	_instanceFactory->SetCreationStrategy(typeName.c_str(), InstantiatorFactory::CreateInstantiator<TestImplementation>());

	shared_ptr<void> one = _instanceFactory->GetInstance(*_container, typeName.c_str());
	shared_ptr<void> two = _instanceFactory->GetInstance(*_container, typeName.c_str());

	EXPECT_EQ(one, two);
}

TEST_F(SingletonInstanceFactoryTests, Remove_CreationStrategySet_RemovesTheCreationStrategyFromTheFactory)
{
	auto typeName = ::ConvertToTString(typeid (ITestInterface).name());

	_instanceFactory->SetCreationStrategy(typeName.c_str(), InstantiatorFactory::CreateInstantiator<TestImplementation>());

	shared_ptr<void> one = _instanceFactory->GetInstance(*_container, typeName.c_str());

	EXPECT_NE(one, __nullptr);

	_instanceFactory->Remove(typeName.c_str());

	EXPECT_THROW(_instanceFactory->GetInstance(*_container, typeName.c_str()), Exception*);
}
