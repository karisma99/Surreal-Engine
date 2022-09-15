#ifndef _Surreal
#define _Surreal

class Surreal
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

	void LoadResources();
	void GameInitialize(); 
	void GameEnd();

public:
	static int GetHeight() { return Instance().privGetHeight(); }; 
	static int GetWidth() { return Instance().privGetWidth(); };
	static void SetClear(float r, float g, float b, float a) { Instance().privSetClearColor(r, g, b, a); };
	static void SetWidthHeight(int w, int h) { Instance().privSetWidthHeight(w, h); };
	static void SetWindowName(const char* name) { Instance().privSetWindowName(name); };
	
private:	
	void privInitialize(HWND hwnd);
	void privUpdate();
	void privDraw();
	void privUnLoadContent();

	static void Initialize(HWND hwnd) { Instance().privInitialize(hwnd); };
	static void Update() { Instance().privUpdate(); };
	static void Draw() { Instance().privDraw(); };
	static void UnLoadContent() { Instance().privUnLoadContent(); };

	int privGetWidth();
	int privGetHeight();
	void privSetWindowName(const char* name);
	void privSetWidthHeight(int w, int h);
	void privSetClearColor(float r, float g, float b, float a);

	void privDelete();
	static void Delete() { Instance().privDelete(); };

	float privGetTimeInSeconds();
	static float GetTime() { return Instance().privGetTimeInSeconds(); };

};

#endif _Surreal