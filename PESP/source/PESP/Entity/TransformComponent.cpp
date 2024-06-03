#include <PESP/Entity/TransformComponent.h>

TransformComponent::TransformComponent() = default;

TransformComponent::~TransformComponent() = default;

void TransformComponent::setPosition(const Vector3D& position)
{
	m_position = position;
	updateWorldMatrix();
}

Vector3D TransformComponent::getPosition()
{
	return m_position;
}

void TransformComponent::setRotation(const Vector3D& rotation)
{
	m_rotation = rotation;
	updateWorldMatrix();
}

Vector3D TransformComponent::getRotation()
{
	return m_rotation;
}

void TransformComponent::getWorldMatrix(Matrix4x4& mat)
{
	mat = m_worldMat;
}

void TransformComponent::updateWorldMatrix()
{
	Matrix4x4 temp;
	m_worldMat.setIdentity();

	temp.setIdentity();
	temp.setScale(m_scale);
	m_worldMat *= temp;

	temp.setIdentity();
	temp.setRotationX(m_rotation.x);
	m_worldMat *= temp;

	temp.setIdentity();
	temp.setRotationY(m_rotation.y);
	m_worldMat *= temp;

	temp.setIdentity();
	temp.setRotationZ(m_rotation.z);
	m_worldMat *= temp;

	temp.setIdentity();
	temp.setTranslation(m_position);
	m_worldMat *= temp;
}

void TransformComponent::setScale(const Vector3D& scale)
{
	m_scale = scale;
	updateWorldMatrix();
}

Vector3D TransformComponent::getScale()
{
	return m_scale;
}