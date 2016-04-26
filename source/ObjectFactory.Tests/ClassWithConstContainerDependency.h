#pragma once

#include <memory>

#include <InstantiatorFactory.h>

class IContainer;

class ClassWithConstContainerDependency
{
public:
	ClassWithConstContainerDependency();
	ClassWithConstContainerDependency(const std::shared_ptr<const IContainer> &container);
	ClassWithConstContainerDependency(const ClassWithConstContainerDependency &other);
	ClassWithConstContainerDependency(ClassWithConstContainerDependency &&other);
	virtual ~ClassWithConstContainerDependency() = default;

	friend void swap(ClassWithConstContainerDependency &left, ClassWithConstContainerDependency &right);

	const std::shared_ptr<const IContainer> &GetContainer() const;

private:
	std::shared_ptr<const IContainer> _container;
};

void swap(ClassWithConstContainerDependency &left, ClassWithConstContainerDependency &right);

DECLARE_INSTANTIATOR(ClassWithConstContainerDependency);
