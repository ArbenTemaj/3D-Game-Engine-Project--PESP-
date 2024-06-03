#include "PESPGame.h"
#include "Player.h"
#include <time.h>

PESPGame::PESPGame() = default;

PESPGame::~PESPGame() = default;

void PESPGame::onCreate()
{
	Game::onCreate();

	FontUtility fontUtility;
	fontUtility.createFont(L"Bahnschrift", 16, L"PESP\\Assests\\Fonts\\");


	auto sphere = getResourceManager()->createResourceFromFile< Mesh >(L"PESP/Assests/Meshes/sphere.obj");

	//auto sky = getResourceManager()->createResourceFromFile< Texture >(L"PESP/Assests/Textures/sky.jpg");
	auto heightMap = getResourceManager()->createResourceFromFile< Texture >(L"PESP/Assests/Textures/height_map.png");
	auto grass = getResourceManager()->createResourceFromFile< Texture >(L"PESP/Assests/Textures/grass.jpg");
	auto ground = getResourceManager()->createResourceFromFile< Texture >(L"PESP/Assests/Textures/ground.jpg");
	auto waveheightMap = getResourceManager()->createResourceFromFile< Texture >(L"PESP/Assests/Textures/WaterHeightMap.png");

	auto skyMat = getResourceManager()->createResourceFromFile< Material >(L"PESP/Assests/Shaders/SkyBox.hlsl");

	auto font = getResourceManager()->createResourceFromFile<Font>(L"PESP/Assests/Fonts/Bahnschrift.font");

	//skyMat->addTexture(sky);
	//skyMat->setCullMode(CullMode::Front);

	//skybox
	/*{
		auto entity = getWorld()->createEntity<Entity>();
		auto meshComponent = entity->createComponent<MeshComponent>();
		auto transform = entity->getTransform();
		meshComponent->setMesh(sphere);
		meshComponent->addMaterial(skyMat);

		transform->setScale(Vector3D(5000, 5000, 5000));
	}*/

	//terrain 
	{
		auto entity = getWorld()->createEntity<Entity>();
		auto terrainComponent = entity->createComponent<TerrainComponent>();
		terrainComponent->setHeightMap(heightMap);
		terrainComponent->setGroundMap(grass);
		terrainComponent->setCliffMap(ground);

		auto transform = entity->getTransform();
		transform->setScale(Vector3D(1, 1, 1));
	}

	//sea 
	{
		auto entity = getWorld()->createEntity<Entity>();
		auto waterComponent = entity->createComponent<WaterComponent>();
		waterComponent->setWaveHeightMap(waveheightMap);


		auto transform = entity->getTransform();
		transform->setPosition(Vector3D(-768, 15, -768));
	}

	//fog
	{
		auto entity = getWorld()->createEntity<Entity>();
		auto fogComponent = entity->createComponent<FogComponent>();
		fogComponent->setData(Vector4D(1.0f, 0.7f, 0.7f, 1.0f), 50.0, 600.0);
	}
	
	//light
	{
		m_entity = getWorld()->createEntity<Entity>();
		auto lightComponent = m_entity->createComponent<LightComponent>();
		//lightComponent->setColor(Vector4D(1, 1, 1, 1));
		lightComponent->setColor(Vector4D(0.8f, 0.4f, 0.4f, 1));
		m_entity->getTransform()->setRotation(Vector3D(-0.707f, 0.707f, 0));
	}

	//text - info
	{
		m_text = getWorld()->createEntity<Entity>();
		auto text = m_text->createComponent<TextComponent>();
		text->setFont(font);
		text->setText(L"info");
		m_text->getTransform()->setPosition(Vector3D(10, 10, 0));
	}

	//text - bottomRight
	{
		m_textT = getWorld()->createEntity<Entity>();
		auto text = m_textT->createComponent<TextComponent>();
		text->setFont(font);
		text->setText(L"Real-time graphical rendering of the ESP-Engine");
		m_textT->getTransform()->setPosition(Vector3D(0, 0, 0));
	}

	m_player = getWorld()->createEntity<Player>();

	getInputSystem()->lockCursor(m_looked);
}

void PESPGame::onUpdate(f32 deltaTime)
{

	Game::onUpdate(deltaTime);
	m_rotation += 1.57 * deltaTime;

	m_entity->getTransform()->setRotation(Vector3D(0.707f, -3.14f, 0));

	auto clientSize = getDisplay()->getClientSize();
	auto textComp = m_text->getComponent<TextComponent>();
	auto textBounds = m_textT->getComponent<TextComponent>()->getBounds();

	auto playerPos = m_player->getTransform()->getPosition();
	auto playerRot = m_player->getTransform()->getRotation();
	auto p = 180.0f / 3.14f;


	auto infoText = std::wstringstream();
	infoText << L"PESP info\n\n";
	infoText << L"FPS: " << (int)(1.0f / deltaTime) << L"\n";
	infoText << L"Screen Size W:" << (int)clientSize.width << L" H:" << (int)clientSize.height << L"\n";
	infoText << L"Player Position: X:" << (int)playerPos.x
		<< L" Y:" << (int)playerPos.y
		<< L" Z:" << (int)playerPos.z << L"\n";
	infoText << L"Player Rotation: X:" << (int)(playerRot.x * p)
		<< L" Y:" << (int)(playerRot.y * p)
		<< L" Z:" << (int)(playerRot.z * p) << L"\n";

	m_textT->getTransform()->setPosition(Vector3D( //bottom rigth message
		clientSize.width - textBounds.width - 15,
		clientSize.height - textBounds.height - 10,
		0
	));

	textComp->setText(infoText.str().c_str());

	if (getInputSystem()->isKeyDown(Key::Escape))
	{
		m_looked = !m_looked;
		getInputSystem()->lockCursor(m_looked);
	}
}