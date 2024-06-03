#include <PESP/Entity/Component.h>
#include <PESP/Entity/Entity.h>

Component::Component() = default;
Component::~Component() = default;

void Component::release()
{
	m_entity->removeComponent(m_typeId);
}

Entity* Component::getEntity()
{
	return m_entity;
}

void Component::onCreateInternal() {}