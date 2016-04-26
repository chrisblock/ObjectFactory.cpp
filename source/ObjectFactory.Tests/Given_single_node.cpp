#include "stdafx.h"

#include <DependencyGraphNode.h>

class Given_single_node : public ::testing::Test
{
protected:
	virtual void SetUp() override
	{
	};

	virtual void TearDown() override
	{
	};

	std::string _name = "name";
};

TEST_F(Given_single_node, When_default_constructed_Then_name_is_empty_string)
{
	DependencyGraphNode node;

	EXPECT_EQ(std::string(), node.GetName());
}

TEST_F(Given_single_node, When_default_constructed_Then_parent_is_null)
{
	DependencyGraphNode node;

	EXPECT_EQ(nullptr, node.GetParent());
}

TEST_F(Given_single_node, When_default_constructed_Then_has_no_dependencies)
{
	DependencyGraphNode node;

	EXPECT_EQ(false, node.HasDependencies());
}

TEST_F(Given_single_node, When_name_only_constructed_Then_name_matches)
{
	DependencyGraphNode node(_name);

	EXPECT_EQ(_name, node.GetName());
}

TEST_F(Given_single_node, When_name_only_constructed_Then_parent_is_null)
{
	DependencyGraphNode node(_name);

	EXPECT_EQ(nullptr, node.GetParent());
}

TEST_F(Given_single_node, When_name_only_constructed_Then_has_no_dependencies)
{
	DependencyGraphNode node(_name);

	EXPECT_EQ(false, node.HasDependencies());
}

TEST_F(Given_single_node, When_name_only_constructed_Then_has_dependency_on_self)
{
	DependencyGraphNode node(_name);

	EXPECT_EQ(true, node.HasDependencyOn(_name));
}

TEST_F(Given_single_node, When_constructed_with_name_and_parent_Then_name_matches)
{
	std::shared_ptr<DependencyGraphNode> parent = std::make_shared<DependencyGraphNode>("parent");

	DependencyGraphNode node(_name, parent);

	EXPECT_EQ(_name, node.GetName());
}

TEST_F(Given_single_node, When_constructed_with_name_and_parent_Then_parent_matches)
{
	std::shared_ptr<DependencyGraphNode> parent = std::make_shared<DependencyGraphNode>("parent");

	DependencyGraphNode node(_name, parent);

	EXPECT_EQ(parent, node.GetParent());
}

TEST_F(Given_single_node, When_constructed_with_name_and_parent_Then_has_no_dependencies)
{
	std::shared_ptr<DependencyGraphNode> parent = std::make_shared<DependencyGraphNode>("parent");

	DependencyGraphNode node(_name, parent);

	EXPECT_EQ(false, node.HasDependencies());
}

TEST_F(Given_single_node, When_constructed_with_name_and_parent_Then_has_dependency_on_self)
{
	std::shared_ptr<DependencyGraphNode> parent = std::make_shared<DependencyGraphNode>("parent");

	DependencyGraphNode node(_name, parent);

	EXPECT_EQ(true, node.HasDependencyOn(_name));
}

TEST_F(Given_single_node, When_dependency_added_Then_dependency_is_reported)
{
	static const char NAME[] = "dependency1";

	std::shared_ptr<DependencyGraphNode> dependency1 = std::make_shared<DependencyGraphNode>(NAME);
	std::shared_ptr<DependencyGraphNode> dependency2 = std::make_shared<DependencyGraphNode>("dependency2");

	DependencyGraphNode node(_name);

	node.AddDependency(dependency1);
	node.AddDependency(dependency2);

	EXPECT_EQ(true, node.HasDependencyOn(NAME));
}

TEST_F(Given_single_node, When_non_cyclic_dependencies_added_Then_cycle_is_not_reported)
{
	std::shared_ptr<DependencyGraphNode> dependency1 = std::make_shared<DependencyGraphNode>("dependency1");
	std::shared_ptr<DependencyGraphNode> dependency2 = std::make_shared<DependencyGraphNode>("dependency2");

	DependencyGraphNode node(_name);

	node.AddDependency(dependency1);
	node.AddDependency(dependency2);

	EXPECT_EQ(false, node.HasCycles());
}

TEST_F(Given_single_node, When_cyclic_dependencies_added_Then_cycle_is_reported)
{
	std::shared_ptr<DependencyGraphNode> dependency1 = std::make_shared<DependencyGraphNode>("dependency1");
	std::shared_ptr<DependencyGraphNode> dependency2 = std::make_shared<DependencyGraphNode>("dependency2");

	std::shared_ptr<DependencyGraphNode> node = std::make_shared<DependencyGraphNode>(_name);

	node->AddDependency(dependency1);
	node->AddDependency(dependency2);

	dependency1->AddDependency(node);

	EXPECT_EQ(true, node->HasCycles());
}

TEST_F(Given_single_node, When_complex_cyclic_dependencies_added_Then_cycle_is_reported)
{
	std::shared_ptr<DependencyGraphNode> dependency1 = std::make_shared<DependencyGraphNode>("dependency1");
	std::shared_ptr<DependencyGraphNode> dependency2 = std::make_shared<DependencyGraphNode>("dependency2");
	std::shared_ptr<DependencyGraphNode> dependency3 = std::make_shared<DependencyGraphNode>("dependency3");
	std::shared_ptr<DependencyGraphNode> dependency4 = std::make_shared<DependencyGraphNode>("dependency4");
	std::shared_ptr<DependencyGraphNode> dependency5 = std::make_shared<DependencyGraphNode>("dependency5");
	std::shared_ptr<DependencyGraphNode> dependency6 = std::make_shared<DependencyGraphNode>("dependency6");

	dependency2->AddDependency(dependency1);
	dependency3->AddDependency(dependency2);
	dependency4->AddDependency(dependency3);
	dependency5->AddDependency(dependency4);
	dependency6->AddDependency(dependency5);

	std::shared_ptr<DependencyGraphNode> node = std::make_shared<DependencyGraphNode>(_name);

	node->AddDependency(dependency6);

	dependency1->AddDependency(node);

	EXPECT_EQ(true, node->HasCycles());
}
