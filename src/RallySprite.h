#pragma once
#include "Rally.h"
#include "Drawable.h"
#include <string>
class RallySprite
{
private:
	float angle;
	float centerX;
	float centerY;
	float scaleX;
	float scaleY;
	GraphicsObject_Sprite* pGOSprite;

public:
	RallySprite();
	~RallySprite();
	RallySprite(const RallySprite&) = delete;
	RallySprite& operator=(const RallySprite&) = delete;
	RallySprite(std::string imgKey);
	RallySprite(Image* i);

	void SetImage(Image* i);
	void SetImage(std::string imgKey);

	void Render(Camera* pcam);
	float GetAngle();
	void SetAngle(float a);
	void SetCenter(float offsetx, float offsety);
	void SetPosition(float scalex, float scaley);
	void SetScaleFactor(float scalex, float scaley);
	void SetScalePixel(float width, float height);

};