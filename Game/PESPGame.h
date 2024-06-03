#pragma once
#include <PESP/All.h>
#include <sstream>

class PESPGame : public Game
{
public:
	PESPGame();
	~PESPGame();
protected:
	virtual void onCreate() override;
	virtual void onUpdate(f32 deltaTime) override;

private:
	Entity* m_entity = nullptr;
	Entity* m_text = nullptr;
	Entity* m_textT = nullptr;
	Entity* m_player = nullptr;

	f32 m_rotation = 0.0f;
	bool m_looked = true;
};