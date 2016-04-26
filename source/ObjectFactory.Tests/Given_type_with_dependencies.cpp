#include "stdafx.h"

#include <VariadicArgumentInstantiator.h>

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

class TypeWithDependencies
{
public:
	TypeWithDependencies(const std::shared_ptr<Dependency> &dependency) :
		_dependency(dependency)
	{
	};

	TypeWithDependencies(const TypeWithDependencies &other) = default;
	TypeWithDependencies(TypeWithDependencies &&other) = default;
	virtual ~TypeWithDependencies() = default;

	TypeWithDependencies &operator =(const TypeWithDependencies &other) = default;
	TypeWithDependencies &operator =(TypeWithDependencies &&other) = default;

private:
	std::shared_ptr<Dependency> _dependency;
};

class TypeWithDependenciesTestRegistry : public Registry
{
public:
	void Register(_Inout_ IContainer &container) const override
	{
		container.Register<Dependency>();
	};
};

class Given_type_with_dependencies : public ::testing::Test
{
protected:
	void SetUp() override
	{
	};

	void TearDown() override
	{
	};
};

TEST_F(Given_type_with_dependencies, When_getting_type_name_Then_type_is_returned)
{
	VariadicArgumentInstantiator<TypeWithDependencies, Dependency> instantiator;

	std::string expected = typeid (TypeWithDependencies).name();

	EXPECT_EQ(expected, instantiator.GetType());
}

TEST_F(Given_type_with_dependencies, When_getting_dependencies_Then_list_of_dependencies_is_returned)
{
	VariadicArgumentInstantiator<TypeWithDependencies, Dependency> instantiator;

	std::vector<std::string> expected = { typeid (Dependency).name() };

	std::vector<std::string> actual = instantiator.GetDependencies();

	EXPECT_EQ(expected, actual);
}

TEST_F(Given_type_with_dependencies, When_instance_is_created_Then_instance_is_returned)
{
	TypeWithDependenciesTestRegistry registry;

	Container container(registry);

	VariadicArgumentInstantiator<TypeWithDependencies, Dependency> instantiator;

	std::shared_ptr<void> actual = instantiator.CreateInstance(container);

	EXPECT_NE(nullptr, actual);
}

TEST_F(Given_type_with_dependencies, When_instance_is_created_Then_new_instance_is_returned_every_time)
{
	TypeWithDependenciesTestRegistry registry;

	Container container(registry);

	VariadicArgumentInstantiator<TypeWithDependencies, Dependency> instantiator;

	std::shared_ptr<void> one = instantiator.CreateInstance(container);
	std::shared_ptr<void> two = instantiator.CreateInstance(container);

	EXPECT_NE(one, two);
}
