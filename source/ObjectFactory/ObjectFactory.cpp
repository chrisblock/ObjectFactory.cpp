#include "stdafx.h"

#include "ObjectFactory.h"

#include "Container.h"

shared_ptr<IContainer> ObjectFactory::_container;

void ObjectFactory::Initialize(const Registry &registry)
{
	_container = make_shared<Container>();

	_container->Initialize(registry);
}

void ObjectFactory::Clear()
{
	_container.reset();
}
