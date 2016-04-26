#pragma once

#include <memory>
#include <string>
#include <vector>

class DependencyGraphNode : public std::enable_shared_from_this<DependencyGraphNode>
{
public:
	DependencyGraphNode();
	DependencyGraphNode(const std::string &name);
	DependencyGraphNode(const std::string &name, const std::shared_ptr<DependencyGraphNode> &parent);
	DependencyGraphNode(const DependencyGraphNode &other);
	DependencyGraphNode(DependencyGraphNode &&other);
	~DependencyGraphNode();

	DependencyGraphNode &operator =(DependencyGraphNode other);

	friend void swap(DependencyGraphNode &left, DependencyGraphNode &right);

	const std::string &GetName() const;

	std::shared_ptr<DependencyGraphNode> GetParent() const;

	void AddDependency(const std::string &name);
	void AddDependency(const std::shared_ptr<DependencyGraphNode> &dependency);
	bool HasDependencyOn(const std::string &name) const;

	bool HasCycles() const;
	bool HasDependencies() const;

private:
	std::string _name;
	std::weak_ptr<DependencyGraphNode> _parent;
	std::vector<std::shared_ptr<DependencyGraphNode>> _dependencies;
};

void swap(DependencyGraphNode &left, DependencyGraphNode &right);
