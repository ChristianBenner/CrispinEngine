#pragma once
#include <map>
#include "Managers\Audio.h"
#include "Objects\Data\GLTexture.h"
class Scene
{
public:
	Scene();

	virtual void draw() = 0;
	virtual bool update(short* currentStage) = 0;
	virtual void destroy() = 0;

protected:
	/*
	Not sure about this:
	// Holds data that the stage will automatically free when destroyed
	std::map<int, Crispin::Sound> m_sounds;
	std::map<int, Crispin::Music> m_music;
	std::map<int, Crispin::GLTexture> m_textures;
	*/
};

class SceneData {
public:
	SceneData(Scene* stage, short ID) {
		p_stage = stage;
		p_ID = ID;
	}

	Scene* p_stage;
	short p_ID;
};