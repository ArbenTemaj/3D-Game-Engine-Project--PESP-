#pragma once
#include <PESP/Prerequisites.h>
#include <set>

class GraphicsEngine
{
public:
	GraphicsEngine(Game* game);
	~GraphicsEngine();

	void update();
public:
	RenderSystem* getRenderSystem();

	void addComponent(Component* component);
	void removeComponent(Component* component);
private:
	std::unique_ptr<RenderSystem> m_render_system = nullptr;
	Game* m_game = nullptr;

	std::set<MeshComponent*> m_meshes;
	std::set<CameraComponent*> m_cameras;
	std::set<LightComponent*> m_lights;
	std::set<TerrainComponent*> m_terrains;
	std::set<WaterComponent*> m_waterComps;
	std::set<FogComponent*> m_fogs;
	std::set<TextComponent*> m_text;
};