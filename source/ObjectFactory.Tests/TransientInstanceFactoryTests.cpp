#include "stdafx.h"

#include <IContainer.h>
#include <Container.h>
#include <Registry.h>
#include <IInstanceFactory.h>
#include <TransientInstanceFactory.h>

#include "ITestInterface.h"
#include "TestImplementation.h"

class TransientInstanceFactoryTests : public testing::Test
{
protected:
	shared_ptr<IContainer> _container;
	shared_ptr<IInstanceFactory> _instanceFactory;

	virtual void SetUp()
	{
		_container = make_shared<Container>();

		_instanceFactory = make_shared<TransientInstanceFactory>();
	};

	virtual void TearDown()
	{
		_container.reset();
		_instanceFactory.reset();
	};
};

TEST_F(TransientInstanceFactoryTests, GetInstance_CreationStrategyNotSet_ThrowsException)
{
	std::string typeName = typeid (ITestInterface).name();

	EXPECT_THROW(_instanceFactory->GetInstance(*_container, typeName.c_str()), std::exception);
}

TEST_F(TransientInstanceFactoryTests, GetInstance_CreationStrategySet_ReturnsDifferentInstances)
{
	std::string typeName = typeid (ITestInterface).name();

	_instanceFactory->SetCreationStrategy(typeName.c_str(), InstantiatorFactory::CreateInstantiator<TestImplementation>());

	shared_ptr<void> one = _instanceFactory->GetInstance(*_container, typeName.c_str());
	shared_ptr<void> two = _instanceFactory->GetInstance(*_container, typeName.c_str());

	EXPECT_NE(one, two);
}

TEST_F(TransientInstanceFactoryTests, Remove_CreationStrategySet_RemovesTheCreationStrategyFromTheFactory)
{
	std::string typeName = typeid (ITestInterface).name();

	_instanceFactory->SetCreationStrategy(typeName.c_str(), InstantiatorFactory::CreateInstantiator<TestImplementation>());

	shared_ptr<void> one = _instanceFactory->GetInstance(*_container, typeName.c_str());

	EXPECT_NE(one, __nullptr);

	_instanceFactory->Remove(typeName.c_str());

	EXPECT_THROW(_instanceFactory->GetInstance(*_container, typeName.c_str()), std::exception);
}
