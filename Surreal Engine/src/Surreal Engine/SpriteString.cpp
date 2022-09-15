//SpriteString

#include "SpriteString.h"
#include "SceneManager.h"

SpriteString::SpriteString()
{
	posX = 0;
	posY = 0;
	height = 0; 
	width = 0; 
	pFont = nullptr;
}

SpriteString::SpriteString(const SpriteFont&)
{
	posX = 0;
	posY = 0;
	height = 0;
	width = 0;
	pFont = nullptr;
}

SpriteString::SpriteString(SpriteFont* sf, std::string s, int x, int y)
{
	pFont = sf; 
	posX = x; 
	posY = y; 
	height = 0; 
	width = 0;

	int tempHeight = 0; 
	for (unsigned int i = 0; i < s.length(); i++)
	{
		SpriteFont::Glyph* g = sf->GetGlyph(s[i]);
		glyphs.insert(glyphs.end(), g);
		tempHeight = (int)g->GetHeight();
		width += (int)g->GetWidth();

		if (tempHeight > height)
			height = tempHeight;
	}
}

int SpriteString::GetHeight()
{
	return height;
}

int SpriteString::GetWidth()
{
	return width; 
}

void SpriteString::Render()
{
	float offset = 0; 
	for (auto& it : glyphs)
	{
		SurrealSprite* s = it; 
		s->SetPosition((float)(posX + offset), (float)posY);
		s->RenderPartialTexture();
		offset += s->GetWidth();
	}
}

void SpriteString::Set(int x, int y)
{
	posX = x; 
	posY = y; 
}

void SpriteString::Set(SpriteFont* sf, std::string s, int x, int y)
{
	pFont = sf; 
	posX = x; 
	posY = y; 
}