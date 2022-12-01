#pragma once
#include "SpriteFont.h"
#include "Drawable.h"
#include "SceneManager.h"
#include <vector>
class SpriteString
{
public:
	using GlyphCollection = std::vector<SpriteFont::Glyph*>;

	SpriteString() = default;
	SpriteString(const SpriteString&) = default;
	SpriteString& operator=(const SpriteString&) = delete;
	SpriteString(SpriteFont* sf, std::string s, int x, int y);
	~SpriteString();

	void Initialize(SpriteFont* sf, std::string s, int x, int y);
	void Recycle();

	int GetWidth();
	int GetHeight();
	void Set(int x, int y);
	void Set(SpriteFont* sf, std::string s, int x, int y);

	void Set(std::string s);

	void Render(Camera* pcam);
	void Draw2D() { Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrent2DCamera()); };

private:
	GlyphCollection glyphs;
	SpriteFont* sfont;
	int width;
	int height;
	int posX;
	int posY;

	bool active = false;

};