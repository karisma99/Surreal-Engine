//ScreenLog

#include "ScreenLog.h"
#include "SurrealSprite.h"
#include "SpriteFont.h"
#include "SceneManager.h"

ScreenLog* ScreenLog::ptrInstance = nullptr;

ScreenLog::ScreenLog()
{

}

void ScreenLog::Add(char* A, ...)
{
	va_list args; 
	va_start(args, A); 
	vsprintf_s(Instance().DebugBuff, A, args);
	va_end(args);

	std::string s(Instance().DebugBuff);
	Instance().messages.push_back(s);
}

void ScreenLog::privRender()
{
	int offsetY = 0; 
	for (auto& it : messages)
	{
		std::string s = it; 
		int offsetX = 0; 
		for (unsigned int i = 0; i < it.length(); i++)
		{
			SurrealSprite* sprite = font->GetGlyph(s[i]);
			sprite->SetPosition((float)anchorX + offsetX, (float)anchorY - (sprite->GetHeight() * offsetY));
			offsetX += (int)sprite->GetWidth();
			sprite->Render();
		}
		offsetY++;
	}
}

void ScreenLog::privDelete()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

