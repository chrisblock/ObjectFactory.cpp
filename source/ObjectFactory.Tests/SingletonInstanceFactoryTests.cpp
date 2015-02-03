#include "stdafx.h"

#include <IContainer.h>
#include <Container.h>
#include <Registry.h>
#include <IInstanceFactory.h>
#include <SingletonInstanceFactory.h>

#include "ITestInterface.h"
#include "TestImplementation.h"

class SingletonInstanceFactoryTests : public testing::Test
{
protected:
	std::shared_ptr<IContainer> _container;
	std::shared_ptr<IInstanceFactory> _instanceFactory;

	virtual void SetUp()
	{
		_container = std::make_shared<Container>();

		_instanceFactory = std::make_shared<SingletonInstanceFactory>();
	};

	virtual void TearDown()
	{
		_container.reset();
		_instanceFactory.reset();
	};
};

TEST_F(SingletonInstanceFactoryTests, GetInstance_CreationStrategyNotSet_ThrowsException)
{
	std::string typeName = typeid (ITestInterface).name();

	EXPECT_THROW(_instanceFactory->GetInstance(*_container, typeName.c_str()), std::exception);
}

TEST_F(SingletonInstanceFactoryTests, GetInstance_CreationStrategySet_ReturnsReferenceToSameInstance)
{
	std::string typeName = typeid (ITestInterface).name();

	_instanceFactory->SetCreationStrategy(typeName.c_str(), InstantiatorFactory::CreateInstantiator<TestImplementation>());

	std::shared_ptr<void> one = _instanceFactory->GetInstance(*_container, typeName.c_str());
	std::shared_ptr<void> two = _instanceFactory->GetInstance(*_container, typeName.c_str());

	EXPECT_EQ(one, two);
}

TEST_F(SingletonInstanceFactoryTests, RemoveInstance_CreationStrategyNotSet_DoesNothing)
{
	std::string typeName = typeid (ITestInterface).name();

	EXPECT_NO_THROW(_instanceFactory->RemoveInstance(typeName.c_str()));
}

TEST_F(SingletonInstanceFactoryTests, RemoveInstance_CreationStrategySet_RemovesInstance)
{
	std::string typeName = typeid (ITestInterface).name();

	_instanceFactory->SetCreationStrategy(typeName.c_str(), InstantiatorFactory::CreateInstantiator<TestImplementation>());

	std::shared_ptr<void> one = _instanceFactory->GetInstance(*_container, typeName.c_str());

	_instanceFactory->RemoveInstance(typeName.c_str());

	std::shared_ptr<void> two = _instanceFactory->GetInstance(*_container, typeName.c_str());
	std::shared_ptr<void> three = _instanceFactory->GetInstance(*_container, typeName.c_str());

	EXPECT_NE(one, two);
	EXPECT_EQ(two, three);
}

TEST_F(SingletonInstanceFactoryTests, Remove_CreationStrategySet_RemovesTheCreationStrategyFromTheFactory)
{
	std::string typeName = typeid (ITestInterface).name();

	_instanceFactory->SetCreationStrategy(typeName.c_str(), InstantiatorFactory::CreateInstantiator<TestImplementation>());

	std::shared_ptr<void> one = _instanceFactory->GetInstance(*_container, typeName.c_str());

	EXPECT_NE(one, nullptr);

	_instanceFactory->Remove(typeName.c_str());

	EXPECT_THROW(_instanceFactory->GetInstance(*_container, typeName.c_str()), std::exception);
}
