#include <PESP/Entity/FogComponent.h>
#include <PESP/Entity/Entity.h>
#include <PESP/Game/World.h>
#include <PESP/Game/Game.h>
#include <PESP/Graphics/GraphicsEngine.h>

FogComponent::FogComponent() = default;

FogComponent::~FogComponent()
{
    m_entity->getWorld()->getGame()->getGraphicsEngine()->removeComponent(this);
}

void FogComponent::setData(const Vector4D& color, f32 start, f32 end)
{
    m_color = color;
    m_start = start;
    m_end = end;
}

Vector4D FogComponent::getColor()
{
    return m_color;
}

f32 FogComponent::getStart()
{
    return m_start;
}

f32 FogComponent::getEnd()
{
    return m_end;
}

void FogComponent::onCreateInternal()
{
    m_entity->getWorld()->getGame()->getGraphicsEngine()->addComponent(this);
}