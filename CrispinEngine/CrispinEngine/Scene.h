#pragma once
class Scene
{
public:
	Scene();

	virtual void draw() = 0;
	virtual bool update(short* currentStage) = 0;
	virtual void destroy() = 0;
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