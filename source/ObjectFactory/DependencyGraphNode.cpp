#include "stdafx.h"

#include "DependencyGraphNode.h"

#include <algorithm>

void swap(DependencyGraphNode &left, DependencyGraphNode &right)
{
	using std::swap;

	swap(left._dependencies, right._dependencies);
	swap(left._name, right._name);
	swap(left._parent, right._parent);
}

DependencyGraphNode::DependencyGraphNode()
{
}

DependencyGraphNode::DependencyGraphNode(const std::string &name) :
	  DependencyGraphNode(name, nullptr)
{
}

DependencyGraphNode::DependencyGraphNode(const std::string &name, const std::shared_ptr<DependencyGraphNode> &parent) :
	  _name(name)
	, _parent(parent)
{
}

DependencyGraphNode::DependencyGraphNode(const DependencyGraphNode &other) :
	  _name(other._name)
	, _parent(other._parent)
	, _dependencies(other._dependencies)
{
}

DependencyGraphNode::DependencyGraphNode(DependencyGraphNode &&other) :
	  DependencyGraphNode()
{
	swap(*this, other);
}

DependencyGraphNode::~DependencyGraphNode()
{
}

DependencyGraphNode &DependencyGraphNode::operator =(DependencyGraphNode other)
{
	swap(*this, other);

	return *this;
}

const std::string &DependencyGraphNode::GetName() const
{
	return _name;
}

std::shared_ptr<DependencyGraphNode> DependencyGraphNode::GetParent() const
{
	return _parent.lock();
}

void DependencyGraphNode::AddDependency(const std::string &name)
{
	std::shared_ptr<DependencyGraphNode> dependency = std::make_shared<DependencyGraphNode>(name, shared_from_this());

	AddDependency(dependency);
}

void DependencyGraphNode::AddDependency(const std::shared_ptr<DependencyGraphNode> &dependency)
{
	_dependencies.push_back(dependency);
}

bool DependencyGraphNode::HasDependencyOn(const std::string &name) const
{
	bool result = (_name == name);

	if (result == false)
	{
		std::vector<std::shared_ptr<DependencyGraphNode>>::const_iterator pos = std::find_if(_dependencies.cbegin(), _dependencies.cend(), [=](const std::shared_ptr<DependencyGraphNode> &d) { return d->HasDependencyOn(name); });

		result = (pos != _dependencies.cend());
	}

	return result;
}

bool DependencyGraphNode::HasCycles() const
{
	bool result = false;

	for (const std::shared_ptr<DependencyGraphNode> &descendant : _dependencies)
	{
		if (descendant->HasDependencyOn(_name))
		{
			result = true;

			break;
		}
	}

	return result;
}

bool DependencyGraphNode::HasDependencies() const
{
	bool result = (_dependencies.empty() == false);

	return result;
}
