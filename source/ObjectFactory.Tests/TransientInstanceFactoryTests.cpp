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
	std::shared_ptr<IContainer> _container;
	std::shared_ptr<IInstanceFactory> _instanceFactory;

	virtual void SetUp()
	{
		_container = std::make_shared<Container>();

		_instanceFactory = std::make_shared<TransientInstanceFactory>();
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

	std::shared_ptr<void> one = _instanceFactory->GetInstance(*_container, typeName.c_str());
	std::shared_ptr<void> two = _instanceFactory->GetInstance(*_container, typeName.c_str());

	EXPECT_NE(one, two);
}

TEST_F(TransientInstanceFactoryTests, RemoveInstance_CreationStrategyNotSet_DoesNothing)
{
	std::string typeName = typeid (ITestInterface).name();

	EXPECT_NO_THROW(_instanceFactory->RemoveInstance(typeName.c_str()));
}

TEST_F(TransientInstanceFactoryTests, Remove_CreationStrategySet_RemovesTheCreationStrategyFromTheFactory)
{
	std::string typeName = typeid (ITestInterface).name();

	_instanceFactory->SetCreationStrategy(typeName.c_str(), InstantiatorFactory::CreateInstantiator<TestImplementation>());

	std::shared_ptr<void> one = _instanceFactory->GetInstance(*_container, typeName.c_str());

	EXPECT_NE(one, __nullptr);

	_instanceFactory->Remove(typeName.c_str());

	EXPECT_THROW(_instanceFactory->GetInstance(*_container, typeName.c_str()), std::exception);
}
