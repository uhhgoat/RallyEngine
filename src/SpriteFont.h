#ifndef _SpriteFont
#define _SpriteFont

#include <xmllite.h>
#include <map>
class RallySprite;
class Texture;

class SpriteFont
{
public:
	using Key = int;
	using Glyph = RallySprite;// your sprite class;

private:
	std::string Name;
	Texture* FontTexture;
	using FontMap = std::map< Key, Glyph* >;
	FontMap fontmap;

	const std::string DefaultPath = "Fonts/";

	// Parse the XML file
	void XMLtoCollection(std::string filename);

	// Tool: Reads & converts an XML attribute into an int
	void ElementTextToInt(IXmlReader* pReader, int& out);

public:
	SpriteFont() = delete;
	SpriteFont(std::string name, std::string path);
	~SpriteFont();
	SpriteFont(const SpriteFont&) = delete;
	SpriteFont& operator=(const SpriteFont&) = delete;


	Glyph* GetGlyph(char c);
};

#endif _SpriteFont