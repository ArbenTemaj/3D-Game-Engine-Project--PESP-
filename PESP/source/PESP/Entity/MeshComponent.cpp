#include <PESP/Entity/MeshComponent.h>
#include <PESP/Entity/Entity.h>
#include <PESP/Game/World.h>
#include <PESP/Game/Game.h>
#include <PESP/Graphics/GraphicsEngine.h>

MeshComponent::MeshComponent() = default;

MeshComponent::~MeshComponent()
{
	m_entity->getWorld()->getGame()->getGraphicsEngine()->removeComponent(this);
}

void MeshComponent::setMesh(const MeshPtr& mesh)
{
	m_mesh = mesh;
}

const MeshPtr& MeshComponent::getMesh()
{
	return m_mesh;
}

void MeshComponent::addMaterial(const MaterialPtr& material)
{
	m_materials.push_back(material);
}

void MeshComponent::removeMaterial(ui32 index)
{
	if (index >= m_materials.size()) return;
	m_materials.erase(m_materials.begin() + index);
}
const std::vector<MaterialPtr>& MeshComponent::getMaterials()
{
	return m_materials;
}

void MeshComponent::onCreateInternal()
{
	m_entity->getWorld()->getGame()->getGraphicsEngine()->addComponent(this);
}