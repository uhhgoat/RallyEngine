#include "SpriteTest.h"
SpriteTest::SpriteTest()
{
	SetImage("heart");

	SetAngle(0);
	SetCenter(50, 0);
	SetScalePixel(100, 100);
	SetPosition(100, 100);

}

SpriteTest::SpriteTest(float angle, float x, float y, float scale)
{
	SetImage("heart");

	SetAngle(angle);
	SetCenter(50, 0);
	SetScalePixel(scale, scale);
	SetPosition(x, y);
}

SpriteTest::~SpriteTest()
{
}

void SpriteTest::Remove()
{
}