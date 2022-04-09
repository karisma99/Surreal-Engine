// ScreenLog

#ifndef _ScreenLog
#define _ScreenLog

#include <list>

class SpriteFont;

class ScreenLog
{
	friend class ScreenLogAttorney;

private:

	static ScreenLog* ptrInstance;

	ScreenLog();
	ScreenLog(const ScreenLog& c) = delete;
	ScreenLog& operator = (const ScreenLog& t) = delete;
	~ScreenLog() = default;

	static ScreenLog& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new ScreenLog;
		return *ptrInstance;
	};

	using MessageCollection = std::list < std::string >;
	MessageCollection messages; 

public:
	void Add(char* A, ...);

private:
	static void Delete() { Instance().privDelete(); };
	static void Render() { Instance().privRender(); };

	void privDelete();
	void privRender();

	static const int anchorX = 50;
	static const int anchorY = 550; 
	char DebugBuff[256];
	std::string DebugFont = "DebugFont";
	SpriteFont* font;

};

#endif _ScreenLog