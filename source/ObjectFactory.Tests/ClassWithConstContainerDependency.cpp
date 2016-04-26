#include "stdafx.h"

#include "ClassWithConstContainerDependency.h"

IMPLEMENT_INSTANTIATOR(ClassWithConstContainerDependency, const IContainer);

void swap(ClassWithConstContainerDependency &left, ClassWithConstContainerDependency &right)
{
	using std::swap;

	swap(left._container, right._container);
}

ClassWithConstContainerDependency::ClassWithConstContainerDependency()
{
}

ClassWithConstContainerDependency::ClassWithConstContainerDependency(const std::shared_ptr<const IContainer> &container) :
	  _container(container)
{
}

ClassWithConstContainerDependency::ClassWithConstContainerDependency(const ClassWithConstContainerDependency &other) :
	  _container(other._container)
{
}

ClassWithConstContainerDependency::ClassWithConstContainerDependency(ClassWithConstContainerDependency &&other) :
	  ClassWithConstContainerDependency()
{
	swap(*this, other);
}

const std::shared_ptr<const IContainer> &ClassWithConstContainerDependency::GetContainer() const
{
	return _container;
}
