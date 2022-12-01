#include "SpriteString.h"
#include "RallySprite.h"
SpriteString::SpriteString(SpriteFont* sf, std::string s, int x, int y)
{
	sfont = sf;
	posX = x;
	posY = y;
	for (std::string::iterator it = s.begin(); it != s.end(); it++)
	{
		glyphs.push_back(sf->GetGlyph(*it));
	}
	active = true;
}

SpriteString::~SpriteString()
{
	while (!glyphs.empty())
	{
		glyphs.pop_back();
	}
}

void SpriteString::Initialize(SpriteFont* sf, std::string s, int x, int y)
{
	sfont = sf;
	posX = x;
	posY = y;
	for (std::string::iterator it = s.begin(); it != s.end(); it++)
	{
		glyphs.push_back(sf->GetGlyph(*it));
	}
	active = true;
}

void SpriteString::Recycle()
{
	active = false;
	while (!glyphs.empty())
	{
		glyphs.pop_back();
	}
}

int SpriteString::GetWidth()
{
	return width;
}
int SpriteString::GetHeight()
{
	return height;
}
void SpriteString::Set(int x, int y)
{
	posX = x;
	posY = y;
}
void SpriteString::Set(SpriteFont* sf, std::string s, int x, int y)
{
	sfont = sf;
	posX = x;
	posY = y;
	for (std::string::iterator it = s.begin(); it != s.end(); it++)
	{
		glyphs.push_back(sf->GetGlyph(*it));
	}
}
void SpriteString::Set(std::string s)
{
	glyphs.clear();
	for (std::string::iterator it = s.begin(); it != s.end(); it++)
	{
		glyphs.push_back(sfont->GetGlyph(*it));
	}
}

void SpriteString::Render(Camera* pcam)
{
	int offset = 20;
	if (!active)
		return;
	for (GlyphCollection::iterator it = glyphs.begin(); it != glyphs.end(); it++)
	{
		(*it)->SetPosition((float)posX + offset, (float)posY);
		offset += 20;
		(*it)->Render(pcam);
	}
}