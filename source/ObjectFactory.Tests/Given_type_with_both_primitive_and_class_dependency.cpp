#include "stdafx.h"

#include <LambdaInstantiator.h>

#include <Container.h>
#include <Registry.h>

class Dependency
{
public:
	Dependency() = default;
	Dependency(const Dependency &other) = default;
	Dependency(Dependency &&other) = default;
	virtual ~Dependency() = default;

	Dependency &operator =(const Dependency &other) = default;
	Dependency &operator =(Dependency &&other) = default;
};

class TypeWithBothPrimitiveAndClassDependency
{
public:
	TypeWithBothPrimitiveAndClassDependency(const std::shared_ptr<Dependency> &dependency, const std::int32_t timeout) :
		  _timeout(timeout)
		, _dependency(dependency)
	{
	};

	TypeWithBothPrimitiveAndClassDependency(const TypeWithBothPrimitiveAndClassDependency &other) = default;
	TypeWithBothPrimitiveAndClassDependency(TypeWithBothPrimitiveAndClassDependency &&other) = default;

	TypeWithBothPrimitiveAndClassDependency &operator =(const TypeWithBothPrimitiveAndClassDependency &other) = default;
	TypeWithBothPrimitiveAndClassDependency &operator =(TypeWithBothPrimitiveAndClassDependency &&other) = default;

private:
	std::int32_t _timeout;
	std::shared_ptr<Dependency> _dependency;
};

class TypeWithBothPrimitiveAndClassDependencyTestRegistry : public Registry
{
public:
	void Register(_Inout_ IContainer &container) const override
	{
		container.Register<Dependency>();
	};
};

class Given_type_with_both_primitive_and_class_dependency : public ::testing::Test
{
protected:
	virtual void SetUp() override
	{
	};

	virtual void TearDown() override
	{
	};
};

TEST_F(Given_type_with_both_primitive_and_class_dependency, When_getting_type_name_Then_type_is_returned)
{
	LambdaInstantiator<TypeWithBothPrimitiveAndClassDependency, Dependency> instantiator([](const std::shared_ptr<Dependency> &dependency) { return std::make_shared<TypeWithBothPrimitiveAndClassDependency>(dependency, 42); });

	std::string expected = typeid (TypeWithBothPrimitiveAndClassDependency).name();

	EXPECT_EQ(expected, instantiator.GetType());
}

TEST_F(Given_type_with_both_primitive_and_class_dependency, When_getting_dependencies_Then_empty_list_is_returned)
{
	LambdaInstantiator<TypeWithBothPrimitiveAndClassDependency, Dependency> instantiator([](const std::shared_ptr<Dependency> &dependency) { return std::make_shared<TypeWithBothPrimitiveAndClassDependency>(dependency, 42); });
	
	std::vector<std::string> expected = { typeid (Dependency).name() };

	std::vector<std::string> actual = instantiator.GetDependencies();

	EXPECT_EQ(expected, actual);
}

TEST_F(Given_type_with_both_primitive_and_class_dependency, When_instance_is_created_Then_instance_is_returned)
{
	TypeWithBothPrimitiveAndClassDependencyTestRegistry registry;

	Container container(registry);

	LambdaInstantiator<TypeWithBothPrimitiveAndClassDependency, Dependency> instantiator([](const std::shared_ptr<Dependency> &dependency) { return std::make_shared<TypeWithBothPrimitiveAndClassDependency>(dependency, 42); });

	std::shared_ptr<void> actual = instantiator.CreateInstance(container);

	EXPECT_NE(nullptr, actual);
}

TEST_F(Given_type_with_both_primitive_and_class_dependency, When_instance_is_created_Then_new_instance_is_returned_every_time)
{
	TypeWithBothPrimitiveAndClassDependencyTestRegistry registry;

	Container container(registry);

	LambdaInstantiator<TypeWithBothPrimitiveAndClassDependency, Dependency> instantiator([](const std::shared_ptr<Dependency> &dependency) { return std::make_shared<TypeWithBothPrimitiveAndClassDependency>(dependency, 42); });

	std::shared_ptr<void> one = instantiator.CreateInstance(container);
	std::shared_ptr<void> two = instantiator.CreateInstance(container);

	EXPECT_NE(one, two);
}
