#pragma once
class Stage
{
public:
	Stage();

	virtual void draw() = 0;
	virtual bool update(short* currentStage) = 0;
};

class StageData {
public:
	StageData(Stage* stage, short ID) {
		p_stage = stage;
		p_ID = ID;
	}

	Stage* p_stage;
	short p_ID;
};