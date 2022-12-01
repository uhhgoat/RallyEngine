#pragma once
#include "../src/GameObject.h"
#include "../src/RallySprite.h"
class SpriteTest : public RallySprite, public Align16
{
public:
	SpriteTest();
	SpriteTest(float angle, float x, float y, float scale);
	~SpriteTest();

	void Remove();
};