#include "stdafx.h"

#include "ObjectFactory.h"

#include "Container.h"

std::shared_ptr<IContainer> ObjectFactory::_container;

void ObjectFactory::Initialize(_In_ const Registry &registry)
{
	_container = std::make_shared<Container>();

	_container->Initialize(registry);
}

void ObjectFactory::Clear()
{
	_container.reset();
}
