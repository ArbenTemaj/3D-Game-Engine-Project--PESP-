#include <PESP/Entity/LightComponent.h>
#include <PESP/Entity/Entity.h>
#include <PESP/Game/World.h>
#include <PESP/Game/Game.h>
#include <PESP/Graphics/GraphicsEngine.h>

LightComponent::LightComponent() = default;

LightComponent::~LightComponent()
{
	m_entity->getWorld()->getGame()->getGraphicsEngine()->removeComponent(this);
}

void LightComponent::setColor(const Vector4D& color)
{
	m_color = color;
}

Vector4D LightComponent::getColor()
{
	return m_color;
}

void LightComponent::onCreateInternal()
{
	m_entity->getWorld()->getGame()->getGraphicsEngine()->addComponent(this);
}