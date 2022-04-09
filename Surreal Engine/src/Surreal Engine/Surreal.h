#ifndef _Surreal
#define _Surreal

#include "AzulCore.h"

class Surreal: public Engine
{
	friend class SurrealAttorney;
private:

	static Surreal* ptrInstance;

	// constructor
	Surreal() = default; 
	Surreal(const Surreal& c) = delete; 
	Surreal& operator = (const Surreal& t) = delete; 
	~Surreal() = default; 

	static Surreal& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new Surreal;
		return *ptrInstance;
	};

	// Methods Users need to overload
    virtual void Initialize();
    virtual void LoadContent();
	virtual void Update();
    virtual void Draw();
    virtual void UnLoadContent();

	void LoadResources();
	void GameInitialize(); 
	void GameEnd();

public:
	static int GetHeight() { return Instance().getHeight(); }; 
	static int GetWidth() { return Instance().getWidth(); };
	static void SetClear(float r, float g, float b, float a) { Instance().SetClearColor(r, g, b, a); };
	static void SetWidthHeight(int w, int h) { Instance().setWidthHeight(w, h); };
	static void SetWindowName(const char* name) { Instance().setWindowName(name); };
	static void Run() { Instance().run(); Delete(); };
	static void Delete() { Instance().privDelete(); };


private:	
	void privDelete();
	static float GetTime() { return Instance().GetTimeInSeconds(); };

};

#endif _Surreal