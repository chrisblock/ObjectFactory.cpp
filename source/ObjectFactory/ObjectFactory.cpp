#include "stdafx.h"

#include "ObjectFactory.h"

#include "Container.h"

shared_ptr<IContainer> ObjectFactory::_container;

void ObjectFactory::Initialize(const Registry &registry)
{
	Container *container = new Container();

	container->Initialize(registry);

	_container.reset(container);
}

void ObjectFactory::Clear()
{
	_container.reset((IContainer *) __nullptr);
}
